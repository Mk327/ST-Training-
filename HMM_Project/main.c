#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include <stdint.h>
#include <stddef.h>
#include "hmm.h"











 /*First Test Case*/

#define getInt(x, ...) atoi(x)

extern char end, edata, etext;

int main(int argc, char *argv[])
{
    char *ptr[MAX_ALLOCS];
    int freeStep, freeMin, freeMax, blockSize, numAllocs, j;
    printf("etext = %p, edata=%p, end=%p, initial program break=%p\n", &etext, &edata, &end, (char*)sbrk(0));

    if (argc < 3 || strcmp(argv[1], "--help") == 0) {
        printf("%s num-allocs block-size [step [min [max]]]\n", argv[0]);
        exit(1);
    }

    numAllocs = getInt(argv[1], GN_GT_0, "num-allocs");
    if (numAllocs > MAX_ALLOCS) {
       printf("num-allocs > %d\n", MAX_ALLOCS);
        exit(1);
    }

    blockSize = getInt(argv[2], GN_GT_0 | GN_ANY_BASE, "block-size");

    freeStep = (argc > 3) ? getInt(argv[3], GN_GT_0, "step") : 1;
     freeMin =  (argc > 4) ? getInt(argv[4], GN_GT_0, "min") : 1;
     freeMax =  (argc > 5) ? getInt(argv[5], GN_GT_0, "max") : numAllocs;

    if (freeMax > numAllocs) {
        printf("free-max > num-allocs\n");
        exit(1);
    }

    printf("Initial program break:          %10p\n", sbrk(0));

   printf("Allocating %d*%d bytes\n", numAllocs, blockSize);
    for (j = 0; j < numAllocs; j++) {
        ptr[j] = malloc(blockSize);
       // printf("%p\n",ptr[j]);
        if (ptr[j] == NULL) {
            printf("malloc returned null\n");
            exit(1);
        }
    }
    printf("Program break is now:           %10p\n", sbrk(0));

    printf("Freeing blocks from %d to %d in steps of %d\n",
           freeMin, freeMax, freeStep);
    for (j = freeMin - 1; j < freeMax; j += freeStep)
    {
        free(ptr[j]);
    }
    printf("After free(), program break is: %10p\n", sbrk(0));
   
   // while(1);

    exit(EXIT_SUCCESS);
}








// /*Second Test Case*/

// void random_alloc_free_test() {
// 	srand((unsigned int)time(NULL));

// 	void* pointers[NUM_ALLOCS] = {NULL};

// 	for (int  i = 0; i < MAX_ITERATIONS; ++i) {
// 		int index = rand() % NUM_ALLOCS;
// 		if (pointers[index] == NULL) {
// 			// Allocate memory
// 			size_t size = (size_t)(rand() % MAX_SIZE) + 1;
// 			pointers[index] = malloc(size);
// 			if (pointers[index] != NULL) {
// 				printf("Allocated memory of size %zu at address %p\n", size, pointers[index]);
// 			} else {
// 				fprintf(stderr, "Allocation failed for size %zu\n", size);
// 			}
// 		} else {
// 			// Free memory
// 			printf("Freeing memory at address %p\n", pointers[index]);
// 			free(pointers[index]);
// 			pointers[index] = NULL;
// 		}
// 	}

// 	// Free remaining allocated memory
// 	for ( int j = 0; j < NUM_ALLOCS; j++) {
// 		if (pointers[j] != NULL) {
// 			printf("Freeing remaining memory at address %p\n", pointers[j]);
// 			free(pointers[j]);
// 			pointers[j] = NULL;
// 		}
// 	}
// }

// int main() {
// 	printf("Starting random allocation and deallocation test...\n");
// 	random_alloc_free_test();
// 	printf("Test complete.\n");
// 	return 0;
// }






/*Third Test Case*/

// int main() {
//     void* ptrs[NUM_ALLOCS] = {NULL};

//     // Allocate memory
//     for (int i = 0; i < NUM_ALLOCS; i++) {
//         size_t size = rand() % MAX_ALLOC_SIZE + 1;
//         ptrs[i] = malloc(size);
//         if (ptrs[i] == NULL) {
//             fprintf(stderr, "Memory allocation failed\n");
//             // Cleanup allocated memory before exiting
//             for (int j = 0; j < i; j++) {
//                 free(ptrs[j]);
//             }
//             exit(EXIT_FAILURE);
//         }
//     }

//     // Free memory
//     for (int i = 0; i < NUM_ALLOCS; i++) {
//         free(ptrs[i]);
//     }

//     printf("Allocations and deallocations completed successfully!\n");

//     return 0;
// }




/*Last test case*/

// #define NUM_OPERATIONS 1000

// //#define MAX_SIZE (100000)

// enum Operation
// {
//     MALLOC,
//     CALLOC,
//     REALLOC,
//     FREE
// };

// void *allocated_blocks[NUM_OPERATIONS];

// void perform_random_operations()
// {

//     srand(time(NULL));

//     for (int i = 0; i < NUM_OPERATIONS; i++)
//     {
// 		if (i == 400)
// 		{
// 			int x = 5;
// 		}
//         enum Operation op = rand() % 4;
//         switch (op)
//         {
//         case MALLOC:
//         {
//            size_t size = rand() % MAX_SIZE + 1;
// 		   // size_t size = 9820;
//             allocated_blocks[i] = malloc(size);
//             printf("Allocated block %p with size %zu\n", allocated_blocks[i], size);
//             break;
//         }
//         case CALLOC:
//         {
//             size_t num = rand() % MAX_SIZE + 1;
//              size_t size = rand() % MAX_SIZE + 1;
// 			//size_t num = 9820/2;
// 			//size_t size = 2;
//             allocated_blocks[i] = calloc(num, MAX_SIZE/num);
//             printf("Allocated block %p with %zu elements of size %zu\n", allocated_blocks[i], num, size);
//             break;
//         }
//         case REALLOC: {
//             if (i > 0) {
//                 int idx = rand() % i;
//                  size_t size = rand() % MAX_SIZE + 1;
// 				//size_t size = 9820;
//                 allocated_blocks[idx] = realloc(allocated_blocks[idx], size);
//                 printf("Reallocated block %p with size %zu\n", allocated_blocks[idx], size);
//             }
//             break;
//         }
//         case FREE:
//         {
//             if (i > 0)
//             {
//                 int idx = rand() % i;
//                 free(allocated_blocks[idx]);
//                 allocated_blocks[idx] = NULL;
//                 //printf("Freed block %p\n", allocated_blocks[idx]);
//             }
//             break;
//         }
//         }
//     }
// }

// int main()
// {
//     perform_random_operations();

//     return 0;
// }