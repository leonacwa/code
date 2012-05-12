// C  Matrix
#include <stdio.h>

#define MAXN 101
int A[MAXN][MAXN], B[MAXN][MAXN];

void input(int A[MAXN][MAXN], int m, int n) {
    int i, j;
    for (i = 0; i < m; ++i)
        for(j = 0; j < n; ++j)
            scanf("%d", &A[i][j]);
}

int main()
{
    int i, j, k, ij;
    int m, n, p;
    while (EOF != scanf("%d %d %d", &m, &n, &p)) {
        //while (!(m & n & p)) puts("fuck you.");
        input(A, m, n);
        input(B, n, p);
        for (i = 0; i < m; ++i) {
            for (j = 0; j < p; ++j) {
                ij = 0;
                for (k = 0; k < n; ++k) {
                    ij += A[i][k] * B[k][j];
                }
                if (j < p-1)
                    printf("%d ", ij);
                else
                    printf("%d\n", ij);
            }
        }
    }
    return 0;
}
