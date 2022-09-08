#include <stdio.h>


// функция, для подсчета количества вхождения цифры в числе
int count_elements(int n, int element) {
    int ans = 0;
    while (n > 0) {
        if (n % 10 == element)
            ans++;
        n /= 10;
    }
    return ans;
}


int main() {
    int n;
    // получаем значение n из потока ввода (%d - означает, что ввод состоит только из цифры)
    scanf("%d", &n);
    // создаем переменные, которые будем использовать в коде
    // в x будем хранить копию введенного n
    // в min_local сохраним минимальную ненулевую цифру из исходного числа
    int x = n;
    int min_local = 10;
    // найдем min_local
    while (x > 0) {
        if (x % 10 != 0 && x % 10 < min_local)
            min_local = x % 10;
        x /= 10;
    }
    int ans = min_local;

    // теперь для каждой возможной цифры посчитаем количество вхождений ее в начальное число
    // и прибавим их с соответствующим разрядом в порядке возрастания
    for (int i = 0; i < 10; ++i) {
        int new_iterator = count_elements(n, i);
        if (i == min_local)
            new_iterator -= 1;  // не забудем, что одно ненулевое число мы уже добавили в ответ
        for (int j = 0; j < new_iterator; ++j) {
            ans = ans * 10 + i;
        }
    }
    // выводим ответ
    printf("%d", ans);
    return 0;
}
