//sample for mmap

#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>

#define HEAP_SIZE (1024*1024)  //1mb of heap 

int main() {
    //use mmap to allocate 1mb of memory to the process' logical addressing space
    void *heap_start = mmap(NULL, HEAP_SIZE, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
    
    if (heap_start == MAP_FAILED) {
        perror("mmap failed");
        exit(1);
    }
    
    printf("heap allocated at %p\n", heap_start);
    
    //here, we are accessing a part of the memory ourselves but using malloc() allocating heap, filling, freeing
    //memory from it is all done by it, so the user doesnt have to worry about it much, but here since mmap() itself
    //is a system call, all this has to be managed by us 
    char *ptr = (char *)heap_start;  //ptr to the start of the memory allocated for the heap
    
    ptr[0] = 'A';
    ptr[1] = 'b';
    printf("data written: %c %c\n", ptr[0], ptr[1]);
    
    //unmapping the memory allocated for the heap in the logical space of the process, KEEP IN MIND, this is not 
    //the same as freeing certain parts of the heap, which is what we actually want to do
    munmap(heap_start, HEAP_SIZE);
    printf("heap memory unmapped from process\n");
}