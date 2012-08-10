/*
   2011 ACM/ICPC Fuzhou Online
   Squiggly Sudoku
   */
#include <stdio.h>
#include <string.h>

int wall[4] = {16, 32, 64, 128};
int _x[4] = {-1, 0, 1, 0};
int _y[4] = {0, 1, 0, -1};

int map[9][9];
int desc[9][9];
int ss[9][9];

int col[9];
int row[9];
int block[9];
int grid[9];

int hx[81], hy[81], h_cnt;
int ans_cnt;

#define bit_set(x, n)   ( (x) |= (1<<(n)) )
#define bit_set_0(x, n) ( (x) &= ~(1<<(n)) )
#define bit_test(x, n)  ( (x) & (1<<(n))  )
#define block_id(x, y)  ( (x)/3*3 + (y)/3 )

/*
   inline void bit_set(int &x, int n)   { x |= (1 << n);  } 
   inline void bit_set_0(int &x, int n) { x &= ~(1 << n);  } 
   inline int bit_test(int x, int n)  { return x &  (1 << n);  }
   inline int block_id(int x, int y)  { return (x/3)*3 + y/3;  }
*/

void dfs_ss(int x, int y, int id)
{	
	int i, n;
	if (ss[x][y] != -1 || x < 0 || x >= 9 || y < 0 || y >= 9)  return;
	ss[x][y] = id;
	n = desc[x][y] & 15;
	map[x][y] = n;
	if (n == 0) {
		hx[h_cnt] = x;
		hy[h_cnt] = y;
		h_cnt++;
		//printf("%d:%d, %d   ", h_cnt,  x, y);
	} 
	else {
		bit_set(col[y], n);
		bit_set(row[x], n);
		bit_set(block[block_id(x,y)], n);
		bit_set(grid[id], n);
	}

	for (i = 0; i < 4; ++i) {
		if ((desc[x][y] & wall[i]) == 0) {
			dfs_ss(x+_x[i], y+_y[i], id);
		}
	}
}

void dfs(int k)
{
	int i, j, x, y;
	if (k == h_cnt) {
		ans_cnt++;
		if (ans_cnt == 1) {
			for (i = 0; i < 9; ++i ) {
				for (j = 0; j < 9; ++j) {
					desc[i][j] = map[i][j];
					printf("%d", map[i][j]);
				}
				printf("\n");
			}
		}
		return;
	}
	x = hx[k];
	y = hy[k];
	if (map[x][y] != 0) for(;;) printf("error\n");
	for (i = 1; i <= 9; ++i) {
		if (  !(bit_test(col[y], i) || bit_test(row[x], i) 
			|| bit_test(block[block_id(x,y)], i) || bit_test(grid[ss[x][y]], i)) ) {
			
			bit_set(col[y], i);
			bit_set(row[x], i);
			bit_set(block[block_id(x,y)], i);
			bit_set(grid[ss[x][y]], i);
		
			//printf("test %d: %d,%d : %d\n", k, x, y, i);
				
			map[x][y] = i;
			dfs(k+1);
			map[x][y] = 0;
			
			bit_set_0(col[y], i);
			bit_set_0(row[x], i);
			bit_set_0(block[block_id(x,y)], i);
			bit_set_0(grid[ss[x][y]], i);
		}
		if (ans_cnt > 1) return;
	}
}

int main()
{
	int cs, nCase;
	int i, j, cnt;
	scanf("%d", &nCase);
	for (cs = 1; cs <= nCase; ++cs) {
		for (i = 0; i < 9; ++i) {
			for (j = 0; j < 9; ++j) {
				scanf("%d", &desc[i][j]); 
				//	printf("%d: %d ", desc[i][j], desc[i][j]&15);
			}
			//	puts("");
		}
		memset(ss, -1, sizeof(ss));
		memset(col, 0, sizeof(col));
		memset(row, 0, sizeof(row));
		memset(block, 0, sizeof(block));
		memset(grid, 0, sizeof(grid));
		cnt = 0;
		h_cnt = 0;
		for (i = 0; i < 9; ++i) {
			for (j = 0; j < 9; ++j) {
				if (ss[i][j] == -1) {
					dfs_ss(i, j, cnt++);
					//	printf("%d %d:ss %d\n", i, j, cnt-1);
				}
			}
		}
		//printf("h_cnt %d\n", h_cnt);
		/*
		   for (i = 0; i < 9; ++i) {
		   for (j = 0; j < 9; ++j) {
		   printf("%d ", map[i][j]);
		   }
		   puts("");
		   }
		   */
		ans_cnt = 0;
		dfs(0);
		printf("Case %d:\n", cs);
		if (ans_cnt == 0) printf("No solution\n");
		else if (ans_cnt > 1) printf("Multiple Solutions\n");
		else {
			for (i = 0; i < 9; ++i) {
				for (j = 0; j < 9; ++j ) {
					printf("%d", desc[i][j]);
				}
				printf("\n");
			}
		}
	}
	return 0;
}
