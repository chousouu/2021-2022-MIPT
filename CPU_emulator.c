#include <stdio.h>
#include <stdlib.h>
struct Registers {
    int eax;
    int ebx;
    int ecx;
    int edx;
};
int detect_symbol_one(char *command);
int detect_symbol_two(char *command);
void mov(int *p, int k, char *command);



int main() {
    int p[4] = {0, 0, 0, 0}; // eax ebx ecx edx 
    char command[11]; 
    int x;
    while(1) {
        scanf("%s", command); // mov e*x, e!x  
//                               012345678910 ; arr[11]  *-5; e/number-9 !-10
         switch(command[0]) {
            case 'm': 
                int k = detect_symbol_one(command);
                mov(p, k, command);
                for (int i = 0; i < 4; i++) {
                    printf("%d ", p[i]);
                }
                break;
/*            case 'a':
                add();
                break;
            case 's':
                sub();
                break;
            case 'r': 
                return 0;                    
                break;
*/



         }
    }
}

int detect_symbol_one(char *command) {
    if (command[5] == 'a') {
        return 1;
    }
    if (command[5] == 'b') {
        return 2;
    }
    if (command[5] == 'c') {
        return 3;
    }
    if (command[5] == 'd') {
        return 4;
    }  
}
int detect_symbol_two(char *command) {
   if (command[10] == 'a') {
        return 1;
    }
    if (command[10] == 'b') {
        return 2;
    }
    if (command[10] == 'c') {
        return 3;
    }
    if (command[10] == 'd') {
        return 4;
    }  
}

void mov(int *p, int k, char *command) { 
    if (command[9] != 'e') {
        int int_char = command[9] - 48; 
        p[k] = p[k] + int_char;
    }
    else {
        int z = detect_symbol_two(command); 
        p[k] = p[k] + p[z];
    }
}