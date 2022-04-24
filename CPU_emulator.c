#include <stdio.h>
#include <stdlib.h>
struct Info {
    int MUSOR;
    int eax;
    int ebx;
    int ecx;
    int edx;
};

int detect_symbol_one(char *command);
int detect_symbol_two(char *command);
void mov(char* second_register, struct Info *p_Registers, int k);
void reg_printer(struct Info *p_Registers);


int main() {
    struct Info Registers = {0, 0, 0, 0}; 
    struct Info *p_Registers = &Registers;

    reg_printer(p_Registers);

    char command[8]; 
    char second_register[3] = {0, 0, 0};
    int x;
    char c;

    while(1) {
        for (int i = 0; i < 9; i++) {
            if ((c = getchar()) != '\0') {
                command[i] = c;
            }
        }
        c = getchar();
        if  ( c != '\0') { 
            second_register[0] = c;
            c = getchar(); 
            if ((c != '\0') || (c != ' ')) { 
                second_register[1] = c;
                c = getchar();
            }
        }
        command[8] = ' ';
        int k = detect_symbol_one(command);
        switch(command[0]) {
            case 'm': 
                mov(second_register, p_Registers, k);
                reg_printer(p_Registers);
                break;
            case 's':

                break;
         }
    }
}



int detect_symbol_two(char *second_register) { //detects 2nd registers 2nd symbol(%) -> ex: mov ebx e%x;
    if (second_register[1] == 'a') {
        return 0;
    }
    if (second_register[1] == 'b') {
        return 1;
    }
    if (second_register[1] == 'c') {
        return 2;
    }
    if (second_register[1] == 'd') {
        return 3;
    }  
}

int detect_symbol_one(char *command) { //detects first registers 2nd symbol(%) -> ex: mov e%x ...
    if (command[5] == 'a') {
        return 0;
    }
    if (command[5] == 'b') {
        return 1;
    }
    if (command[5] == 'c') {
        return 2;
    }
    if (command[5] == 'd') {
        return 3;
    }  
}

void mov(char* second_register, struct Info *p_Registers, int k) {  //k - 2nd symbol 1st reg
    printf("second reg : %c\n", second_register[0]);
    printf("k : %d\n", k);
    reg_printer(p_Registers);
    if (second_register[0] != 'e') {
        int int_char = second_register[0] - 48; //число, явл. вторым регистром
        printf("int_char : %d\n", int_char);
        switch(k) {
            case 0: 
                p_Registers->eax = int_char;
                break;
            case 1: 
                p_Registers->ebx = int_char;
                break;
            case 2: 
                p_Registers->ecx = int_char;
                break;
            case 3: 
                p_Registers->edx = int_char;  
                break;  
        }
    }
    if (second_register[0] == 'e') {
        int number = detect_symbol_two(second_register);
        printf("number : %d\n", number);
        int first_reg_value;

        if (number == 0) {
            first_reg_value = (int)p_Registers->eax;
            printf(" first_reg_value : %d\n", first_reg_value);
        }
        if (number == 1) {
            first_reg_value = (int)p_Registers->ebx;
            printf(" first_reg_value : %d\n", first_reg_value);
        }
        if (number == 2) {
            first_reg_value = (int)p_Registers->ecx;
            printf(" first_reg_value : %d\n", first_reg_value);
        }
        if (number == 3) {
            first_reg_value = (int)p_Registers->edx;
            printf(" first_reg_value : %d\n", first_reg_value);
        }

        switch(k) {
            case 0: 
                p_Registers->eax = first_reg_value;
                reg_printer(p_Registers);
                break;
            case 1: 
                p_Registers->ebx = first_reg_value;
                reg_printer(p_Registers);
                break;
            case 2: 
                p_Registers->ecx = first_reg_value;
                reg_printer(p_Registers);
                break;
            case 3: 
                p_Registers->edx = first_reg_value;  
                reg_printer(p_Registers);
                break;  
        }
    }
    return;
}



void reg_printer(struct Info *p_Registers) {
    printf("Registers :[ %d %d %d %d]\n", p_Registers->eax, p_Registers->ebx, p_Registers->ecx, p_Registers->edx);
}