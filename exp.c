#include <stdio.h>
#include <stdint.h>

int main() {
    int x = 4;
    int *y = &x;
    
    uintptr_t z = (uintptr_t)y;
    printf("hex value of the address is: 0x%lx\n", z);
    printf("hex value of the address is: %p\n", y);
    
    uintptr_t d = z + 18;   //where 18 is also treated as a hex number here
    printf("d: 0x%lx\n", d);
    return 0;
}