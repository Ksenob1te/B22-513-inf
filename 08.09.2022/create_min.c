#include <stdio.h>


int count_elements(int n, int element) {
    int ans = 0;
    while (n > 0) {
        if (n % 10 == element)
            ans++;
        n /= 10;
    }
    return ans;
}

int find_first(int x) {
    int min_local = 10;
    while (x > 0) {
        if (x % 10 != 0 && x % 10 < min_local)
            min_local = x % 10;
        x /= 10;
    }
    return min_local;
}


void fill_result(const int* min_local, int* ans, const int* n) {
    for (int i = 0; i < 10; ++i) {
        int new_iterator = count_elements(*n, i);
        if (i == *min_local)
            new_iterator -= 1;
        for (int j = 0; j < new_iterator; ++j) {
            *ans = *ans * 10 + i;
        }
    }
    printf("%d", *ans);
}


int main() {
    int n = 0;
    int scan_result = scanf("%d", &n);
    if (scan_result <= 0) {
        printf("input_fail\n");
        return 0;
    }
    int min_local = find_first(n);
    int ans = min_local;

    fill_result(&min_local, &ans, &n);
    return 0;
}
