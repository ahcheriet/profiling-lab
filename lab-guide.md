# Lab Guide: Understanding Program Profiling with gprof

## 📚 Table of Contents

1. [Introduction to Profiling](#introduction-to-profiling)
2. [Instrumentation vs Sampling](#instrumentation-vs-sampling)
3. [Understanding gprof Output](#understanding-gprof-output)
4. [Debug vs Release Builds](#debug-vs-release-builds)
5. [Practical Exercises](#practical-exercises)
6. [Common Pitfalls](#common-pitfalls)
7. [Advanced Topics](#advanced-topics)

---

## Introduction to Profiling

**Program profiling** is the process of measuring where a program spends its time and resources during execution. This is crucial for:

- **Performance Optimization**: Identify bottlenecks before optimizing
- **Understanding Behavior**: See which functions are called and how often
- **Resource Management**: Detect memory leaks and inefficient allocations
- **Validation**: Ensure optimizations actually improve performance

### Why Profile?

> "Premature optimization is the root of all evil." — Donald Knuth

Always **measure before optimizing**. Your intuition about performance bottlenecks is often wrong!

### Types of Profiling

1. **CPU Profiling**: Time spent in each function (gprof)
2. **Memory Profiling**: Allocation patterns and leaks (Valgrind)
3. **Cache Profiling**: CPU cache usage (Cachegrind)
4. **I/O Profiling**: Disk and network operations

---

## Instrumentation vs Sampling

### Instrumentation-based Profiling (gprof)

**How it works:**
- Compiler inserts extra code at function entry/exit
- Records every function call and execution time
- Enabled with `-pg` compiler flag

**Advantages:**
- ✅ Accurate call counts
- ✅ Complete call graph information
- ✅ Deterministic results

**Disadvantages:**
- ❌ Adds runtime overhead (~10-30%)
- ❌ Can affect program behavior
- ❌ May miss very short functions

**Example:**
```bash
gcc -pg -g myprogram.c -o myprogram
./myprogram
gprof myprogram gmon.out > analysis.txt
```

### Sampling-based Profiling (perf, VTune)

**How it works:**
- Periodically interrupts program execution
- Records current instruction pointer
- Statistical approximation of time spent

**Advantages:**
- ✅ Lower overhead (~1-5%)
- ✅ Can profile without recompilation
- ✅ Better for production systems

**Disadvantages:**
- ❌ Statistical (not exact)
- ❌ May miss infrequent operations
- ❌ Requires more samples for accuracy

---

## Understanding gprof Output

When you run `gprof program gmon.out`, you get two main sections:

### 1. Flat Profile

The flat profile shows **where time is spent**:

```
Flat profile:

Each sample counts as 0.01 seconds.
  %   cumulative   self              self     total           
 time   seconds   seconds    calls  ms/call  ms/call  name    
 60.00      0.12     0.12  1000000     0.00     0.00  is_prime
 30.00      0.18     0.06        1    60.00   180.00  count_primes
 10.00      0.20     0.02                             main
```

**Column meanings:**

| Column | Meaning |
|--------|---------|
| **% time** | Percentage of total execution time |
| **cumulative seconds** | Total time up to this function |
| **self seconds** | Time in this function only (excluding children) |
| **calls** | Number of times called |
| **self ms/call** | Average time per call (excluding children) |
| **total ms/call** | Average time per call (including children) |
| **name** | Function name |

**How to read it:**
1. Look at **% time** column - highest values are bottlenecks
2. Check **calls** - excessive calls might indicate inefficiency
3. Compare **self** vs **total** time - shows if time is in the function itself or its children

### 2. Call Graph

The call graph shows **who calls whom**:

```
index % time    self  children    called     name
                                                 <spontaneous>
[1]    100.0    0.02      0.18       0         main [1]
                0.06      0.12       1/1           count_primes [2]
-----------------------------------------------
                0.06      0.12       1/1           main [1]
[2]     90.0    0.06      0.12       1         count_primes [2]
                0.12      0.00 1000000/1000000     is_prime [3]
-----------------------------------------------
                0.12      0.00 1000000/1000000     count_primes [2]
[3]     60.0    0.12      0.00 1000000         is_prime [3]
-----------------------------------------------
```

**How to read it:**

Each function has an entry like:
```
                <callers>
[index]  %time    self  children  called     name
                <callees>
```

- **callers**: Functions that called this one
- **callees**: Functions this one called
- **self**: Time in this function only
- **children**: Time in functions it called

**Example interpretation:**

```
[2]     90.0    0.06      0.12       1         count_primes [2]
                0.12      0.00 1000000/1000000     is_prime [3]
```

This means:
- `count_primes` takes 90% of total time
- It spent 0.06s in its own code
- It spent 0.12s in `is_prime` (called 1,000,000 times)
- Optimization should focus on `is_prime`!

---

## Debug vs Release Builds

### Debug Build (Default)

```bash
gcc -pg -g src/example.c -o build/example
```

**Characteristics:**
- No optimization
- Debug symbols included
- Slower execution
- Easier to debug
- Profiling results show actual source code behavior

**Use for:**
- Development
- Initial profiling
- Debugging performance issues

### Release Build (Optimized)

```bash
gcc -pg -g -O2 src/example.c -o build/example
```

**Characteristics:**
- Compiler optimizations enabled
- Faster execution
- May inline small functions
- May reorder code
- Harder to debug

**Common optimization levels:**
- `-O0`: No optimization (default)
- `-O1`: Basic optimizations
- `-O2`: Recommended optimizations
- `-O3`: Aggressive optimizations
- `-Os`: Optimize for size

### Why Profile Both?

1. **Debug builds** show algorithmic bottlenecks
2. **Optimized builds** show real-world performance
3. Compiler may optimize away problems you're trying to measure
4. Some issues only appear with optimization (e.g., cache effects)

### Example Comparison

**Debug build (O0):**
```
 60.00   0.12   is_prime
 30.00   0.06   count_primes
 10.00   0.02   main
```

**Optimized build (O2):**
```
 50.00   0.05   is_prime     (faster, may be inlined)
 40.00   0.04   count_primes
 10.00   0.01   main
```

Notice:
- Absolute times are lower
- Relative percentages may change
- Some functions might disappear (inlined)

---

## Practical Exercises

### Exercise 1: Optimize Prime Number Detection

**Goal:** Improve the `is_prime` function in `example1.c`

**Current implementation** (inefficient):
```c
bool is_prime(int n) {
    if (n <= 1) return false;
    if (n == 2) return true;
    if (n % 2 == 0) return false;
    
    for (int i = 3; i < n; i += 2) {  // ← Checks up to n-1
        if (n % i == 0) return false;
    }
    return true;
}
```

**Steps:**

1. **Profile the original:**
   ```bash
   make profile-example1
   cat profile-example1.txt | less
   ```
   
   Note the time spent in `is_prime`.

2. **Optimize:** Only check up to √n:
   ```c
   bool is_prime(int n) {
       if (n <= 1) return false;
       if (n == 2) return true;
       if (n % 2 == 0) return false;
       
       for (int i = 3; i * i <= n; i += 2) {  // ← Only up to √n
           if (n % i == 0) return false;
       }
       return true;
   }
   ```

3. **Recompile and profile:**
   ```bash
   make clean
   make profile-example1
   cat profile-example1.txt | less
   ```

4. **Compare results:**
   - How much faster is it?
   - What's the new time breakdown?

**Expected improvement:** 10-100x speedup depending on input size!

### Exercise 2: Analyze Recursive vs Iterative Fibonacci

**Goal:** Understand why recursive Fibonacci is slow

**Steps:**

1. **Profile example2:**
   ```bash
   make profile-example2
   cat profile-example2.txt | less
   ```

2. **Examine the call graph:**
   - How many times is `fibonacci_recursive` called?
   - What about `fibonacci_iterative`?

3. **Questions to answer:**
   - Why does recursive Fibonacci have so many calls?
   - What's the time complexity of each approach?
   - Can you add memoization to improve the recursive version?

**Hint:** For `fibonacci(40)`, the recursive version calls itself ~331 million times!

### Exercise 3: Compare Sorting Algorithms

**Goal:** Visualize O(n²) vs O(n log n) performance

**Steps:**

1. **Profile example3:**
   ```bash
   make profile-example3
   cat profile-example3.txt | less
   ```

2. **Observe:**
   - Time spent in `bubble_sort` vs `quick_sort`
   - Number of comparisons/swaps

3. **Experiment:**
   - Modify the array size in `example3.cpp`
   - Try 1000, 5000, 10000 elements
   - Plot how execution time grows

4. **Challenge:**
   - Implement merge sort
   - Compare all three algorithms
   - Which is fastest? Why?

### Exercise 4: Detect Memory Issues with Valgrind

**Goal:** Find and fix memory leaks

**Steps:**

1. **Run Valgrind:**
   ```bash
   make valgrind-example4
   ```

2. **Introduce a bug:** Comment out a `free()` or `delete[]` in `example4.cpp`:
   ```cpp
   // free(buffer);  // ← Comment this out
   ```

3. **Recompile and check:**
   ```bash
   make clean
   make example4
   make valgrind-example4
   ```

4. **Observe:**
   - Valgrind reports memory leaks
   - Shows exactly where memory was allocated
   - Helps track down the bug

5. **Fix and verify:**
   - Uncomment the `free()`
   - Rerun Valgrind
   - Should show no leaks

---

## Common Pitfalls

### 1. Forgetting to Compile with -pg

**Problem:**
```bash
gcc src/example.c -o build/example
./build/example
gprof build/example gmon.out
```
**Result:** Empty or missing profile

**Solution:** Always use `-pg`:
```bash
gcc -pg src/example.c -o build/example
```

### 2. Program Too Fast to Profile

**Problem:** Program finishes in < 0.01 seconds

**Solution:**
- Increase workload (larger input)
- Run multiple iterations in a loop
- Use sampling profilers instead

### 3. Profiling the Wrong Build

**Problem:** Profiling a debug build and expecting production performance

**Solution:** Profile both, but understand the differences

### 4. Ignoring Call Counts

**Problem:** Focusing only on time percentages

**Solution:** A function called 1 million times might be worth optimizing even if each call is fast

### 5. Over-optimizing

**Problem:** Spending hours optimizing a function that takes 1% of runtime

**Solution:** Focus on the top 3-5 bottlenecks first

---

## Advanced Topics

### 1. Line-by-Line Profiling

For more detailed analysis, use `gcov`:

```bash
# Compile with coverage
gcc -pg -fprofile-arcs -ftest-coverage src/example.c -o build/example

# Run
./build/example

# Generate report
gcov src/example.c
cat example.c.gcov
```

### 2. Comparing Profiling Tools

| Tool | Type | Overhead | Detail | Use Case |
|------|------|----------|--------|----------|
| **gprof** | Instrumentation | High (10-30%) | Function-level | Development |
| **Valgrind/Callgrind** | Simulation | Very High (10-100x) | Instruction-level | Deep analysis |
| **perf** | Sampling | Low (1-5%) | Statistical | Production |
| **Intel VTune** | Sampling | Low | Hardware counters | Professional |

### 3. Profiling Multi-threaded Programs

`gprof` has limited multi-threading support. For better results:

- Use `perf` on Linux
- Use specialized tools (Intel VTune, Google Perf Tools)
- Profile each thread separately

### 4. Automated Performance Testing

Create a script to track performance over time:

```bash
#!/bin/bash
# benchmark.sh

for size in 1000 5000 10000 50000; do
    # Modify input size in code
    sed -i "s/int size = .*/int size = $size;/" src/example3.cpp
    
    # Compile and run
    make example3
    
    # Time it
    /usr/bin/time -v ./build/example3 2>&1 | grep "Elapsed"
done
```

---

## Summary

**Key Takeaways:**

1. ✅ Always **profile before optimizing**
2. ✅ Focus on **bottlenecks** (top 20% of code causing 80% of runtime)
3. ✅ Understand both **flat profile** and **call graph**
4. ✅ Compare **debug vs optimized** builds
5. ✅ Use the **right tool** for the job
6. ✅ **Measure** the impact of optimizations

**Profiling Workflow:**

```
1. Profile → 2. Identify bottleneck → 3. Optimize → 4. Re-profile → 5. Verify improvement
         ↑                                                                ↓
         └────────────────────────────────────────────────────────────────┘
```

**Remember:** The goal isn't to optimize everything, but to make the program **fast enough** for its purpose!

---

## Further Reading

- [GNU gprof Manual](https://sourceware.org/binutils/docs/gprof/)
- [Valgrind Documentation](https://valgrind.org/docs/manual/manual.html)
- [Performance Analysis Guide](https://easyperf.net/blog/)
- [Algorithms and Complexity](https://www.bigocheatsheet.com/)

---

**Happy Profiling! 🚀**
