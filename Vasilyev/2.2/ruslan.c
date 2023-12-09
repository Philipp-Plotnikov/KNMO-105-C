#include <stdio.h>
#include <math.h>
#define N 100

int main(){
    double x, q=1, s=1;
    int n=1;
    printf("type x:\n");
    scanf("%lf", &x);
    for(n;n<=N;n++){
        q*=x/n;
        s+=q;
    }
    printf("ruslan's exp(x)=%lf\n", s);
    printf("exp(x)=%lf", exp(x));
    return 0;
}
