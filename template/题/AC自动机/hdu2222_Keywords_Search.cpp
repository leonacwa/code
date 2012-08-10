/*
 * hdu2222 Keywords Search
 * 多串匹配，AC自动机入门题
 * AC自动机是用来处理多串匹配问题的，
 * 即给你很多串，再给你一篇文章，让你在文章中找这些串是否出现过，在哪出现。
 * 学AC自动机，先学KMP，理解next数组的含义，这里的fail指针与next数组相似
 **/

#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

const int MAXN = 50 * 10000 + 100;
const int MAX_CHILD = 26;

struct Node {
    int cnt;
    Node *son[MAX_CHILD];
    Node *fail;
} nd[MAXN];
int nd_cnt;
int ch_num[256];

Node* newNode()
{
    Node *p = nd + nd_cnt++;
    memset(p, 0, sizeof(Node));
    return p;
}

void insert(Node *root, const char *s)
{
    Node *p = root;
    while (*s) {
        int i = ch_num[*s];
        if (p->son[i] == NULL) {
            p->son[i] = newNode();
        }
        p = p->son[i];
        ++s;
    }
    p->cnt++; // 居然会有重复字符串
}

Node* Q[MAXN];
void AC_construct(Node *root)
{
    int f = 0, r = 0;
    Node *q = root;
    for (int i = 0; i < MAX_CHILD; ++i) {
        if (q->son[i]) {
            q->son[i]->fail = root;
            Q[r++] = q->son[i];
        } else {
            q->son[i] = root;
        }
    }
    while (f < r) {
        q = Q[f++];
        for (int i = 0; i < MAX_CHILD; ++i) {
            if (q->son[i]) {
                Q[r++] = q->son[i];
                Node * v = q->fail;
                while (v->son[i] == NULL) v = v->fail;
                q->son[i]->fail = v->son[i];
            } else {
                q->son[i] = q->fail->son[i];
            }
        }
    }
}

int AC_find(Node *root, const char *s)
{
    int ret = 0;
    Node *q = root, *p;
    while (*s) {
        int i = ch_num[*s];
        while (q->son[i] == NULL) q = q->fail;
        q = q->son[i];
        p = q;
        while (p != root && p->cnt != -1) {
            ret += p->cnt;
            p->cnt = -1;
            p = p->fail;
        }
        ++s;
    }
    return ret;
}

char str[1000000+100];

int main()
{
    for (int i = 0; i < MAX_CHILD; ++i) ch_num[i+'a'] = i;
    int nTest;
    scanf("%d", &nTest);
    while (nTest--) {
        nd_cnt = 0;
        Node *root = newNode();
        int n;
        scanf("%d", &n);
        for (int i = 0; i < n; ++i) {
            scanf("%s", str);
            insert(root, str);
        }
        scanf("%s", str);
        AC_construct(root);
        printf("%d\n", AC_find(root, str));
    }
    return 0;
}
