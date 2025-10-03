# C/C++ Program Profiling Lab with gprof

A hands-on educational project for learning program profiling in C and C++ using `gprof`, set up in a VS Code devcontainer for cross-platform compatibility.

## 📚 What You'll Learn

- How to compile programs with profiling enabled
- How to use `gprof` to analyze program performance
- How to interpret flat profiles and call graphs
- How to identify performance bottlenecks
- How to use Valgrind for memory profiling
- Best practices for optimization

## 🚀 Quick Start

### Prerequisites

- [Visual Studio Code](https://code.visualstudio.com/)
- [Docker Desktop](https://www.docker.com/products/docker-desktop/)
- [Dev Containers extension](https://marketplace.visualstudio.com/items?itemName=ms-vscode-remote.remote-containers) for VS Code

### Opening the Project

1. **Clone this repository:**
   ```bash
   git clone https://github.com/ahcheriet/profiling-lab.git
   cd profiling-lab
   ```

2. **Open in VS Code:**
   ```bash
   code .
   ```

3. **Reopen in Container:**
   - VS Code will detect the devcontainer configuration
   - Click "Reopen in Container" when prompted
   - Or use Command Palette (`Ctrl+Shift+P` / `Cmd+Shift+P`) → "Dev Containers: Reopen in Container"

4. **Wait for container to build:**
   - First time setup takes a few minutes
   - The container installs GCC, gprof, Valgrind, and other tools
   - Subsequent starts are much faster

## 📁 Project Structure

```
profiling/
├── .devcontainer/
│   ├── devcontainer.json    # VS Code devcontainer configuration
│   └── Dockerfile            # Container with GCC, gprof, Valgrind
├── src/
│   ├── example1.c            # Inefficient prime number detection
│   ├── example2.c            # Recursive vs iterative Fibonacci
│   ├── example3.cpp          # Bubble Sort vs Quick Sort
│   └── example4.cpp          # Memory allocation patterns
├── Makefile                  # Build and profiling automation
├── README.md                 # This file
└── lab-guide.md              # Detailed profiling concepts and exercises
```

## 🛠️ How to Use

### Step 1: Compile a Program with Profiling

All programs are compiled with the `-pg` flag for profiling support:

```bash
make example1
```

Available examples:
- `make example1` - Prime number detection (nested loops)
- `make example2` - Fibonacci (recursive vs iterative)
- `make example3` - Sorting algorithms comparison
- `make example4` - Memory allocation patterns

Or compile all at once:
```bash
make
```

### Step 2: Run the Program

Running the program generates a `gmon.out` file containing profiling data:

```bash
make run-example1
```

Or run the executable directly:
```bash
./build/example1
```

After execution, you'll see `gmon.out` in your directory.

### Step 3: Generate and View the Profile Report

Use `gprof` to analyze the profiling data:

```bash
make profile-example1
```

This will:
1. Run the program (generating `gmon.out`)
2. Generate a profile report using `gprof`
3. Save the report to `profile-example1.txt`

View the report:
```bash
cat profile-example1.txt | less
```

Or open it in VS Code:
```bash
code profile-example1.txt
```

### Step 4: Interpret the Results

The `gprof` output contains two main sections:

#### **Flat Profile**
Shows where the program spends its time:

```
  %   cumulative   self              self     total           
 time   seconds   seconds    calls  ms/call  ms/call  name    
 60.00      0.12     0.12    10000     0.01     0.01  is_prime
 30.00      0.18     0.06        1    60.00   180.00  count_primes
 10.00      0.20     0.02                             main
```

- **% time**: Percentage of total runtime
- **self seconds**: Time spent in this function only
- **calls**: Number of times the function was called
- **name**: Function name

#### **Call Graph**
Shows which functions call which:

```
index % time    self  children    called     name
[1]    90.0    0.06      0.12       1         count_primes [1]
                0.12      0.00   10000/10000     is_prime [2]
-----------------------------------------------
                0.12      0.00   10000/10000     count_primes [1]
[2]    60.0    0.12      0.00   10000         is_prime [2]
```

This helps identify which calling patterns are expensive.

## 🎯 Example Workflows

### Example 1: Finding Prime Numbers

```bash
# Compile with profiling
make example1

# Run and profile
make profile-example1

# View the report
cat profile-example1.txt | less
```

**What to look for:**
- `is_prime` should consume most of the time
- Notice the inefficient algorithm checking divisibility up to `n-1`

### Example 2: Recursive vs Iterative Fibonacci

```bash
make profile-example2
cat profile-example2.txt | less
```

**What to look for:**
- Massive number of calls to `fibonacci_recursive`
- Exponential time complexity evident in call count
- Compare with `fibonacci_iterative` efficiency

### Example 3: Sorting Algorithm Comparison

```bash
make profile-example3
cat profile-example3.txt | less
```

**What to look for:**
- `bubble_sort` vs `quick_sort` time comparison
- O(n²) vs O(n log n) performance difference

### Example 4: Memory Profiling with Valgrind

```bash
# Compile
make example4

# Run with Valgrind
make valgrind-example4
```

**What to look for:**
- Memory leaks (if any)
- Allocation/deallocation patterns
- Memory usage statistics

## 🔧 Advanced Usage

### Manual Profiling Steps

If you want to do it manually:

```bash
# 1. Compile with -pg flag
gcc -Wall -pg -g src/example1.c -o build/example1

# 2. Run the program
./build/example1

# 3. Generate profile report
gprof build/example1 gmon.out > profile.txt

# 4. View the report
less profile.txt
```

### Profiling with Different Optimization Levels

Compare profiling results with different optimization flags:

```bash
# No optimization (default)
gcc -pg -g src/example1.c -o build/example1_O0

# With -O2 optimization
gcc -pg -g -O2 src/example1.c -o build/example1_O2

# Run both and compare
./build/example1_O0
gprof build/example1_O0 gmon.out > profile_O0.txt

./build/example1_O2
gprof build/example1_O2 gmon.out > profile_O2.txt
```

### Using Valgrind for More Detailed Analysis

```bash
# Memory leak check
valgrind --leak-check=full ./build/example4

# Cache profiling
valgrind --tool=cachegrind ./build/example3

# Call graph profiling (alternative to gprof)
valgrind --tool=callgrind ./build/example1
kcachegrind callgrind.out.*  # Requires kcachegrind installation
```

## 📖 Learning Resources

- **[lab-guide.md](lab-guide.md)** - Comprehensive guide to profiling concepts
- **GNU gprof Manual:** [https://sourceware.org/binutils/docs/gprof/](https://sourceware.org/binutils/docs/gprof/)
- **Valgrind Documentation:** [https://valgrind.org/docs/manual/quick-start.html](https://valgrind.org/docs/manual/quick-start.html)

## 🎓 Exercises

See [lab-guide.md](lab-guide.md) for detailed exercises including:

1. Optimize the prime number detection algorithm
2. Profile before and after optimization
3. Compare recursive vs iterative approaches
4. Analyze sorting algorithm performance
5. Detect and fix memory leaks

## 🧹 Cleanup

Remove build artifacts:
```bash
make clean
```

Remove profile reports:
```bash
make clean-profiles
```

Remove everything:
```bash
make clean-all
```

## 📝 Notes

- The `-pg` flag enables profiling but adds overhead (~10-30%)
- Always profile with realistic workloads
- Profiling results may vary between runs
- The devcontainer ensures consistent results across different host OSes

## 🤝 Contributing

Contributions are welcome! Feel free to:
- Add more example programs
- Improve documentation
- Fix bugs
- Suggest new exercises

## 📄 License

This project is open source and available for educational purposes.

---

**Happy Profiling! 🚀**
