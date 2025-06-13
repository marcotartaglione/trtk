# TRT Kernel

A simple 32-bit hobby OS kernel designed to run on QEMU

## Build & run

| Dependecy | Purpouse |
|:----:|---|
| `make` | Build system |
| `gcc` | Compiler |
| `nasm` | Assembler |
| `ld` | Linker |
| `qemu-system-x86_64` | Emulated x84 env |

## Build commands

| Dependecy | Purpouse |
|:----:|---|
| `make` | Build `kernel.bin` |
| `make clean` | Clean previous builds |
| `make qemu` | Run QEMU |
| `make qemu-gdb` | Run QEMU waiting for GDB |
