
# push_swap

## 📝 Overview
**push_swap** is a 42 School algorithmic project.<br>
The objective is simple:
* Sort a stack of integers using a limited set of operations
* Aim to minimize the total number of moves
* Display the generated move sequence on the terminal

The project forces a deep understanding of algorithm complexity, sorting optimization, and strict memory/input constraints.

### 📌 Rules & Constraints
* **Two Stacks:** Sorting is performed using stack A (initially filled with inputs) and stack B (initially empty).
* **Allowed Operations:** Only specific actions are allowed:
    * `pa`, `pb` - push to opposite stack
    * `sa`, `sb`, `ss` - swap top elements
    * `ra`, `rb`, `rr` - rotate stack: all values move upwards
    * `rra`, `rrb`, `rrr` - reverse rotate stack: all values move downwards
* **Standard Library Limits:**
    * No pre-existing sorting functions are allowed.
    * The only permitted system calls are: `malloc(),` `free(),` `write()` and `exit()`.

### 🧹 Input Handling
The program strictly checks for malformed arguments.<br>
It throws an `Error` to `stderr` and terminates safely, whenever it encounters:
* Duplicate values
* Integer overflows / underflows (beyond the range of `int`)
* Non-integer inputs and unexpected characters
* Empty string arguments (`""`) or blank strings containing only whitespace

---

## 🏆 Benchmarks
All values below represent *worst case performance*, i.e.: upper bound of moves executed.

| Input Size | Max Moves Required |
| :---- | :---- |
| *Already Sorted* | 0 |
| *3 integers* | 2 |
| *5 integers* | 10 |
| *100 integers* | 670 |
| *500 integers* | 4700 |

---
## 🚀 Getting Started

### ⚙️ Compilation
Compile the executable using the provided `Makefile`:
```bash
make
```

### 💻 Usage
Run the binary by passing a list of space separated integers:
```
./bin/push_swap 2 7 -4 -23 1233 0 -999 42
```
To measure the number of moves executed by the sorting sequence, pipe the program's
output into the line count utility:
```
./bin/push_swap 2 7 -4 -23 1233 0 -999 42 | wc -l
```


---

## 🧠 Implementation Strategy
* **Data Structure:** Built using an optimized **circular buffer** array for both
stacks, avoiding the allocation and speed overhead of doubly linked lists.
* **Minimal Allocations:** Only two dynamic memory allocation calls are made
during execution - one heap block per stack.
* **Index Normalization:** Before sorting, values are mapped to normalized
indices (from `0` to `N - 1`) by quick-sorting a temporary duplicate array. This
simplifies comparison logic.
* **Three-way Quicksort Block Splitting:**
    * Employs a 2-pivot partition strategy, splitting the main stack into 3 separate
    chunks: *bottom of A*, *top of B* and *bottom of B*.
    * Recursively split each block until sub-chunks reach a small, easily sortable state.
* **Targeted Optimizations:** For stacks of up to 3 values

---

## 🧪 Testing
The `test/` directory contains three distinct bash testing scripts to validate
performance, memory management and input validation:
* `testing_script.sh`: Comprehensive testing suite for edge-case boundaries,
overflows, invalid inputs and stacks of various sizes.
* `testing_script_count_lines.sh` Allowing to verify move count across different
stacks, using a random `bash` generator.
* ```linux_memcheck_testing_script.sh``` Memory validation script running the
tests through Valgrind, to ensure absence of memory leaks.
```bash
# replace 'placeholder' with your tester of choice (redirecting to a file is recommended for long output)
./test/placeholder.sh > output_file 2>&1
```
💡*Note: If running on macOS, ensure* GNU `coreutils` *are installed* (`brew install coreutils`)

---

## 🧑🏻‍💻 Key Learnings
As one of my earliest core programming challenges, this fascinating project has helped me
build many of the foundations of my development practices. Among the learned aspects:
* Careful handling null-terminated C strings
* Hardening edge-case intuition
* Manipulating advanced pointer arrays and structs
* Managing modular multi-file setups
* Rigorous code refactoring
* Data structures: ***stack*** and ***circular buffer***
* Sorting algorithms
* Recursion complexity
* Basics of bash scripting


### 🛠️ Future Refinements
Further optimizations can still be brought, producing even better results.<br>
For example, here are some of the adjustments that are yet to be explored:
* Find a way to incorporate cheaper moves such as 'ss', 'rr' & 'rrr'
* Add more comparisons, which are *free* in *push_swap* terms
* Avoid splitting small chunks into 3
* Search for more ideal pivots for splitting

### 📚 Resources
* [push_swap in less than 4,200 operations](https://medium.com/@ulysse.gks/push-swap-in-less-than-4200-operations-c292f034f6c0) -
Detailed breakdown of the multi-pivot chunk technique
* [Circular Buffers, explained!](https://en.wikipedia.org/wiki/Circular_buffer) -
Wikipedia reference for understanding array-based queues

*Developed as part of the 42 School Curriculum.*
