/* Jigsaw Puzzle */
#include <stdio.h>
#include <string.h>

#define MAX_STATE (9*8*7*6*5*4*3*2*1)

struct State {
    char str[10];
    int code;
};

const int fac[9] = {0, 1, 2, 6, 24, 120, 720, 5040, 40320};
const char target[10] = "012345678";

int hash[MAX_STATE + 1];
State Q[MAX_STATE];
int head, tail;

int hashcode(const char *s)
{
    int code = 0, i, j, cnt;
    for (i = 0; i < 9; i++) {
        cnt = 0;
        for (j = i+1; j < 9; j++) if (s[i] > s[j]) cnt++;
        code += fac[9-i-1] * cnt;
    }
    return code;
}

int move(int p, char* dest)
{
    int i, ii = -1;
    char c;
    for (i = 0; i < 9; i++) if (dest[i] == '0') break;
    if (p == 0) { // up
        if (i >= 3) ii = i - 3;
    } else
    if (p == 1) {  // down
        if (i <= 5) ii = i + 3;
    } else
    if (p == 2) { // left
        if (i != 0 && i != 3 && i != 6) ii = i - 1;
    } else
    if (p == 3) { // right
        if (i != 2 && i != 5 && i != 8) ii = i + 1;
    }
    if (ii == -1) return 0;
    c = dest[i];
    dest[i] = dest[ii];
    dest[ii] = c;
    return 1;
}

void pre_work()
{
    int i, code;
    head = 0, tail = 1;
    memset(hash, -1, sizeof(hash));
    code = hashcode(target);
    hash[code] = 0;
    strcpy(Q[0].str, target);
    Q[0].code = code;
    while (head < tail) {
        for (i = 0; i < 4; i++) {
            Q[tail] = Q[head];
            if (move(i, Q[tail].str)) {
                code = hashcode(Q[tail].str);
                if (hash[code] == -1) {
                    hash[code] = hash[Q[head].code]  + 1;
                    Q[tail].code = code;
                    tail++;
                }
            }
        }
        head++;
    }
}

int main()
{
    int code;
    char str[10];
    pre_work();
    while (1 == scanf("%s", str)) {
        code = hashcode(str);
        //printf("%s ", str);
        if (hash[code] == -1) printf("NO\n");
        else printf("%d\n", hash[code]);
    }
    return 0;
}
