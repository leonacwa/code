/* The Social Network */
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <algorithm>
using namespace std;

#define MAXN 2001
#define MAX_NODES (16*MAXN)

struct Trie {
    int a[26], id;
    void init()
    {
        memset(a, -1, sizeof(a));
        id = -1;
    }
};
Trie node[MAX_NODES];
int node_up;

struct Edge{
    int v, next;
};
Edge edge[MAXN*2];
int vv[MAXN];
int edges;

struct Relate{
    int id, count;
};
Relate rel[MAXN];
int rels;
char vis[MAXN];

char name[MAXN][16];
int names;

bool cmp_rel(const Relate&a, const Relate&b)
{
    if (a.count != b.count) return a.count > b.count;
    return strcmp(name[a.id], name[b.id]) < 0;
}

int insert(const char *s)
{
    int p = 0;
    while (*s) {
        if (node[p].a[*s - 'a'] == -1) {
            while (node_up >= MAX_NODES) puts("fuck you!");
            node[node_up].init();
            node[p].a[*s - 'a'] = node_up++;
        }
        p = node[p].a[*s - 'a'];
        s++;
    }
    if (node[p].id != -1) return node[p].id;
    node[p].id = names++;
    return names-1;
}

int query(const char *s)
{
    int p = 0;
    while (*s) {
        if (node[p].a[*s - 'a'] == -1) return -1;
        p = node[p].a[*s - 'a'];
        s++;
    }
    return node[p].id;
}

void push_edge(int u, int v)
{
    edge[edges].v = v;
    edge[edges].next = vv[u];
    vv[u] = edges++;
    edge[edges].v = u;
    edge[edges].next = vv[v];
    vv[v] = edges++;
}

void recommend(int p)
{
    Relate rel_tmp;
    int i, j, u, v, Max = 0;
    memset(vis, 0, sizeof(vis));
    memset(rel, 0, sizeof(rel));
    for (i = 0; i < names; i++)  rel[i].id = i;
    vis[p] = 1;
    for (i = vv[p]; i != -1; i = edge[i].next) {
        vis[edge[i].v] = 1;
    }
    for (i = vv[p]; i != -1; i = edge[i].next) {
        u = edge[i].v;
        for (j = vv[u]; j != -1; j = edge[j].next) {
            v = edge[j].v;
            if (!vis[v]) {
                rel[v].count++;
                if (Max < rel[v].count) Max = rel[v].count;
            }
        }
    }
    rels = 0;
    for (i = 0; i < names; i++) {
        if (rel[i].count == Max) rel[rels++] = rel[i];
    }
    sort(rel, rel+rels, cmp_rel);
}

int main()
{
    int cs, tt;
    int i, j, Max, n, q, p1, p2;
    char str1[256], str2[256];
    scanf("%d", &tt);
    for (cs = 1; cs <= tt; cs++) {
        printf("Case %d:\n", cs);
        names = 0;
        node[0].init();
        node_up = 1;
        edges = 0;
        memset(vv, -1, sizeof(vv));

        scanf("%d %d", &n, &q);
        for (i = 0; i < n; i++) {
            scanf("%s %s", str1, str2);
            j = names;
            p1 = insert(str1);
            if (p1 == j)  strcpy(name[j], str1);
            j = names;
            p2 = insert(str2);
            if (p2 == j)  strcpy(name[j], str2);
            push_edge(p1, p2); //printf("%s %s, %d %d\n", str1, str2, p1, p2);
        }
        for (i = 0; i < q; i++) {
            scanf("%s", str1);
            recommend(query(str1));// printf("recomend %s  %d\n", str1, query(str1));
            Max = rel[0].count;
            if (Max == 0) printf("-\n");
            else {
                printf("%s", name[rel[0].id]);
                for (j = 1; j < rels; j++) {
                    if (Max == rel[j].count) printf(" %s", name[rel[j].id]);
                    else break;
                }
                printf("\n");
            }
        }
    }
    return 0;
}
