# Scanner

## Compilers - P1

**Implemented Option 3 -> Table & Driver**

**Version Control**:
GitHub repo: https://github.com/STLnick/scanner

---

!! TODO: UPDATE file with new project names / run commands !!

- Will be building one exe - testScanner
- scanner() will be called inside that testing executable
- scanner() is our actual scanner logic - i.e. the real project

---

**To run the program**:
First run 'make' in the root of the project to build 'P0'. The executable `P0` is built and placed in `/bin`.

At the same location in the project folders you can just run `./bin/P0`
Or you can execute `cd ./bin` and then run `./P0`

**Run command structure**:

> In each case `[file]` will be read in 'word by word' (whitespaces separate what's read in).

> `[file]` _must have the extension of_ `.sp2020`.
> - for example `test1.sp2020`, `text.sp2020`, `whatever.sp2020`

`./P0`

- read from the keyboard until simulated EOF (Command to type to simulate EOF -> *nix: ctrl+d, windows: ctrl+z)

`./P0 < [file]`

- redirect from `[file]` until EOF

`./P0 [file]` or `./P0 [file].sp2020`

- read from `[file].sp2020`

`./P0 -h`

- help

---

**What Works**:

**What Doesn't Work**:
