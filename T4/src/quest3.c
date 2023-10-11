#include <stdio.h>

int fibonacci(int n){
    return n < 2 ? n : fibonacci(n-2) + fibonacci(n-1);
}

int main(){
    int n;
    char garbage;
    if(scanf("%d%c", &n, &garbage) == 2 && garbage == '\n' && n > 0){
        n = fibonacci(n);
        printf("%d", n);
        return 0;
    } else {
        printf("n/a");
        return 1;
    }
}

/*
0: 0
1: 1
2: 1
3: 2
4: 3
5: 5
6: 8
7: 13
8: 21
9: 34


fibonacci( 6 ) = fibonacci( 5 ) + fibonacci( 4 )  
fibonacci( 5 ) = fibonacci( 4 ) + fibonacci( 3 )  
fibonacci( 4 ) = fibonacci( 3 ) + fibonacci( 2 )  
fibonacci( 3 ) = fibonacci( 2 ) + fibonacci( 1 )
fibonacci( 2 ) = fibonacci( 1 ) + fibonacci( 0 )
fibonacci( 1 ) = 1
fibonacci( 0 ) = 0


                                       6
                  ------------------------------------------
                 |                                          |
                 4                     +                    5
        -------------------                        -------------------
       |                   |                      |                   |
       2         +         3                      3        +          4
   ---------           ---------              ---------           ---------
  |         |         |         |            |         |          |        | 
  0    +    1         1    +    2            1   +     2          2   +    3
                              -----                  -----      -----    -----
                             |     |                |     |    |     |  |     | 
                             0  +  1                0  +  1    0  +  1  1  +  2
                                                                            ----- 
                                                                           |     |
                                                                           0  +  1

*/