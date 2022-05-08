#include <stdio.h>
int main()
{
    //A 65 Z90; a 97 - z122;
    // 48 - 57  : 0 - 9 
    char arr[100];
    char a;
    int i = 0;
    for (a = getchar(); a!= '\n'; ) {
        arr[i] = a;
        i++;
        a = getchar();
    }
    char array_of_non_letters[100];
    int arr_index[100] = { 0 } ;// массив, хранящий номер элемента arr, где не буква
    for (int i = 0; i < 100; i++) {
        if ( ((int)arr[i] <= 97 && (int)arr[i] >= 90) || (int)arr[i] > 122 || (int)arr[i] < 65  ) {
            array_of_non_letters[i] = arr[i];
            arr_index[i] = i;
        }
    }
    long long N_count = i;
    long long res = 0;
    long long A_razn_a = 32;
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
		: "a" (p_arr), "c" (i), "d" (A_razn_a)
	);
	
	//printf("\narr = %p, A_razn_a = %llu\n\n", p_arr, res);
	for (int i = 0; i < 100; i++) {
        if (arr_index[i] != 0) {
            arr[i] = array_of_non_letters[i];
        }
    }

    for(int j = 0; j < i; j++) {
        printf("%c", arr[j]);
    }

    return 0;
}
