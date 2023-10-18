#include <stdio.h>

#define my_abs(x) ((x >=0) ? x : -x)

int is_prime(int num);
void find_max_primary_div(int inpunt_value);

int main(){
    int num;
    char garbage;
    if(scanf("%d%c", &num, &garbage) != 1 && garbage != '\n'){
        printf("n/a");
        return 1;
    }
    num = my_abs(num);
    find_max_primary_div(num);
    return 0;
}

void find_max_primary_div(int inpunt_value){
    if(inpunt_value == 0){
        printf("n/a");
        } else if(is_prime(inpunt_value)){
            printf("%d", inpunt_value);
        }
    else{
        int flag = 0;
        for(int i = (inpunt_value / 2); i > 1 && !flag; --i){
            if(is_prime(i)){
                int tmp = inpunt_value;
                while(tmp > 0) {
                    tmp -= i;
                }

                if(tmp == 0){
                    printf("%d", i);
                    flag = 1;
                }
            }
        }
        if(flag == 0){
            printf("n/a");
        }
    }   
}

int is_prime(int num){
        if(num < 4){
            return 1;
        }

        for(int i = 2; i < num; ++i){
            int tmp = i;

            while(tmp < num){
                tmp += i;

            if(tmp == num){
                return 0;
            }
        }
    }

    return 1;
}