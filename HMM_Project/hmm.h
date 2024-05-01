#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#define Inrecease_Size 132000 /*the step of increasing brogram break*/
#define Decrease_Size  128000 /*the step of decreasing brogram break*/
#define MD_Size        24 /*Meta data size of each block*/
#define _BSD_SOURCE
#define NUM_ALLOCS 1000
#define MAX_SIZE 10000
#define MAX_ITERATIONS 1000
#define MAX_ALLOCS 1000000
#define MAX_ALLOC_SIZE 1000 
#define CORRUPTION_SIZE 8 // Number of bytes to corrupt in allocated memory

#define getInt(x, ...) atoi(x)


struct Dynamic_List
{
	size_t   size; /*size requseted to be allocated in heap*/
	char free_flag; /*free flag to be set if its a free block and cleared if not */
	struct Dynamic_List *next; /*pointer to the next block */
	//struct Dynamic_List *prev;  /*pointer to the previous block */
};

/*Function to Initialize the first of the segment 
- size = total size - metadata size
- it will be all free -> free_flag = 1
- it will not have previous or next segment at first 
 */


void Initialize (struct Dynamic_List *pointer);

/*FUnction to split big free block 
- as the user wants a size that smaller than the size of the block 
- we'll make to different pointers one of them to be used to the reserved block 
- the another pointer points to the remaining free block 
 */


void Split ( struct Dynamic_List* reserved_block ,size_t  size) ;

/*Function to make dynamic allocation using sbrk
- it will ask the user about the size he wants 
- it will allocate a Dynamic_List pointer to the user has available size
 */

void* Myalloc (size_t size);


/*Function to increase the heap size when the chunck is filled */


void Increase_Sbrk(struct Dynamic_List *new_pointer,size_t  size_requested);

/*Function to decrease the heap size when the chunck is free of data */


void Decrease_Sbrk(struct Dynamic_List *down_pointer);

/* Function to merge two consecuitve free blocks 
by adding thier sizes together so
size = size of first block + size of second block + metadata size
and make the next pointer of first block & previous pointer
of second block vanish
 */

void Merge (void);

/*Function to free specified block by getting its pointer 
firstly it will check if its in the specified regions or not 
- Make its free flag to be 1 indcating it's free
- call the merge function to merge it with another free block if avaialble
 */

void Myfree (void *ptr);




/* Function  to allocate dynamic blocks as user requsets
   it allocates number of blocks  each with the size requested 
*/
void* Mycalloc (int num , int size);



/* Function to reallocate a previous allocated block with a new size */
void *Myrealloc (void *ptr , size_t new_size );




void *malloc(size_t size);
void free(void *ptr);
void *calloc(size_t nmemb, size_t size);
void *realloc(void *ptr, size_t size);
