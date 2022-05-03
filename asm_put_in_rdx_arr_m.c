#include <stdio.h>
#include <stdlib.h>
// создать массив на n элементов, (m, n - вводит пользователь), 
//заполнить его; и в регистр rdx положить значение элемента c номером m
int main()
{
    int n = 0;
    int m = 0;
    printf("n:");
    scanf("%d", &n);
    printf("m:");
    scanf("%d", &m);
    int* arr = (int*)calloc(n,sizeof(int));
    for(int i = 0; i < n; i++)
        scanf("%d", &arr[i]);
    printf("Array:\narr = %p\n", arr);
    
    int N_count = m;
    long long res = 0;
    int * p_arr = arr;
    printf("Variables:\nres = %lld\narr = %p\n", res, p_arr);
    
	asm volatile(
		".intel_syntax noprefix\n"
        
        "xor rdx, rdx;\n"
        "xor rbx, rbx;\n"
		"mov ebx, [rax + (rcx-1)*4];\n"
		"mov rdx, rbx;\n"

		".att_syntax noprefix"
		: "=d" (res)
		: "a" (p_arr), "c" (N_count)
	);
    
    printf("After asm:\nres = %lld\narr = %p", res, p_arr);

    return 0; 
}
