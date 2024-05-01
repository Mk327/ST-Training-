# Heap Memory Manager (HMM)

This project aims to provide a custom implementation of dynamic memory allocation functions (`malloc`, `free`, `realloc`, `calloc`) in C, as an alternative to the standard functions provided by glibc. The implementation includes managing memory allocation and deallocation using a heap memory management approach.

## Features

- **Dynamic Memory Allocation**: Provides functions for allocating memory dynamically as per user request.
- **Memory Deallocation**: Allows freeing allocated memory blocks when they are no longer needed.
- **Memory Reallocating**: Supports resizing previously allocated memory blocks.
- **Memory Alignment**: Ensures alignment of memory allocations to a multiple of 8 bytes.
- **Heap Management**: Manages heap memory by increasing or decreasing its size as needed.

## How to Use

1. **Include Header File**: Include the header file `hmm.h` in your C program.
   ```c
   #include "hmm.h"
   ```

2. **Memory Allocation**: Use the `malloc` function to dynamically allocate memory.
   ```c
   void *ptr = malloc(size);
   ```

3. **Memory Deallocation**: Use the `free` function to release allocated memory blocks.
   ```c
   free(ptr);
   ```

4. **Memory Reallocation**: Use the `realloc` function to resize previously allocated memory blocks.
   ```c
   void *new_ptr = realloc(ptr, new_size);
   ```

5. **Memory Initialization**: Optionally, use the `calloc` function to allocate and initialize memory with zeros.
   ```c
   void *ptr = calloc(num, size);
   ```

## Implementation Details

- The implementation maintains a linked list data structure to manage allocated memory blocks.
- Each memory block is preceded by metadata containing information such as size and allocation status and Next block.
- Memory blocks are split or merged as needed to fulfill allocation or deallocation requests efficiently.
- The heap size is adjusted dynamically using the `sbrk` system call to accommodate memory allocation requests.
- Memory alignments are ensured by adjusting requested sizes to multiples of 8 bytes.

## Note

- This implementation is designed for educational purposes and may not be as efficient or robust as standard library implementations.
- Use caution when integrating this memory manager into production code, as it may not offer the same level of performance or compatibility as standard library functions.
