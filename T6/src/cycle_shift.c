#include <stdio.h>

#define NMAX 10
#define CUSTOM_ABS(x) ((x < 0) ? -(x) : (x))

void input (int *buffer, int *length, int *shift);
void output (int *buffer, int length);
void cyclicShift(int *buffer, int length, int shift);

int main(){

    int buffer[NMAX];
	int length, shift;

	input(buffer, &length, &shift);

	if(length > NMAX || length <= 0){
		printf("n/a");
		return 1;
	}

    cyclicShift(buffer, length, shift);

    output(buffer, length);

}

void input(int *buffer, int *lenght, int *shift){
	scanf("%d", lenght);
	if(*lenght > NMAX || *lenght <= 0){
		return;
	}
	for(int *p = buffer; p - buffer < *lenght; ++p){
		scanf("%d", p);
	}

    scanf("%d", shift);
}

void output(int *buffer, int lenght){
	for(int *p = buffer; p - buffer < lenght; ++p){
		printf("%d", *p);
		if(p - buffer < lenght - 1){
			printf(" ");
		}
	}
}

void cyclicShift(int *buffer, int length, int shift){
    int temp;
    shift %= length;
    if(shift > 0){
        for(int i = 0; i < shift; ++i){
            temp = buffer[0];
            for(int j = 0; j < length - 1; j++){
                buffer[j] = buffer[j+1];
            }
            buffer[length - 1] = temp;
        }
    } else if(shift < 0){
        for(int i = 0; i < CUSTOM_ABS(shift); i++){
            temp = buffer[length - 1];
            for (int j = length - 1; j > 0; --j){
                buffer[j] = buffer[j - 1];
            }
            buffer[0] = temp;
        }
    }
}
