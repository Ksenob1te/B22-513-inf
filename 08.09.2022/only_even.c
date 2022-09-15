#include <stdio.h>


void task(int* n) {
    int ans = 0, t_pow = 1;
    while (*n > 0) {
        if ((*n % 10) % 2 == 0) {
            ans += *n % 10 * t_pow;
            t_pow *= 10;
        }
        *n /= 10;
    }
    printf("%d", ans);
}


int main() {
    int n = 0;
    int scan_result = scanf("%d", &n);
    if (scan_result <= 0) {
        printf("input_fail");
        return 0;
    }
    task(&n);
    return 0;
}
