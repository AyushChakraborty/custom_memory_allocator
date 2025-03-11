#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdint.h>
#include <sys/mman.h>   //mmap exposes the memory system call

/*
void *mmap(void addr[.length], size_t length, int prot, int flags,
           int fd, off_t offset);
int munmap(void addr[.length], size_t length);

creates a new mapping in the virtual address space of the calling process
*/

/*
malloc() is a library call and instead calls system functions like mmap() for larger chunk/block allocation,
sbrk() for shorter chunk allocation and brk() which changes the program break which itself is the boundary between
heap and data segment 

sbrk(n) (psudocode) increses the heap by n bytes
*/

//lets assume that the heaps size is fixed for now, so dealing with this 

//mmap can req for memory anywhere in the logical addr space not just the heap


//first thing which can be done is to reserve a large chunk of memory that will serve as heap space for allocations
//keep in mind that mmap() directly requests for memory from the OSs virtual memory space

#define HEAP_SIZE (128*128)   //aprox 12kb
#define BLOCK_SIZE 32    //32 bytes per block 
#define NUM_BLOCKS 512    //512 blocks in the heap mapped space for a process


typedef struct bitmask {
    int bitmask_arr[BLOCK_SIZE];
}bitmask;


void *init_heap_space(bitmask *bitmask_arr) {
    //map heap space to the logical address space of the process by req for space from OS directly
    void *heap_start_ptr = mmap(NULL, HEAP_SIZE, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
    
    if (heap_start_ptr == MAP_FAILED) {
        perror("mapping failed\n");
        exit(1);
    }

    //making the bitmask array, init all the masks to be 0 initially
    for (int i=0; i<NUM_BLOCKS; i++) {
        bitmask_arr->bitmask_arr[i] = 0;
    }
    return heap_start_ptr;
}


uintptr_t map_func(int block_num, void *base_addr) {  //block_num is 0 indexed
    uintptr_t base_addr_hex = (uintptr_t)base_addr;
    return base_addr_hex + (BLOCK_SIZE * block_num);
    //using this function, each bit in the bit map can be associated to a heap memory address
}


//have to allocate heap space if not already, then occupy as many num of bytes as needed by the user within the 
//number of blocks to be needed, then when custom_free() is called, only free those, not the whole heap mapping
void *custom_malloc(int reqd_bytes) {
    
    bitmask bitmask_arr;
    void *heap_start_ptr = init_heap_space(&bitmask_arr);
    
    //using 32 bytes per block
    int blocks_needed = ceil((double)reqd_bytes/16);
    
    
}


int main(int argc, char **argv) {
    
    
    
    return 0;
}