#include <stdio.h>

#define NMAX 10

void input (int *buffer, int *length);
void output (int *buffer, int length);
int sum_numbers(int *buffer, int length);
int find_numbers(int* buffer, int length, int number, int* numbers);


int main()
{

	int buffer[NMAX], numbers[NMAX];
	int length, sum;

	input(buffer, &length);

	if(length > NMAX || length <= 0){
		printf("n/a");
		return 1;
	}

	sum = sum_numbers(buffer, length);

	length = find_numbers(buffer, length, sum, numbers);

	output(numbers, length);
	return 0;
    
}

void input(int *buffer, int *lenght){
	scanf("%d", lenght);
	if(*lenght > NMAX || *lenght <= 0){
		return;
	}
	for(int *p = buffer; p - buffer < *lenght; ++p){
		scanf("%d", p);
	}
}

void output(int *buffer, int lenght){
	for(int *p = buffer; p - buffer < lenght; ++p){
		printf("%d", *p);
		if(p - buffer < lenght - 1){
			printf(" ");
		}
	}
}

int sum_numbers(int *buffer, int length)
{
	int sum = 0;
	
	for (int *p = buffer; p - buffer < length; ++p)
	{
		if (*p % 2 == 0)
		{
			sum += *p;
		}
	}

	return sum;
}

int find_numbers(int* buffer, int length, int number, int* numbers)
{	
	int i = 0;
	for(int *p = buffer; p - buffer < length; ++p){
		if(*p != 0){
		if(number % *p == 0){
			numbers[i] = *p;
			i++;
		}
	}
	}

	return i;
}
