#include <stdio.h>

int main(int argc, char *argv[]){
    if ((argv[1][0] != '1' && argv[1][0] != '0') || argc < 2) {
        printf("n/a");
        return 1;
    }

    if(argv[1][0] == '0'){
        printf("encode");
    }

    if(argv[1][0] == '1'){
        printf("decode");
    }

    return 0;
}