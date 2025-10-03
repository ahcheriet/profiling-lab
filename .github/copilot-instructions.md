<!-- Use this file to provide workspace-specific custom instructions to Copilot. For more details, visit https://code.visualstudio.com/docs/copilot/copilot-customization#_use-a-githubcopilotinstructionsmd-file -->
- [x] Verify that the copilot-instructions.md file in the .github directory is created.

- [x] Clarify Project Requirements
	Project: C/C++ profiling education lab with gprof in VS Code devcontainer

- [x] Scaffold the Project
	Project structure created with .devcontainer/, src/, Makefile, README.md, and lab-guide.md

- [x] Customize the Project
	All required files created:
	- .devcontainer/Dockerfile (GCC, gprof, Valgrind)
	- .devcontainer/devcontainer.json (C/C++ extensions)
	- src/example1.c (prime numbers)
	- src/example2.c (Fibonacci)
	- src/example3.cpp (sorting algorithms)
	- src/example4.cpp (memory allocations)
	- Makefile (build, run, profile targets)
	- README.md (complete instructions)
	- lab-guide.md (educational content)

- [x] Install Required Extensions
	Extensions configured in devcontainer.json (installed automatically when devcontainer opens)

- [x] Compile the Project
	All examples compiled successfully with -pg flag for profiling

- [x] Create and Run Task
	Not needed - Makefile provides all necessary build and run targets

- [x] Launch the Project
	Project ready to use. To start:
	1. Reopen in Dev Container (Command Palette → "Dev Containers: Reopen in Container")
	2. Run 'make help' to see available targets
	3. Follow README.md for profiling instructions

- [x] Ensure Documentation is Complete
	✓ README.md with step-by-step profiling instructions
	✓ lab-guide.md with detailed educational content
	✓ copilot-instructions.md tracking project completion
	✓ All files created and tested successfully
