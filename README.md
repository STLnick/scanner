# Scanner

## Compilers - P1

**Implemented Option 3 -> Table & Driver**

**Version Control**:
GitHub repo: https://github.com/STLnick/scanner

---

**To run the program**:
First run 'make' in the root of the project to build 'scanner'. The executable `scanner` is built and placed in `/bin`.

At the same location in the project folders you can just run `./bin/scanner`
Or you can execute `cd ./bin` and then run `./scanner`

**Run command structure**:

> In each case `[file]` will be read in 'word by word' (whitespaces separate what's read in).

> `[file]` _must have the extension of_ `.fs`.
> - for example `test1.fs`, `text.fs`, `whatever.fs`

`./scanner`

- read from the keyboard until simulated EOF (Command to type to simulate EOF -> *nix: ctrl+d, windows: ctrl+z)

`./scanner < [file]`

- redirect from `[file]` until EOF

`./scanner [file]` or `./scanner [file].fs`

- read from `[file].fs`
    - **NOTE**: The files to be read from _MUST BE IN THE_ `/bin` directory with the executable

`./scanner -h`

- help


---

**What Works**:
- Parses tokens correctly
- Implements table and driver
- Skips comments
- Tracks and adds line number info to token

**What Doesn't Work**:
- Error handling isn't precise

---
### Commit Log

**b7f73d0** Cleanup dead code, comments, and some formatting

**b9d60ec** Implement line numbers in token struct

**428190d** Remove dead code from refactor

**298d1d8** Complete table driver refactor

**2a1e206** Parse separate keyword tokens from identifier tokens

**4dddd4c** Establish Table driver, transitions and State

**56c9c07** Change all header files to have the same SCANNER_ prefix

**f3927f1** Move init function to separate file and include in main

**c99107c** Cleanup main formatting, structure and add a few comments

**242f79c** Add comment for clarity of switch statement purpose

**5f3ce0d** Refactor skipping comments into a function

**928b96a** Skip comments in source code

**b51b4d3** Improve description of keywords

**c58341a** Add keywords into the parsing done by the scanner

**6443bf5** Correct 'issue' - need test files to be in same directory as exe

**b8398a5** Adjust showHelp messaging for scanner project from P0

**136c03c** Bring in command line parsing code from P0

**261313c** Parse double character operators/delimiters

**bcdbc8b** Add colon equals operator

**271b094** Implement remaining single character operators/delimiters parsing

**19577c7** Improve readability of token info output

**526be9a** Parse plus, minus, multiplication and division signs

**c796208** Change error text to match Project Description

**4521ffc** Run CLion file formatter on project

**5d4d44f** Parse assignment operator and semicolon

**79282ef** Define functions to advance scanner and return a new token

**3d26b1f** Parse an identifier from a text file

**fb817f3** Remove old, dead code from working and testing

**976ec63** Define and utilize function to skip whitespace

**6e3a2ca** Scan and print a NUM and EOF token

**1aa7243** Define method to lookahead

**bb5ce7b** Add EOF token

**ad86a3b** Define method to pretty print a token from scanner

**5b656d0** Remove lineNum from TokenRecord temporarily

**4e7c715** Refactor scanner to use a string for src instead of file stream

**a88bc6c** Test by outputting source file content through scanner in loop

**cf3ff92** Include library for malloc

**5013110** Write method to advance scanner

**9dd2d21** Initialize scanner with source file stream

**0c06928** Define scanner struct

**ccb6673** Remove comments

**e3e7fae** Add starter files for scanner

**62e7f6a** Mock up initializing a token with values

**07db7bf** Write basic init function for a token

**87f6b96** Setup struct for TokenRecord with type enum

**886221d** Make project specific changes to Makefile

**7690a3f** Remove unnecessary README

**7baabef** Add general format of project README with TODOs

**154d2bb** Initial commit
