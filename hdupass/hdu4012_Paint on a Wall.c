/*Paint on a Wall
BFS + 位压缩，状态记为每个位置是否为目标颜色*/
#include <stdio.h>
#include <string.h>
#define MAXN (1<<20)
int q[MAXN];
int len[MAXN];
int head, tail;
char tar[2][9];
int n;

void push(int v) { q[tail++] = v;}
void pop(){head++;}
int front() {return q[head];}
int get_bit(int v, int i) {return v&(1<<i);}

int change(int top, int h1, int w1, int h2, int w2, char color)
{
    int i, j, code = top;
    for (i = h1; i < h2; i++) {
        for (j = w1; j < w2; j++) {
            if (color == tar[i][j])
                code |= (1<<(2*j+i));
            else
                code &= ~(1<<(2*j+i));
        }
    }
    return code;
}
int main()
{
    int tt, cs;
    int i, j, target, new_code, top, w;
    scanf("%d", &tt);
    for (cs = 1; cs <= tt; cs++) {
        scanf("%d%s%s", &n, tar[0], tar[1]);
        memset(len, -1, sizeof(len));
        target = (1<<(2*n)) - 1;
        head = tail = 0;
        push(0);
        len[0] = 0;
        while (head < tail) {
            top = front();
            pop();
            if (top == target) {break;}
            for (i = 0; i < n; i++) {
                if (!get_bit(top, 2*i)) {
                    for (w = 1; w <= n-i; w++) {
                        new_code = change(top, 0, i, 1, i+w, tar[0][i]);
                        if (len[new_code] == -1) {
                            len[new_code] = len[top] + 1;
                            push(new_code);
                        }
                        new_code = change(top, 0, i, 2, i+w, tar[0][i]);
                        if (len[new_code] == -1) {
                            len[new_code] = len[top] + 1;
                            push(new_code);
                        }
                    }
                }
                if (!get_bit(top, 2*i + 1)) {
                    for (w = 1; w <= n-i; w++) {
                        new_code = change(top, 1, i, 2, i+w, tar[1][i]);
                        if (len[new_code] == -1) {
                            len[new_code] = len[top] + 1;
                            push(new_code);
                        }
                        new_code = change(top, 0, i, 2, i+w, tar[1][i]);
                        if (len[new_code] == -1) {
                            len[new_code] = len[top] + 1;
                            push(new_code);
                        }
                    }
                }
            }
        }
        printf("Case #%d: %d\n", cs, len[target]);
    }
    return 0;
}
