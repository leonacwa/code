/* poj 1030 Rating */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAXN 128
typedef struct _Team {
    int r[2];
    int id, rank;
} Team;
Team tm[MAXN], _team;
Team rk[MAXN];
int N, rs;

int in_contest(const Team*t)
{
    return (t->r[0] + t->r[1]) > 0;
}
int twice(const Team*t)
{
    return t->r[0] > 0 && t->r[1] > 0;
}
int get_k(const Team*t)
{
    if (t->r[0]) return 0;
    if (t->r[1]) return 1;
}
int get_r(const Team*t, int k)
{
    if (t->r[k] > 0) {
        return t->r[k];
    }
    return t->r[1-k];
}
void p_ans()
{
    int i, rank = 0;
    printf("%d", rk[0].id);
    rank = rk[0].rank;
    for (i = 1; i < rs; i++) {
        printf("%s%d", rank == rk[i].rank?" ":"\n", rk[i].id, rk[i].rank);
        rank = rk[i].rank;
    }
}
int main()
{
    int n, i, j, k, t, rank, id, ret, pj;
    char buf[3*MAXN], *ptr;

    memset(tm, 0, sizeof(tm));
    for (N= 0, k = 0; k < 2; k++) {
        scanf("%d", &n);
        gets(buf);
        rank = 1;
        for (i = 0; i < n; i++) {
            j = 0;
            gets(buf);
            ptr = strtok(buf, " ");
            while (ptr != NULL) {
                j++;
                id = atoi(ptr);
                if (id > N)
                    N = id;
                tm[id].r[k] = rank;
                tm[id].id = id;
                ptr = strtok(NULL, " ");
            }
            rank += j;
        }
        gets(buf);
    }

    rs = 0;
    for (i = 1; i<= N; i++) if (twice(&tm[i])) {
        rk[rs++] = tm[i];
        tm[i].r[0] = tm[i].r[1] = 0;
    }
    rk[0].rank = 1;
    rank = 0;
    for (i = 0; i < rs-1; i++) {
        k = i;
        for (j = i+1; j < rs; j++) {
            ret = rk[k].r[0]+rk[k].r[1] - (rk[j].r[0]+rk[j].r[1]);
            if (ret > 0 || (ret == 0 && rk[k].id > rk[j].id)) { // sort by id
                k = j;
            }
        }
        if (k != i) {
            _team = rk[k];
            rk[k] = rk[i];
            rk[i] = _team;
        }
        if (i > 0 && rk[i].r[0]+rk[i].r[1] == rk[i-1].r[0]+rk[i-1].r[1]) {
            rk[i].rank = rk[i-1].rank;
        }
        else {
            rk[i].rank = rk[i-1].rank + 1;
        }
    }
    if (rs > 1) {
        i = rs - 1;
        rk[rs-1].rank = rk[rs-2].rank + (rk[i].r[0]+rk[i].r[1] != rk[i-1].r[0]+rk[i-1].r[1]);
    }
/// rule A
    for (i = 1; i <= N; i++) if (in_contest(&tm[i]) && !twice(&tm[i])) {
        k = get_k(&tm[i]);
        for (j = 0; j < rs; j++) {
            if (tm[i].r[k] == rk[j].r[k]) {
                break;
            }
        }
        if (j < rs) {
            for ( t = j+1; t < rs; t++) {
                if (tm[i].r[k] == rk[t].r[k] && rk[t].rank != rk[j].rank) {
                    break;
                }
            }
            if (t < rs) {
                tm[i].r[0] = tm[i].r[1] = 0;
            }
            else {
                tm[i].rank = rk[j].rank;
                for (t = rs; t > j; t--) {
                    rk[t] = rk[t-1];
                }
                rs++;
                rk[j] = tm[i]; /*then*/
                tm[i].r[0] = tm[i].r[1] = 0;

                for (; j < rs-1; j++) {  // sort by id
                    if (rk[j].rank == rk[j+1].rank && rk[j].id > rk[j+1].id) {
                        _team = rk[j];
                        rk[j] = rk[j+1];
                        rk[j+1] = _team;
                    }
                    else {
                        break;
                    }
                }

            }
        }
    }

/// rule B  B规则写得吐血
    for (i = 1; i <= N; i++) if (in_contest(&tm[i]) && !twice(&tm[i])) {
        k = get_k(&tm[i]);
        pj = -1;
        for (j = 0; j < rs; j++) {
            if (rk[j].r[k] > 0) {
                if (tm[i].r[k] <= rk[j].r[k]) { /** 初步找到一个位置 */
                    break;
                }
                pj = j;
            }
        }
        if (j < rs) {
            for (t = 0; t < j; t++) {
              if (rk[t].r[k] > 0) {
                  if (rk[t].rank == rk[j].rank) { /** 是否放得下i*/
                      break;
                  }
              }
            }
            if (t < j) {
                continue;
            }
        }

        for (t = j+1; t < rs; t++) {
            if (rk[t].r[k] > 0) {
                if (tm[i].r[k] > rk[t].r[k]) { /** i是否违反排序*/
                    break;
                }
            }
        }
        if (t < rs) {
            continue;
        }
        /** 正式开始寻找位置 */
        if (tm[i].r[k] != rk[j].r[k] || (j > 0 && rk[j-1].rank == rk[j].rank)) {
            for (t = pj+1; t < j; t++) if (pj < 0 || (rk[t].rank != rk[pj].rank)) {
                if (((rk[t].r[k] == 0) && (tm[i].r[k] <= rk[t].r[1-k])) ||
                    rk[j].rank == rk[t].rank ) {
                    j = t;
                    break;
                }
            }
        }
        if (j < rs)
            rank = rk[j].rank;
        else
            rank = rk[j-1].rank + 1;
        for (t = rs; t > j; t--) {
            rk[t] = rk[t-1];
            if (rk[t].rank != rank || get_r(&rk[t], k) != tm[i].r[k])
                rk[t].rank++;
        }
        rs++;
        tm[i].rank = rank;
        rk[j] = tm[i];

        for (; j < rs-1; j++) { // sort by id
            if (rk[j].rank == rk[j+1].rank && rk[j].id > rk[j+1].id) {
                _team = rk[j];
                rk[j] = rk[j+1];
                rk[j+1] = _team;
            }
            else  {
                break;
            }
        }
    }
    p_ans();
    return 0;
}
