# loxpp
A C++ port of [jlox](https://github.com/munificent/craftinginterpreters/tree/master/java/com/craftinginterpreters), a reference tree-walk interpreter for [Bob Nystrom](http://github.com/munificent/)'s Lox programming language.

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

loxpp is mostly interface-compliant with jlox.
The biggest difference is when it comes to memory management - jlox relies on the JVM for memory management, but I haven't gotten around to implementing a garbage collector for loxpp.

Other than that, some error messages are different, and no native functions are implemented yet.
