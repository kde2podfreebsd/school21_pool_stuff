#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(){
    char string[100];
    char new[100];
    
    int i = 0;
    char temp = getchar();
    string[i] = temp;
    while(temp != '\n'){
        i++;
        temp = getchar();
        string[i] = temp;
    }

    int j = 0;
    for(int i =0; i < (int)strlen(string); ++i){
        if(string[i] == ' '){
            if(string[i+1] == ' ' || j == 0 || string[i+1] == '\0'){
                continue;
            }
        }
        new[j] = string[i];
        j++;
    }
    new[j-1] = '\0';
    printf("%s", new);
}