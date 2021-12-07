#include <stdio.h>
#include <stddef.h>
#include "mymalloc.h" //include the created header file mymalloc.h

//Initialize the block of memory
void initialize()
{
    freeblock->size = 25000-sizeof(struct meta_block);
    freeblock->free=true;
    freeblock->next=NULL;
}

//Create a new block by splitting the freeblock

void split(struct meta_block *position,size_t size)
{
    struct meta_block *new=(void*)((void*)position+size+sizeof(struct meta_block));
    new->size =(position->size)-size-sizeof(struct meta_block);
    new->free=true;
    new->next=position->next;
    position->free=false;
    position->next=new;
}


void merge()
{
    struct meta_block *current = freeblock;
    while(current->next!=NULL)
    {
        if((current->free)&&(current->next->free))
        {
            current->size=current->size+(current->next->size)+sizeof(struct meta_block);
            current->next=current->next->next;
        }
        current=current->next;
    }
}

void *MyMalloc (size_t size)
{
    struct meta_block *current;//to taverse in the memory block
    
    if(!(freeblock->size))
    {
        initialize();
    }
    current=freeblock;//create a teampary pointer as a current to start of the metadata block

    while((((current->size)<size)||(current->free==false))&&(current->next!=NULL))
    {
        current=current->next;
    }

    if(current->size == size)
    {
        current->free=false;
        printf("Exactly matched memeory block is allocated\n");
        return (void*)(++current);
    }

    else if((current->size)>(size+sizeof(struct meta_block)))
    {
        split(current,size);
        printf("Splited and Memory block is allocated\n");
        return (void*)(++current);
    }

    else
    {
        printf("Insufficient memory to allocate\n");
        return NULL;
    }
    
}

void MyFree(void *ptr)
{
    if(((void*)memory <=ptr)&&(ptr<=(void*)(memory+memory_size)))
    {
        struct meta_block *current=ptr;
        --current;
        current->free=true;
        printf("Free memory block\n");
        merge();
    }
    else
    {
        printf("Invalid pointer\n");
    }
}
