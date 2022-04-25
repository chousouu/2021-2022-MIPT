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
void add(char* second_register, struct Info *p_Registers, int k);
void sub(char* second_register, struct Info *p_Registers, int k);
void reg_printer(struct Info *p_Registers);


int main() {
    struct Info Registers = {0, 0, 0, 0}; 
    struct Info *p_Registers = &Registers;

    char command[8]; 
    char second_register[4];    
    char c;

    int exit_condition = 1;
    
    while(exit_condition != 0) {
        c = getchar();
        if (c == 'r') {
            return 0;
        }
        command[0] = c;
        for (int i = 1; i < 9; i++) {
            c = getchar();
            command[i] = c;
        }
        c = getchar(); //[0] second reg 
        if (c != '-') {
            second_register[0] = c;
            second_register[3] = 48;
            c = getchar(); //[1]
            if (c != '\n') {
                second_register[1] = c;
                c = getchar();
                second_register[2] = c;
                c = getchar();
                second_register[3] = 48;
            }
        }
        else if (c == '-') {
            second_register[3] = 49;  // т.к у меня числа работают только для 0-9, то я зарезервирую отдельный слот в этом массиве для негатив числе
            c = getchar();              // ^ second_Reg = char -> (int)49 == 1 
            second_register[0] = c;
            c = getchar();
        }
        int k = detect_symbol_one(command);
        switch(command[0]) {
            case 'm': 
            mov(second_register, p_Registers, k);
            break;
            case 'a': 
            add(second_register, p_Registers, k);
            break;
            case 's': 
            sub(second_register, p_Registers, k);
            break;
        }
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

int value_of_second_reg(struct Info *p_Registers, char* second_register) {
    int number = detect_symbol_two(second_register);
    int first_reg_value;
    if (number == 0) {
        first_reg_value = (int)p_Registers->eax ;
    }
    if (number == 1) {
        first_reg_value = (int)p_Registers->ebx;
    }
    if (number == 2) {
        first_reg_value = (int)p_Registers->ecx ;
    }
    if (number == 3) {
        first_reg_value = (int)p_Registers->edx ;
    }
    return first_reg_value;
}

void mov(char* second_register, struct Info *p_Registers, int k) {  //k - 2nd symbol 1st reg
    if (second_register[0] != 'e') {
        int sign = 1;
        if (second_register[3] == 49) {
            sign = -1;
        }
        int int_char = (second_register[0] - 48) *sign; //число, явл. вторым регистром
        switch(k) {
            case 0: 
                p_Registers->eax = int_char;
                reg_printer(p_Registers);
                break;
            case 1: 
                p_Registers->ebx = int_char;
                reg_printer(p_Registers);
                break;
            case 2: 
                p_Registers->ecx = int_char;
                reg_printer(p_Registers);
                break;
            case 3: 
                p_Registers->edx = int_char;  
                reg_printer(p_Registers);
                break;  
        }
    }
    if (second_register[0] == 'e') {
        int first_reg_value = value_of_second_reg(p_Registers, second_register);

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

void add(char* second_register, struct Info *p_Registers, int k) {
    if (second_register[0] != 'e') {
        int sign = 1;
        if ( second_register[3] == 49) {
            sign = -1;
        }
        int int_char = (second_register[0] - 48)*sign; //число, явл. вторым регистром
        switch(k) {
            case 0: 
                p_Registers->eax += int_char;
                reg_printer(p_Registers);
                break;
            case 1: 
                p_Registers->ebx += int_char;
                reg_printer(p_Registers);
                break;
            case 2: 
                p_Registers->ecx += int_char;
                reg_printer(p_Registers);
                break;
            case 3: 
                p_Registers->edx += int_char; 
                reg_printer(p_Registers); 
                break;  
        }
    }
    if (second_register[0] == 'e') {
        int first_reg_value = value_of_second_reg(p_Registers, second_register);

        switch(k) {
            case 0: 
                p_Registers->eax += first_reg_value;
                reg_printer(p_Registers);
                break;
            case 1: 
                p_Registers->ebx += first_reg_value;
                reg_printer(p_Registers);
                break;
            case 2: 
                p_Registers->ecx += first_reg_value;
                reg_printer(p_Registers);
                break;
            case 3: 
                p_Registers->edx += first_reg_value;  
                reg_printer(p_Registers);
                break;  
        }
    }
    reg_printer(p_Registers);
    return;
}

void sub(char* second_register, struct Info *p_Registers, int k) {
    if (second_register[0] != 'e') {
        int sign = 1;
        if ( second_register[3] == 49) {
            sign = -1;
    }
        int int_char = (second_register[0] - 48)*sign; //число, явл. вторым регистром
        switch(k) {
            case 0: 
                p_Registers->eax -= int_char;
                reg_printer(p_Registers);
                break;
            case 1: 
                p_Registers->ebx -= int_char;
                reg_printer(p_Registers);
                break;
            case 2: 
                p_Registers->ecx -= int_char;
                reg_printer(p_Registers);
                break;
            case 3: 
                p_Registers->edx -= int_char;
                reg_printer(p_Registers);  
                break;  
        }
    }
    if (second_register[0] == 'e') {
        int first_reg_value = value_of_second_reg(p_Registers, second_register);

        switch(k) {
            case 0: 
                p_Registers->eax -= first_reg_value;
                reg_printer(p_Registers);
                break;
            case 1: 
                p_Registers->ebx -= first_reg_value;
                reg_printer(p_Registers);
                break;
            case 2: 
                p_Registers->ecx -= first_reg_value;
                reg_printer(p_Registers);
                break;
            case 3: 
                p_Registers->edx -= first_reg_value;  
                reg_printer(p_Registers);
                break;  
        }
    }
    return;
}


void reg_printer(struct Info *p_Registers) {
    printf("Registers : {%d, %d, %d, %d}\n", p_Registers->eax, p_Registers->ebx, p_Registers->ecx, p_Registers->edx);
    return;
}