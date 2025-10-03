# Quick Reference Card - gprof Profiling

## 🚀 Getting Started (3 Steps)

1. **Reopen in Dev Container**
   - Press `Ctrl+Shift+P` (or `Cmd+Shift+P` on Mac)
   - Type "Dev Containers: Reopen in Container"
   - Wait for container to build (first time only)

2. **Compile and Run**
   ```bash
   make profile-example1
   ```

3. **View Results**
   ```bash
   cat profile-example1.txt | less
   ```

## 📋 Common Commands

| Command | Description |
|---------|-------------|
| `make` | Compile all examples |
| `make example1` | Compile specific example |
| `make run-example1` | Run example without profiling |
| `make profile-example1` | Run and generate profile report |
| `make valgrind-example4` | Check memory with Valgrind |
| `make clean` | Remove build files |
| `make help` | Show all available commands |

## 📊 Reading gprof Output

### Flat Profile
```
  %   cumulative   self              self     total           
 time   seconds   seconds    calls  ms/call  ms/call  name    
 60.00      0.12     0.12  1000000     0.00     0.00  is_prime
```
- **60.00** = This function uses 60% of total time
- **1000000 calls** = Called 1 million times
- **Focus on high % time** = Optimize these first!

### Call Graph
```
[2]     90.0    0.06      0.12       1         count_primes
                0.12      0.00 1000000/1000000     is_prime
```
- `count_primes` calls `is_prime` 1 million times
- Optimize `is_prime` to speed up `count_primes`

## 🎯 Examples Explained

| Example | What it Does | Key Learning |
|---------|--------------|--------------|
| `example1.c` | Find prime numbers | Nested loops, O(n²) complexity |
| `example2.c` | Fibonacci recursive vs iterative | Exponential vs linear time |
| `example3.cpp` | Bubble Sort vs Quick Sort | O(n²) vs O(n log n) |
| `example4.cpp` | Memory allocations | Valgrind memory analysis |

## 💡 Tips

- ✅ Always profile before optimizing
- ✅ Focus on the top 3 bottlenecks
- ✅ Re-profile after changes to verify improvement
- ❌ Don't optimize functions that take < 5% of time
- ❌ Don't trust intuition - measure!

## 🔧 Manual Profiling (Advanced)

```bash
# 1. Compile with -pg flag
gcc -pg -g myprogram.c -o myprogram

# 2. Run the program
./myprogram

# 3. Generate profile
gprof myprogram gmon.out > profile.txt

# 4. View profile
less profile.txt
```

## 📚 Need More Help?

- Read `README.md` for detailed instructions
- Read `lab-guide.md` for profiling concepts
- Check exercises in `lab-guide.md`

## ⚡ Quick Optimization Workflow

```
1. Profile          → make profile-example1
2. Find bottleneck  → Look at % time column
3. Optimize code    → Edit src/example1.c
4. Re-profile       → make clean && make profile-example1
5. Compare results  → Did it improve?
```

---

**Remember:** *Premature optimization is the root of all evil. Measure first!* 📊
