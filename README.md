# psexpl

A small C utility for inspecting Linux processes by reading metadata from `/proc/<pid>/status`. The project validates a PID and then extracts key process state from the kernel’s proc filesystem.

## Overview

The Linux kernel exposes process metadata under `/proc`. This project demonstrates how to read runtime process information from that interface and format it for a user-facing summary.

The utility currently reads and prints:

- process name
- process state
- parent process ID
- thread count
- umask
- PID

## Features

The repository implements:

- PID validation using `/proc`
- path construction for `/proc/<pid>/status`
- process metadata parsing from kernel-provided text
- memory-safe C structure handling
- formatted output for a subset of process fields

## Technical implementation

The implementation is intentionally straightforward:

- `check_valid()` verifies whether a PID exists
- `build_str()` constructs the correct `/proc` path
- `generic_info()` opens and parses `/proc/<pid>/status`
- relevant fields are extracted and stored in a process structure
- output is printed with basic formatting

Relevant files:

- `src/main.c` — entry point and CLI logic
- `src/infogeneric.c` — validation and path-building
- `src/procgeneric.c` — process metadata parsing
- `include/` — declarations and support code

## Repository structure

- `src/` — implementation files
- `include/` — support headers
- `Makefile` — build script
- `README.md` — documentation

## Prerequisites

- Linux
- GCC or Clang
- Make

## Build

From the repository root:

```bash
make
```

## Usage

Run the tool with a PID:

```bash
./psexpl <pid>
```

Example:

```bash
./psexpl 1234
```

## Known limitations

- Linux-only dependency
- small subset of process data collected
- no automated test suite
- project is small and intentionally focused on one specific system interface

## Future improvements

Possible next improvements:

- additional process fields
- richer error handling
- more polished CLI options
- better documentation and usage examples

## License

The repository includes a license file. Verify the repository metadata before relying on it as a legal statement.

## Related concepts

- Linux process internals
- `/proc`
- system programming
- C memory management
- operating systems
