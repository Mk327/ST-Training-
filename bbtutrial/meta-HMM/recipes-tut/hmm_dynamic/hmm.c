#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include <stdint.h>
#include <stddef.h>
#include "hmm.h"



/*if_initialized varibale to check if the big block was initailzed or not
  allocate_new varibale to check if the big block is filled or not
 */
char if_initialized = 0, allocate_new = 0,if_head_initialized = 0;

/*pointer used to points to the first segment */
static struct Dynamic_List *head = NULL;


/*Function to Initialize the first  of the segment 
- size = total size - metadata size
- it will be all free -> free_flag = 1
- it will not have previous or next segment at first 
 */

void Initialize (struct Dynamic_List *pointer) {


	pointer->size = Inrecease_Size -MD_Size;
	pointer->free_flag = 1;
	pointer->next = NULL;   
	if_initialized = 1 ;
	if(if_head_initialized == 0) 
	{
		head = pointer;
		if_head_initialized = 1 ;
	}
}

/*FUnction to split big free block 
- as the user wants a size that smaller than the size of the block 
- we'll make to different pointers one of them to be used to the reserved block 
- the another pointer points to the remaining free block 
 */


void Split (struct Dynamic_List *reserved_block ,  size_t  size) {

	struct Dynamic_List *remaining_block=(void*)((void*)reserved_block+size+MD_Size);
	remaining_block->size=(reserved_block->size)-size-MD_Size;
	remaining_block->free_flag=1;
	remaining_block->next=reserved_block->next;
	reserved_block->size=size;
	reserved_block->free_flag=0;
	reserved_block->next=remaining_block;

} 

/*Function to increase the heap size when the chunck is filled */


void Increase_Sbrk(struct Dynamic_List *up_pointer,size_t  size_requested){
	/*We increase the heap size by sbrk 
- Icrease the size member of the dynamic struct untill reaching the requested size*/
	while(up_pointer->size < size_requested+MD_Size)
	{
		sbrk (Inrecease_Size);
		up_pointer->size+=Inrecease_Size;
	}


}

/*Function to decrease the heap size when the chunck is free of data */


void Decrease_Sbrk(struct Dynamic_List *down_pointer){


	while(((down_pointer->size) >=  Decrease_Size) && ((down_pointer->free_flag) == 1) && ((down_pointer->next) == NULL) )
	{
		sbrk (-Decrease_Size);
		down_pointer->size-= Decrease_Size;
	}

}


/* Function to merge two consecuitve free blocks 
by adding thier sizes together so
-size = size of first block + size of second block + metadata size
-Make the next pointer of first block & previous pointer
of second block vanish
 */
void Merge (void) {
	/*define new pointer to loop on all segemnts untill reaching last block
 -must be the two free blocks consecuitve
 -adding the sizes
 - make the next pointer of first block points to third block 
	 */
	struct Dynamic_List *curr = NULL;
	struct Dynamic_List *prev = NULL;
	int x = 0;
	curr = head;
	while(curr->next != NULL){
			if((curr->free_flag == 1) && (curr->next->free_flag == 1))
			{
				curr->size+=(curr->next->size)+MD_Size;
				curr->next=curr->next->next;
			}
		prev=curr;
		curr=curr->next; 
		if (curr == NULL)
		{
			prev->next = NULL;
			break;
		}

	}
	if ( curr != NULL)
	{
		
	if((curr->free_flag == 1) && (prev->free_flag == 1) && (curr->next == NULL))
	{
		prev->size+=(curr->size)+MD_Size;
		prev->next = NULL;
	}

	}
 /*Function to decrease the heap size when the chunck is free of data */
	Decrease_Sbrk(prev);
	

}


/*Function to free specified block by getting its pointer 
 firstly it will check if its in the specified regions or not 
 - Make its free flag to be 1 indcating it's free
 - call the merge function to merge it with another free block if avaialble
 */


void Myfree (void *ptr) {

	/*flag varible to indicate the free flag ot each block
  -curr pointer to be used to loop on all blocks 
  -Matching_pointer used to convert the type of ptr varible passed to the function
	 */
	char flag = 0;
	struct Dynamic_List *curr= NULL;
	struct Dynamic_List *Matching_pointer= ptr;
	if ( ptr == NULL)
	{
		return;
	}
	curr = head ;
	/*to loop on all blocks untill reaching null*/
	while ( ((curr->next) != NULL) )
	{
		flag = curr->free_flag;
		curr++;
		if( (curr == Matching_pointer) && (flag == 0))
		{ 
			/* to make curr points to the block meta data again and make its free flag = 1
    and merge the block if possible*/
			--curr;
			curr->free_flag=1;
			Merge();
			break;
		}
		curr--;
		/*to point to the next block*/
		curr=curr->next;

	}
	/*If all blocks are freed go to initailze again*/
	if (head->next == NULL)
	{
		if_initialized = 0;
		if_head_initialized = 0;

	}

}

void free(void *ptr)
{
	Myfree(ptr);
}

/*Function to make dynamic allocation using sbrk
- it will ask the user about the size he wants 
- it will allocate a Dynamic_List pointer to the user has the requsted size
 */


void* Myalloc (size_t  size_requested) {
	/*-curr pointer to be used to loop on all blocks 
  -user pointer to be returned to user that indeciates the first free place
  -free_block pointer used to point on the first segment allocated  
  - make the size to be multiple of 8 bytes for alingnment
	 */
	size_requested = ((size_requested+7)/8)*8;
	struct Dynamic_List *curr= NULL;
	struct Dynamic_List *free_block=NULL;
	void *user_pointer = NULL;
	/* check if it's the first time to allocate or not 
    - if yes go to  Initialize function 
    - if no go to allocate new block if needed
	 */
	if (if_initialized == 0 )
	{
		free_block = (struct Dynamic_List*) sbrk (Inrecease_Size);
		Initialize (free_block);
		if (head->size < size_requested+MD_Size)
		{
			Increase_Sbrk(head,size_requested);
		}

	}

	curr = head ;
	/*loop untill find a suitable block which is free and has suitble size*/
	while ((((curr->size) < size_requested+MD_Size) || ((curr->free_flag) != 1)) && ((curr->next) != NULL))
	{
		// curr->prev=curr;
		curr=curr->next;
		/*if the chunck is filled go to allocate new chunck*/
		if(  ((curr->next) == NULL) && ((curr->size) < size_requested+MD_Size) )
		{
			Increase_Sbrk(curr,size_requested+MD_Size);
			curr = head;
		}

	}


	if (((curr->size) == size_requested) && ((curr->free_flag) == 1))
	{
		curr->free_flag = 0;
		/*increase the curr pointer to be pointing to the first free place*/
		//user_pointer = (void*)(++curr);
		curr++;
		user_pointer = curr;
		return user_pointer;
	}

	/*if the size is more than or equal wanted split the block */
	else if (((curr->size) >= size_requested+MD_Size) && ((curr->free_flag) == 1) )
	{

		Split (curr,size_requested) ;
		/*increase the curr pointer to be pointing to the first free place*/
		curr++;
		user_pointer = curr;
		return user_pointer;
	} 


}

void *malloc(size_t size)
{

	void *ptr=(void*)Myalloc(size);
	return ptr;
}






/* Function  to allocate dynamic blocks as user requsets
   it allocates number of blocks  each with the size requested 
*/
void* Mycalloc (int num , int size)
{

	size_t total_size = num * size;
	void *ptr = NULL;
	if (total_size <= 0 )
	{
		/*If overflow happend or one of the arguments = 0*/
		return NULL;
	}
	ptr =Myalloc(total_size);
	if (ptr != NULL)
	{
		/*to intialize the block bytes all to zero*/
		memset(ptr,0,total_size);
	}
	return ptr;
} 


void *calloc(size_t nmemb, size_t size)
{   
	void* ptr = Mycalloc (nmemb , size);
	return ptr;
}



/* Function to reallocate a previous allocated block with a new size */

void *Myrealloc (void *ptr , size_t new_size) 
{
    void *new_ptr = NULL; 
    struct Dynamic_List *temp = ptr; 
    size_t copy_size = 0;
    if (ptr == NULL )
    {
	new_ptr = malloc (new_size);
	return new_ptr;
   }
    else if (new_size == 0)
   {
	free(ptr);
	return NULL;
   }
    else {
            --temp;
            if (new_size <= (temp->size) )
            {
				/* don't reallaocte if the new size is less than the old */
                        new_ptr = ptr;
            }
            else
            {
	                copy_size = (temp->size) ;
                        new_ptr = Myalloc (new_size);
                        memcpy(new_ptr,ptr,copy_size);
                        Myfree(ptr);
            }
            return new_ptr;
        }
}
	



void *realloc(void *ptr, size_t new_size)
{  
	void *new_pointer= Myrealloc (ptr,new_size); 
	return new_pointer;
}













