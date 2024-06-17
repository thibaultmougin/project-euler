#include <stdio.h>
#include <stdlib.h>

typedef struct splitting{
    long long arr[2];
}splitting;

void print_partition(splitting part){
    printf("%d, %d ", part.arr[0], part.arr[1]);
    printf("\n");
}

int nbchiffres(long long n){
    int res = -1;
    while (n>0){
        n /= 10;
        res++;
    }
    return res;
}

long long pui(int n, int exponent){
    long long res = 1;
    for (int i = 0;i < exponent;i++){
        res *=n;
    }
    return res;
}


splitting* split_number(long long n){
    unsigned long pui_dix;
    splitting shifted;
    int nb_chiffres = nbchiffres(n);
    splitting* res = malloc(sizeof(splitting)*nb_chiffres);
    for (int i =1;i<=nb_chiffres;i++){
        pui_dix = pui(10,i);
        shifted.arr[0] = n/pui_dix;
        shifted.arr[1] = n%pui_dix;
        res[i-1] = shifted;
    }
    return res;
}

int sum_partition(splitting part){
    long long res = 0;
    for (int i =0;i<2;i++){
        res += part.arr[i];
    }
    return res;
}

int isSnumber(long long n, long long target){
    if (n==target){
        return 1;
    }
    if (target < 0){
        return 0;
    }
    splitting* parts = split_number(n);

    int nbchif = nbchiffres(n);

    for (int i =1;i<nbchif+1;i++){
        int sign = i%2 ? 1: -1;
        int k = nbchif/2 + sign*i/2;

        long long sum = sum_partition(parts[k]);
        if (sum ==target){
            return 1;
        }
        else if(sum>target){

            if (isSnumber(parts[k].arr[0], target-parts[k].arr[1])){
                return 1;
            }
            if (isSnumber(parts[k].arr[1], target-parts[k].arr[0])){
                return 1;
            }
        }
        //else{printf("ABANDON\n");}
    }
    return 0;
}

int main(void){

    long long res = 0;
    int num = 0;

    for (long long n = 2;  n <=pui(10,2) ; n++){
        int ok = isSnumber(n*n,n);
        if (ok==1){
            printf("%d\n", n);
            res+=n*n;
            num ++;
        }
    }

    printf("res = %d\n", res);
    printf("num = %d\n", num);

    //printf("%d", isSnumber(657*657,657));

    return 0;
}
