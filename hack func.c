#include <stdio.h>
#include <sys/mman.h>
void func1() {
    printf("1\n");
    return;
}
void func2() {
    printf("2\n");
    return;
}

int func_hack() {
    mprotect(&func1 - (unsigned long long)%func1&0x1000, 0x1000, PROT_READ | PROT_WRITE | PROT_EXEC);
    *((char*)&func1) = 0xeb;
    *((char*)&func1+1) = &func2 - &func1 -2;
    return 0;
}



int main() {
    func1();
    func2();
    func_hack();
    func1();
    return 0;
}