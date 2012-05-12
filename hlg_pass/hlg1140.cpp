#include <stdio.h>

int get_1(int a) {
    int s;
    while (a >= 10) {
        s = 0;
        while (a > 0) {
            s += a % 10;
            a /= 10;
        }
        a = s;
    }
    return a;
}

int get_2(int a, int b) {
    int s;
    if (b == 1) return get_1(a);
    else s = get_2(a, b/2);
    s = s * s;
    if (b % 2 == 1) s *= get_1(a);
    return get_1(s);
}

int main()
{
    int a, b, c;
    while (2 == scanf("%d %d", &a, &b)) {
        a = get_1(a);
        printf("%d\n", get_2(a, b));
    }
    return 0;
}
