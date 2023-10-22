#include <stdio.h>

#define OK 0
#define ERR 1


int input_array_length(int *array_length);
//изменил void input на int input!!!!!!!!
int input (int *buffer, int *length);
void output (int *buffer, int length);
//добавил доп аргумент в sum_numbers
int sum_numbers(int *buffer, int length, int *new_array_length);
int find_numbers(int* buffer, int length, int number, int* numbers);

int main()
{
    int array_length;
	int new_array_length = 0;

	if(input_array_length(&array_length) == 1){
		printf("n/a");
		return 1;
	}

	int array[array_length];

	if(input(array, &array_length) == 1){
		printf("n/a");
		return 1;
	}

	int sum_of_even_numbers = sum_numbers(array, array_length, &new_array_length);

	int output_array[new_array_length];

	find_numbers(array, array_length, sum_of_even_numbers, output_array);
	printf("%d\n", sum_of_even_numbers);
	output(output_array, new_array_length);

}

int input_array_length(int *array_length){
	char garbage;
	int status;
	if(scanf("%d%c", array_length, &garbage) == 2 && garbage == '\n'){
		status = OK;
	} else{
		status = ERR;
	}


	return status;
}

int input(int *buffer, int *length){
    char garbage;
	int status;
    for(int *p = buffer; p - buffer < *length; p++){
        if(scanf("%d%c", p, &garbage) == 2 && garbage == '\n'){ status = OK; } else { status = ERR;}
    }
	return status;
}


int sum_numbers(int *buffer, int length, int *new_array_length)
{
	int sum = 0;
	
	for (int i = 0; i < length; i++)
	{	
		if (buffer[i] % 2 == 0)
		{	
			sum = sum + buffer[i];
		}
	}

	*new_array_length = 0;
	for (int i = 0; i < length; i++)
	{	
		if(buffer[i] != 0){
			if (sum % buffer[i] == 0)
			{	
				*new_array_length += 1;
			}
		}
	}
	
	
	return sum;
}

int find_numbers(int* buffer, int length, int number, int* numbers)
{	
	int status = OK;

	int number_iterator = 0;
	for (int i = 0; i < length; i++)
	{	
		if(buffer[i] != 0){
			if (number % buffer[i] == 0)
			{	
				numbers[number_iterator] =  buffer[i];
				number_iterator += 1;
			}
		}
	}

	return status;
}

void output(int *buffer, int length){
	for(int i = 0; i < length; i++){
		printf("%d", buffer[i]);
		if(i != length-1){
			printf(" ");
		}
	}
}