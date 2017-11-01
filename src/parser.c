#include <builtins.h>
#include <parser.h>
#include <statement.h>
#include <stdlib.h>
#include <string.h>
#include <util.h>
#include <value.h>
#include <errno.h>

void setup_inbuilts() {
	list_add(&env.functions, &sin_ib);
	list_add(&env.functions, &cos_ib);
	list_add(&env.functions, &tan_ib);
	list_add(&env.functions, &radians_ib);
	list_add(&env.functions, &degrees_ib);
	list_add(&env.functions, &print_ib);

	// GPIO library
	list_add(&env.functions, &export_pin_ib);
	list_add(&env.functions, &unexport_pin_ib);
	list_add(&env.functions, &direct_pin_ib);
	list_add(&env.functions, &write_pin_ib);
	list_add(&env.functions, &read_pin_ib);

	list_add(&env.functions, &sleep_ib);
}

int main(int argc, char **argv) {
	init_environment();
	setup_inbuilts();

	list tokens;
	init_list(&tokens);

	// Tokeniser stage
	FILE *file = fopen(argv[1], "r");
	printf("Source file: %s (%d)\n", argv[1], file);
	tokeniser(file, &tokens);
	fclose(file);
	printf("Found %u tokens in the source file: ", tokens.count);
	print_list(&tokens);

	// Statement builder stage
	list statements;
	init_list(&statements);
	statement_builder(&tokens, &statements);
	printf("Built %u statements.\n", statements.count);

	puts("\nProgram output:");
	for(int i = 0; i < statements.count; i++) {
		statement *s = statements.items[i];
		s->func(s->data);
	}
	puts("Program execution complete.");

	puts("\nVariable dump:");
	for(int i = 0; i < env.variables.count; i++) {
		variable *x = env.variables.items[i];
		printf("%s: ", x->name);
		print_value(&x->value);
		if(i == env.variables.count - 1) putchar('\n');
		else fputs(", ", stdout);
	}

	destroy_list(&statements);
	destroy_list(&tokens);
}

/** Tokenises the given file until it reaches EOF, and dumps the contents
    into the list ls. */
void tokeniser(FILE *file, list *tokens) {
	text_builder *builder = malloc(sizeof(text_builder));
	if(builder == NULL) {
		error("Unable to allocate memory: %s\n", strerror(errno));
	}
	int c;

	while(1) {
		builder->length = 0;
		builder->capacity = 16;
		builder->text = malloc(sizeof(char) * builder->capacity);

		while(is_whitespace(c = fgetc(file)));
		if(c == EOF) {
			break;
		} else if(is_symbol(c)) {
			add_char(builder, c);
			complete_symbol(file, builder);
		} else {
			add_char(builder, c);
			while(c >= '0' && c <= '9'
					? ((c = fgetc(file)) != ' ' && (c == '.' || !is_symbol(c)))
					: (c = fgetc(file)) != ' ' && !is_symbol(c)) {
				if(c == EOF) break;
				add_char(builder, c);
			}
			if(is_symbol(c)) ungetc(c, file);
		}
		add_char(builder, '\0');
		list_add(tokens, builder->text);
	}
}

/** Completes multi-symbol tokens, has no effect on everything else. */
void complete_symbol(FILE *file, text_builder *builder) {
	if(builder->length == 0) return;

	char c = builder->text[builder->length - 1];
	switch(c) {
		case '&':
		case '|':
		case '=':
		case '<':
		case '>':;
			// Check for double up
			char next = fgetc(file);
			if(next == c || (c == '>' || c == '<') && next == '=') {
				add_char(builder, next);
			} else {
				ungetc(next, file);
			}
			break;
		case '\'':
		case '"':
			read_string(file, builder, c);
			add_char(builder, c);
			break;
		default: break;
	}
}

/** Reads a given number of hexidecimal digits from the file.
    @param dest The destination to read pairs of digits into as bytes
    @return the number of digits successfully read */
int read_hex(FILE *file, uint8_t *dest, int digits) {
	char c;
	int i, j, move = 1;

	for(i = 0, j = -1; i < digits; i++, move = !move) {
		if(move) dest[++j] = 0;
		else dest[j] <<= 4;

		c = fgetc(file);
		if(c == EOF) {
			return i;
		} else if(c >= '0' && c <= '9') {
			dest[j] |= c - '0';
		} else {
			c &= ~0x20; // Convert to uppercase
			if(c >= 'A' && c <= 'F') {
				dest[j] |= c - 'A' + 10;
			} else {
				return i;
			}
		}
	}
	return digits;
}

char get_escape(FILE *file) {
	char c = fgetc(file);
	if(c == EOF) return '\0';
	switch(c) {
		case 'a': c = '\a'; break;
		case 'b': c = '\b'; break;
		case 'f': c = '\f'; break;
		case 'n': c = '\n'; break;
		case 'r': c = '\r'; break;
		case 't': c = '\t'; break;
		case 'v': c = '\v'; break;
		case 'x': if(!read_hex(file, (uint8_t *)&c, 2)) {c = '\0';} break;
		default: break;
	}
	return c;
}

void read_string(FILE *file, text_builder *builder, const char quote) {
	char c;
	for(; (c = fgetc(file)) != EOF && c != quote;) {
		switch(c) {
			case '\\':
				c = get_escape(file);
				if(!c) return;
				// No break
			default:
				add_char(builder, c);
		}
	}
}

char read_char(FILE *file) {
	char c = fgetc(file);
	if(c == '\\') {
		c = get_escape(file);
	}
	return c;
}

void add_char(text_builder *builder, const char c) {
	if(builder->length >= builder->capacity) {
		builder->capacity <<= 1;
		builder->text = realloc(builder->text, builder->capacity);
	}
	builder->text[builder->length] = c;
	builder->length += 1;
}
