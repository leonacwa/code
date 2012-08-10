 1008 ( SanguoSHA )     Judge Status : Accepted
RunId : 2302    Language : C++    Author : 
Code Render Status : Rendered By HDOJ C++ Code Rander Version 0.01 Beta
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string>
#include <algorithm>
#include <map>
using namespace std;
struct ptrCMP {
    bool operator()(const char * a, const char * b) const {
        return strcmp(a, b) < 0;
    }
};
map<char *, int, ptrCMP> uid;
struct NODE {
    char name[25];
} nlist[10];
int rst[10][10];
bool cmp(const NODE &a, const NODE &b) {
    return strcmp(a.name, b.name) < 0;
}
int alist[800][10];
int buf[10], used[10];
int cnt, tn;
void dfs(int np) {
    int i;
    if (np == tn) {
        for (i = 0; i < tn; i++) {
            alist[cnt][i] = buf[i];
        }
        cnt++;
    } else {
        for (i = 0; i < tn; i++) {
            if (!used[i]) {
                used[i] = 1;
                buf[np] = i;
                dfs(np + 1);
                used[i] = 0;
            }
        }
    }
}
int test(int fi, int fj, int n) {
    int myid = 0, oid = 0;
    while (myid < n && oid < n) {
        if (rst[alist[fj][oid]][alist[fi][myid]]) {
            myid++;
        } else {
            oid++;
        }
    }
    if (myid < n) {
        return 1;
    } else {
        return 0;
    }
}
int main() {
    int f, i, j, n, k, id, cs;
    char str[25];
    scanf("%d", &f);
    for (cs = 1; cs <= f; cs++) {
        uid.clear();
        memset(rst, 0, sizeof(rst));
        scanf("%d", &n);
        for (i = 0; i < n; i++) {
            scanf("%s", nlist[i].name);
        }
        sort(nlist, nlist + n, cmp);
        for (i = 0; i < n; i++) {
            uid[nlist[i].name] = i;
        }
        for (i = 0; i < n; i++) {
            scanf("%d", &k);
            for (j = 0; j < k; j++) {
                scanf("%s", str);
                id = uid[str];
                rst[i][id] = 1;
            }
        }
        cnt = 0;
        tn = n;
        memset(used, 0, sizeof(used));
        dfs(0);
        for (i = 0; i < cnt; i++) {
            for (j = 0; j < cnt; j++) {
                if (!test(i, j, n)) {
                    break;
                }
            }
            if (j == cnt) {
                break;
            }
        }
        printf("Case %d: ", cs);
        if (i == cnt) {
            puts("No");
        } else {
            puts("Yes");
            printf("%s", nlist[alist[i][0]].name);
            for (k = 1; k < n; k++) {
                printf(" %s", nlist[alist[i][k]].name);
            }
            putchar('\n');
        }
    }
}

