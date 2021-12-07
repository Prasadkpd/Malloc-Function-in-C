#include <stdio.h>
#include <stddef.h> //use for get the size_t data type in this
#include <stdbool.h> 

#define memory_size 25000

char memory[memory_size];//create a memory of size 25000 bytes

//following structure for contain the metadata of each block allocated or not

struct meta_block{
   size_t size; //contain the size of the metadata block
   bool free;   //check block is free or not
   struct meta_block *next; //point to the next metadata block
};

struct meta_block *freeblock=(void*)memory; //initialize the pointer to memory

void initialize();
void split(struct meta_block *fitting_slot, size_t size);
void *MyMalloc(size_t No_Bytes);
void merge();
void MyFree(void *ptr);
