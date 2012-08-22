/*
 * HDU 4069 Squiggly Sudoku
 * Dancing Link  X Algorithm 
 * */

#include <stdio.h>
#include <string.h>

const int n = 9;
const int MAX_COL = n*n*4;
const int MAX_ROW = n*n*n;
struct Node {
	int r, c;
	Node *U, *D, *L, *R;
};
Node node[MAX_ROW * MAX_COL+1], row[MAX_ROW+1], col[MAX_COL+1], head;
int cnt, size[MAX_COL];
int block[n][n], map[n][n], ans[n][n], cnt_ans;

const int _x[4] = {-1, 0, 1, 0}; // up  right down left
const int _y[4] = {0, 1, 0, -1};
void dfs_ss(int x, int y, int id) 
{
	if (x < 0 || x >= n || y < 0 || y >= n || block[x][y] != -1) return;
	int i;
	block[x][y] = id;
	for (i = 0; i < 4; ++i) {
		if ((map[x][y] & (1<<(4+i))) == 0) {
			dfs_ss(x+_x[i], y+_y[i], id);
		}
	}
}

void init(int r, int c)
{
	int i;
	cnt = 0;
	head.r = r;
	head.c = c;
	head.L = head.R = head.D = head.U = &head;
	for (i = 0; i < c; ++i) {
		col[i].r = r;
		col[i].c = i;
		col[i].L = &head;
		col[i].R = head.R; /// !!!!!!!!!!!!!!!
		col[i].U = col[i].D = col[i].L->R = col[i].R->L = &col[i];
		size[i] = 0;
	}
	for (i = 0; i < r; ++i) { // row is not necessary, but it is convenience !!!!!!!!!!!!!!!!!
		row[i].r = i;
		row[i].c = c;
		row[i].U = &head;
		row[i].D = head.D; /// !!!!!!!!!!!!!!!
		row[i].L = row[i].R = row[i].U->D = row[i].D->U = &row[i];
	}
}
void insert(int r, int c)
{
	Node *p = &node[cnt++];
	p->r = r;
	p->c = c;
	p->L = row[r].L;
	p->R = &row[r];
	p->L->R = p->R->L = p;
	p->U = col[c].U;
	p->D = &col[c];
	p->U->D = p->D->U = p;
	++size[c];
}
void fill(int i, int j, int k)
{
	int r = (i*n+j)*n + k - 1;
	insert(r, i*n + k - 1); // row, row_k
	insert(r, n*n + j*n + k-1); // row, col+k
	insert(r, n*n*2 + block[i][j]*n + k-1); // row, block_k
	insert(r, n*n*3 + i*n+j); // row, [i][j]_k
}
void del_LR(Node *p)
{
	p->L->R = p->R;
	p->R->L = p->L;
}
void res_LR(Node *p)
{
	p->L->R = p;
	p->R->L = p;
}
void del_UD(Node *p)
{
	p->U->D = p->D;
	p->D->U = p->U;
}
void res_UD(Node *p)
{
	p->U->D = p;
	p->D->U = p;
}
void cover(int c)
{
	if (c == MAX_COL) 
		return;
	Node *R, *C;
	del_LR(&col[c]);
	for (R = col[c].D; R != &col[c]; R = R->D) {
		for (C = R->L; C != R; C = C->L) {
			--size[C->c];
			del_UD(C);
		}
	}
}
void resume(int c)
{
	if (c == MAX_COL) 
		return;
	Node *R, *C;
	for (R = col[c].U; R != &col[c]; R = R->U) {
		for (C = R->R; C != R; C = C->R) {
			++size[C->c];
			res_UD(C);
		}
	}
	res_LR(&col[c]);
}
int dfs(int k)
{
	if (head.R == &head) {
		cnt_ans++;
		if (cnt_ans == 2) 
			return 1;
		return 0;
	}
	int r, c=0, min_size = ~0u>>1;
	Node *p, *rc;
	for (p = head.R; p != &head; p = p->R) {
		if (min_size > size[p->c])
			min_size = size[c = p->c];
	}
	if (min_size == 0) 
		return 0;
	cover(c);
	for (p = col[c].D; p != &col[c]; p = p->D) {
		for (rc = p->L; rc != p; rc = rc->L) 
			cover(rc->c);
		r = p->r;
		if (cnt_ans == 0)
			ans[r/(n*n)][r/n%n] = r % n + 1;
		if (dfs(k+1)) 
			return 1;
		for (rc = p->R; rc != p; rc = rc->R)
			resume(rc->c);
	}
	resume(c);
	return 0;
}

int main()
{
	int nCase, cs;
	int i, j, k, id_ss;
	scanf("%d", &nCase);
	for (cs = 1; cs <= nCase; ++cs) {
		init(MAX_ROW, MAX_COL);
		for (i = 0; i < n; ++i) {
			for (j = 0; j < n; ++j) {
				scanf("%d", &map[i][j]);
			}
		}
		memset(block, -1, sizeof(block));
		id_ss = 0;
		for (i = 0; i < n; ++i) {
			for (j = 0; j < n; ++j) {
				if (block[i][j] == -1) {
					dfs_ss(i, j, id_ss++);
				}
			}
		}
		for (i = 0; i < n; ++i) {
			for (j = 0; j < n; ++j) {
				k = map[i][j] & 15;
				if (k) 	{
					fill(i, j, k);
				}
				else {
					for (k = 1; k <= n; ++k) fill(i, j, k);
				}
			}
		}
		cnt_ans = 0;
		dfs(0);
		printf("Case %d:\n", cs);
		if (cnt_ans == 0) puts("No solution");
		else if (cnt_ans == 1) {
			for (i = 0; i < n; ++i) {
				for (j = 0; j < n; ++j) {
					printf("%d", ans[i][j]);
				}
				puts("");
			}
		}
		else puts("Multiple Solutions");
	}
	return 0;
}
