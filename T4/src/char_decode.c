#include <stdio.h>

#define OK 0
#define ERR 1

void char_to_hex(char character);
void hex_to_char(char character);

int main(int argc, char *argv[]){

    int status = OK;

    if ((argv[1][0] != '1' && argv[1][0] != '0') || argc < 2) {
        printf("n/a");
        status = ERR;
    }

    if(argv[1][0] == '0'){
        char c;
        scanf("%c", &c);
        char_to_hex(c);
    }

    if(argv[1][0] == '1'){
        unsigned int c;
        scanf("%X", &c);
        hex_to_char(c);
    }

    return status;
}

void char_to_hex(char character) {
    printf("%X", character);
}

void hex_to_char(char character){
    printf("%c", character);
}

