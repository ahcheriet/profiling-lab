# Compiler and flags
CC = gcc
CXX = g++
CFLAGS = -Wall -pg -g
CXXFLAGS = -Wall -pg -g
LDFLAGS = -pg
MATHLIB = -lm

# Source directory
SRC_DIR = src

# Build directory
BUILD_DIR = build

# Executable names
EXAMPLE1 = $(BUILD_DIR)/example1
EXAMPLE2 = $(BUILD_DIR)/example2
EXAMPLE3 = $(BUILD_DIR)/example3
EXAMPLE4 = $(BUILD_DIR)/example4
EXAMPLE5 = $(BUILD_DIR)/example5
EXAMPLE6 = $(BUILD_DIR)/example6
EXAMPLE7 = $(BUILD_DIR)/example7
EXAMPLE8 = $(BUILD_DIR)/example8

# Default target
.PHONY: all
all: $(BUILD_DIR) $(EXAMPLE1) $(EXAMPLE2) $(EXAMPLE3) $(EXAMPLE4) $(EXAMPLE5) $(EXAMPLE6) $(EXAMPLE7) $(EXAMPLE8)
	@echo "All examples compiled successfully!"
	@echo "Use 'make help' to see available targets."

# Create build directory
$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

# Compile example1
$(EXAMPLE1): $(SRC_DIR)/example1.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) $< -o $@ $(LDFLAGS)

# Compile example2
$(EXAMPLE2): $(SRC_DIR)/example2.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) $< -o $@ $(LDFLAGS)

# Compile example3
$(EXAMPLE3): $(SRC_DIR)/example3.cpp | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) $< -o $@ $(LDFLAGS)

# Compile example4
$(EXAMPLE4): $(SRC_DIR)/example4.cpp | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) $< -o $@ $(LDFLAGS)

# Compile example5
$(EXAMPLE5): $(SRC_DIR)/example5.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) $< -o $@ $(LDFLAGS)

# Compile example6
$(EXAMPLE6): $(SRC_DIR)/example6.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) $< -o $@ $(LDFLAGS)

# Compile example7
$(EXAMPLE7): $(SRC_DIR)/example7.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) $< -o $@ $(LDFLAGS)

# Compile example8
$(EXAMPLE8): $(SRC_DIR)/example8.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) $< -o $@ $(LDFLAGS) $(MATHLIB)

# Individual compile targets
.PHONY: example1 example2 example3 example4 example5 example6 example7 example8
example1: $(EXAMPLE1)
	@echo "Example 1 compiled: $(EXAMPLE1)"

example2: $(EXAMPLE2)
	@echo "Example 2 compiled: $(EXAMPLE2)"

example3: $(EXAMPLE3)
	@echo "Example 3 compiled: $(EXAMPLE3)"

example4: $(EXAMPLE4)
	@echo "Example 4 compiled: $(EXAMPLE4)"

example5: $(EXAMPLE5)
	@echo "Example 5 compiled: $(EXAMPLE5)"

example6: $(EXAMPLE6)
	@echo "Example 6 compiled: $(EXAMPLE6)"

example7: $(EXAMPLE7)
	@echo "Example 7 compiled: $(EXAMPLE7)"

example8: $(EXAMPLE8)
	@echo "Example 8 compiled: $(EXAMPLE8)"

# Run targets
.PHONY: run-example1 run-example2 run-example3 run-example4 run-example5 run-example6 run-example7 run-example8
run-example1: $(EXAMPLE1)
	@echo "Running Example 1..."
	@./$(EXAMPLE1)

run-example2: $(EXAMPLE2)
	@echo "Running Example 2..."
	@./$(EXAMPLE2)

run-example3: $(EXAMPLE3)
	@echo "Running Example 3..."
	@./$(EXAMPLE3)

run-example4: $(EXAMPLE4)
	@echo "Running Example 4..."
	@./$(EXAMPLE4)

run-example5: $(EXAMPLE5)
	@echo "Running Example 5..."
	@./$(EXAMPLE5)

run-example6: $(EXAMPLE6)
	@echo "Running Example 6..."
	@./$(EXAMPLE6)

run-example7: $(EXAMPLE7)
	@echo "Running Example 7..."
	@./$(EXAMPLE7)

run-example8: $(EXAMPLE8)
	@echo "Running Example 8..."
	@./$(EXAMPLE8)

# Profile targets (run program and generate gprof report)
.PHONY: profile-example1 profile-example2 profile-example3 profile-example4 profile-example5 profile-example6 profile-example7 profile-example8
profile-example1: $(EXAMPLE1)
	@echo "Profiling Example 1..."
	@./$(EXAMPLE1)
	@gprof $(EXAMPLE1) gmon.out > profile-example1.txt
	@echo "Profile saved to profile-example1.txt"
	@echo "View with: cat profile-example1.txt | less"

profile-example2: $(EXAMPLE2)
	@echo "Profiling Example 2..."
	@./$(EXAMPLE2)
	@gprof $(EXAMPLE2) gmon.out > profile-example2.txt
	@echo "Profile saved to profile-example2.txt"
	@echo "View with: cat profile-example2.txt | less"

profile-example3: $(EXAMPLE3)
	@echo "Profiling Example 3..."
	@./$(EXAMPLE3)
	@gprof $(EXAMPLE3) gmon.out > profile-example3.txt
	@echo "Profile saved to profile-example3.txt"
	@echo "View with: cat profile-example3.txt | less"

profile-example4: $(EXAMPLE4)
	@echo "Profiling Example 4..."
	@./$(EXAMPLE4)
	@gprof $(EXAMPLE4) gmon.out > profile-example4.txt
	@echo "Profile saved to profile-example4.txt"
	@echo "View with: cat profile-example4.txt | less"

profile-example5: $(EXAMPLE5)
	@echo "Profiling Example 5 (Matrix Multiplication)..."
	@./$(EXAMPLE5)
	@gprof $(EXAMPLE5) gmon.out > profile-example5.txt
	@echo "Profile saved to profile-example5.txt"
	@echo "View with: cat profile-example5.txt | less"

profile-example6: $(EXAMPLE6)
	@echo "Profiling Example 6 (Search Algorithms)..."
	@./$(EXAMPLE6)
	@gprof $(EXAMPLE6) gmon.out > profile-example6.txt
	@echo "Profile saved to profile-example6.txt"
	@echo "View with: cat profile-example6.txt | less"

profile-example7: $(EXAMPLE7)
	@echo "Profiling Example 7 (String Processing)..."
	@./$(EXAMPLE7)
	@gprof $(EXAMPLE7) gmon.out > profile-example7.txt
	@echo "Profile saved to profile-example7.txt"
	@echo "View with: cat profile-example7.txt | less"

profile-example8: $(EXAMPLE8)
	@echo "Profiling Example 8 (Computational Geometry)..."
	@./$(EXAMPLE8)
	@gprof $(EXAMPLE8) gmon.out > profile-example8.txt
	@echo "Profile saved to profile-example8.txt"
	@echo "View with: cat profile-example8.txt | less"

# Valgrind memory analysis targets
.PHONY: valgrind-example4
valgrind-example4: $(EXAMPLE4)
	@echo "Running Valgrind memory check on Example 4..."
	@valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose ./$(EXAMPLE4)

# Clean targets
.PHONY: clean clean-profiles
clean:
	rm -rf $(BUILD_DIR)
	rm -f gmon.out
	@echo "Build directory cleaned."

clean-profiles:
	rm -f profile-*.txt gmon.out
	@echo "Profile files cleaned."

clean-all: clean clean-profiles
	@echo "All build artifacts and profiles cleaned."

# Help target
.PHONY: help
help:
	@echo "Available targets:"
	@echo "  make                  - Compile all examples"
	@echo ""
	@echo "C Examples (simpler profiling output):"
	@echo "  make example1         - Compile example1 (prime numbers)"
	@echo "  make example2         - Compile example2 (Fibonacci)"
	@echo "  make example5         - Compile example5 (matrix multiplication)"
	@echo "  make example6         - Compile example6 (search algorithms)"
	@echo "  make example7         - Compile example7 (string processing)"
	@echo "  make example8         - Compile example8 (computational geometry)"
	@echo ""
	@echo "C++ Examples:"
	@echo "  make example3         - Compile example3 (sorting algorithms)"
	@echo "  make example4         - Compile example4 (memory allocations)"
	@echo ""
	@echo "Run examples:"
	@echo "  make run-example1     - Run example1"
	@echo "  make run-example2     - Run example2"
	@echo "  make run-example3     - Run example3"
	@echo "  make run-example4     - Run example4"
	@echo "  make run-example5     - Run example5"
	@echo "  make run-example6     - Run example6"
	@echo "  make run-example7     - Run example7"
	@echo "  make run-example8     - Run example8"
	@echo ""
	@echo "Profile examples:"
	@echo "  make profile-example1 - Profile example1 with gprof"
	@echo "  make profile-example2 - Profile example2 with gprof"
	@echo "  make profile-example3 - Profile example3 with gprof"
	@echo "  make profile-example4 - Profile example4 with gprof"
	@echo "  make profile-example5 - Profile example5 with gprof"
	@echo "  make profile-example6 - Profile example6 with gprof"
	@echo "  make profile-example7 - Profile example7 with gprof"
	@echo "  make profile-example8 - Profile example8 with gprof"
	@echo ""
	@echo "Other targets:"
	@echo "  make valgrind-example4 - Run Valgrind memory check on example4"
	@echo ""
	@echo "Cleanup:"
	@echo "  make clean            - Remove build directory"
	@echo "  make clean-profiles   - Remove profile output files"
	@echo "  make clean-all        - Remove all build artifacts"
	@echo "  make help             - Show this help message"
