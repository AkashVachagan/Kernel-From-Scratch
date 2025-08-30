# Kernel From Scratch

This project is an operating system kernel written in C (with a bit of low-level setup). It is written for x86_32.
It boots with GRUB, prints text to the VGA buffer, supports basic colors, newlines, and screen scrolling.


## Features (so far)
- Direct VGA text buffer output  
- Foreground color printing (`kprint_color`)
- Foreground and background color printing (`kprint_color_bg`)  
- Automatic line wrapping and scrolling  
- Basic screen clearing  


## Requirements
Make sure you have the following installed:

```bash
sudo apt update
sudo apt install build-essential qemu-system-x86 nasm grub-common
```
## Clean

To clear all the object, iso files.

```bash
make clean
```

## Build

To compile the kernel and create a bootable ISO:

```bash
make
```

## RUN

To run the iso for on qemu simulation

```bash
make run
```
