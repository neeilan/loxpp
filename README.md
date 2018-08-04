# loxpp
C++ port of [jlox](https://github.com/munificent/craftinginterpreters/tree/master/java/com/craftinginterpreters), a reference tree-walk interpreter for [Bob Nystrom](http://github.com/munificent/)'s Lox programming language.

## Features
loxpp is designed to be interface-compliant with jlox. In addition to standard Lox [syntax and semantics](https://github.com/munificent/craftinginterpreters/tree/master/test/), loxpp supports additional features such as:
### Lambda expressions <sup>[commit](https://github.com/neeilan/loxpp/commit/0850ed63127297f3cff3532df2be1afc23ccb6d2)</sup>
loxpp adds support for anonymous/lambda functions, using the following syntax:
```
lambda (args...) { body }
```
See examples of lambda usage [here](https://github.com/neeilan/loxpp/blob/master/test/simple_lambdas.lox).

### Multi-line comments <sup>[commit](https://github.com/neeilan/loxpp/commit/621301fad503525c9c362d7a4fa6927004384181)</sup>
C++ (Clang) style non-nested multi-line comments are supported:
```
/* Multi
 * line
 * comment 1 */

var x = "Multiline comments!";

/* Il$$3g^l
   charac%ers '\ */

print x;
```

## Build

Requirements:
- A C++11 compiler (can be set via the `CC` option in Makefile)
- Python, if you wish to run functional tests

Using the provided Makefile:
```bash
make          # builds the loxpp executable at ./bin
make test     # runs functional tests
```

Using CMake:

`CMakeLists.txt` is also provided, but for building the executable only.


## Usage
```
./bin/loxpp          # enter REPL
./bin/loxpp <file>   # run file
```

The biggest divergence from jlox is when it comes to memory management - jlox relies on the JVM for loose object cleanup, but I haven't gotten around to implementing a garbage collector for loxpp. Other than that, error messages are slightly different, and the native `clock` function is not yet implemented.
