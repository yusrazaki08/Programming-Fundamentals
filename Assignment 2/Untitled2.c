#include <stdio.h>
int sum_proper_divisors(int num) {
    int sum = 0;
    int i;
    for(i = 1; i <= num / 2; i++) {
        if(num % i == 0) {
            sum += i;
        }
    }
    return sum;
}

int main() {
    int n, a, b, sum_a, sum_b;
    int count = 0;

    printf("Enter n: ");
    scanf("%d", &n);

    printf("Amicable pairs up to %d:\n", n);

    for(a = 1; a <= n; a++) {
        sum_a = sum_proper_divisors(a);
        
        b = sum_a;
        if(a < b && b <= n) {
            sum_b = sum_proper_divisors(b);
            
            if(sum_b == a) {
                printf("(%d, %d)\n", a, b);
                count++;
            }
        }
    }

    if(count > 0) {
        printf("Total pairs: %d\n", count);
    } 
    else {
        printf("No amicable pairs found up to %d.\n", n);
    }

    return 0;
}
