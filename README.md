# Pseudo-C

A school project written as the artefact complimenting an extended project on programming language design. This language is interpreted and heavily resembles C, but is much simpler.

The GPIO functions are designed to work on a Raspberry Pi and were tested on a Pi 2 Model B.

## Building
Running `make` in the project root will invoke the provided [`Makefile`](Makefile). The generated binary is `bin/pseudoc` (`.exe` on windows).
- `make` or `make all` will build the program
- `make clean` will remove the binary and the `bin` folder
- `make clean all` will rebuild the program even if no sources have been changed

## Running the examples
To run a program, just call the executable as follows:

    ./bin/pseudoc [SOURCE FILE]

The example programs are stored in the [`examples`](examples) directory.

## Writing your own programs
The examples should be sufficient to understand the syntax of the language. C programmers will be familiar.

### Data types
The language only has numeric types, no strings or classes. The names of the types follow the same scheme as C's `stdint.h`:

Type name | Data
----------|------------------------
int8      | Signed 8-bit integer
int16     | Signed 16-bit integer
int32     | Signed 32-bit integer
int64     | Signed 64-bit integer
uint8     | Unsigned 8-bit integer
uint16    | Unsigned 16-bit integer
uint32    | Unsigned 32-bit integer
uint64    | Unsigned 64-bit integer
float     | 32-bit floating point
double    | 64-bit floating point

Within expressions, all types will be converted implicitly to either `int64` or `float64`, evaluated then converted to the store type.

### Built-in functions
The language supports:
- Mathematical functions such as `sin`, `cos` and `radians`
- A timing function sleep, whose one parameter is milliseconds
- Functions `exportpin`, `directpin`, `writepin` and `unexportpin` for using GPIO
- A function `print` to output a single number to the screen

User-defined functions are not supported, all functions must be built into the executable.

### Operators
Operator precedence is similar to C. Binary conditions output `0` or `1`. \
In conditionals, there are no short-circuit `||` or `&&` operators, so you must use `|` and `&` for the same purpose.

Operator | Purpose
---------|-------------------------------
`==`     | Equality test
`>=`     | Greater than or equal to
`<=`     | Less than or equal to
`>`      | Greater than
`<`      | Less than
`!=`     | Not equal to
`|`      | Logical OR
`&`      | Logical AND
`<<`     | Bit shift left
`>>`     | Bit shift right
`+`      | Add
`-`      | Subtract
`*`      | Multiply
`/`      | Divide
`^`      | Power
