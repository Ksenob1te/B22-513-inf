#include <stdio.h>

double count_row(const double x, const int n) {
    double xSquared = x * x;
    double answer = x, mult = x;
    for (int i = 3; i <= n; i += 2) {
        mult = -mult * (xSquared / (i * (i - 1)));
        answer += mult;
    }
    return answer;
}

int main() {
    double x = 0;
    int n = 0;
    printf("Type x and n\n");
    int input_status = scanf("%lf%d", &x, &n);
    if (input_status <= 1) {
        printf("Incorrect Input");
        return 0;
    }
    // lg(2 ^ 52) == 15
    printf("%.15f", count_row(x, n));
    return 0;
}
