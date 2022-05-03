#include <stdio.h>
#define N 4
int main()
{
    //A 65 Z90; a 97 - z122;
    char arr[100];
    char a;
    int i = 0;
    for (a = getchar(); a!= '\n'; ) {
        arr[i] = a;
        i++;
        a = getchar();
    }
    long long N_count = i;
    long long res = 0;
    long long diff = 32;
    char * p_arr = arr;

asm volatile (
		".intel_syntax noprefix\n"
        
        "mov r8, 96;\n"
        "L1:;\n"
        "xor rbx, rbx;\n"
        "mov bl, [rax + (rcx-1)];\n"
        "cmp rbx, r8;\n"
        "jle L_le;\n"
		"jg L_g;\n"
		
		"L_le:;\n"
		"add bl, dl;\n"
		"mov [rax + (rcx-1)], bl;\n"
		"jmp L_end;\n"
		
		"L_g:;\n"\
		"sub bl, dl;\n"
		"mov [rax + (rcx-1)], bl;\n"
		"jmp L_end;\n"
		
		"L_end:;\n"
		"loop L1;\n"

		".att_syntax noprefix"
		: "=d" (res)
		: "a" (p_arr), "c" (i), "d" (diff)
	);
	
	printf("\narr = %p, diff = %llu\n\n", p_arr, res);
	
    for(int j = 0; j < i; j++) {
        printf("%c", arr[j]);
    }

    return 0;
}

