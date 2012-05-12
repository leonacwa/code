
#include <stdio.h>
#include <string.h>

int map[9][9];
int desc[9][9];

int col[9];
int row[9];
int block[9];

int hx[81], hy[81], h_cnt;
int ans_cnt;
int num[9][9][10];

#define bit_set(x, n)   ( (x) |= (1<<(n))  )
#define bit_set_0(x, n) ( (x) &= ~(1<<(n)) )
#define bit_test(x, n)  ( (x) & (1<<(n))   )
#define block_id(x, y)  ( (x)/3*3 + (y)/3  )

void p_map()
{
    int i, j;
    for (i = 0; i < 9; ++i) {
        for (j = 0; j < 9; ++j ) {
            printf("%d", map[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

void pre_work()
{
    int x, y, n;
    for (x = 0; x < 9; ++x) {
        for (y = 0; y < 9; ++y) {
            num[x][y][0] = 0;
            for (n = 1; n <= 9; ++n) {
                if ( !(
                    bit_test(col[y], n) ||
                    bit_test(row[x], n) ||
                    bit_test(block[block_id(x,y)], n) /*||
                    bit_test(grid[ss[x][y]], n) */     ) )
                {
                    num[x][y][++num[x][y][0]] = n;
                }
            }
        }
    }
}

void dfs(int k)
{
    int i, x, y, n;
	if (k >= h_cnt) {
		ans_cnt++;
		//if (ans_cnt == 1) {
		    //memcpy(desc, map, sizeof(map));
		    p_map();
		    fflush(stdout);
		//}
		return;
	}
	x = hx[k];
	y = hy[k];
	for (n = num[x][y][0]; n > 0; --n) {
	    i = num[x][y][n];
		if ( !(
            bit_test(col[y], i) ||
            bit_test(row[x], i) ||
            bit_test(block[block_id(x,y)], i)  ) )
        {
			bit_set(col[y], i);
			bit_set(row[x], i);
			bit_set(block[block_id(x,y)], i);

			map[x][y] = i;
			dfs(k+1);
			map[x][y] = 0;

			bit_set_0(col[y], i);
			bit_set_0(row[x], i);
			bit_set_0(block[block_id(x,y)], i);

            //if (ans_cnt >= 1) return;
		}
	}
}

int main()
{
    freopen("sudoku.in", "r", stdin);
    freopen("sudoku.out", "w", stdout);

	int cs, nCase;
	int i, j, id;
	scanf("%d", &nCase);
	for (cs = 1; cs <= nCase; ++cs) {
	    printf("Case %d:\n", cs);
	    h_cnt = 0;
	    memset(col, 0, sizeof(col));
		memset(row, 0, sizeof(row));
		memset(block, 0, sizeof(block));
		for (i = 0; i < 9; ++i) {
			for (j = 0; j < 9; ++j) {
				scanf("%d", &map[i][j]);
				bit_set(col[j], map[i][j]);
                bit_set(row[i], map[i][j]);
                bit_set(block[block_id(i,j)], map[i][j]);
				if (map[i][j] == 0) {
                    hx[h_cnt] = i;
                    hy[h_cnt++] = j;
				}
			}
		}

        pre_work();
		ans_cnt = 0;
		dfs(0);
	}

    fclose(stdin);
    fclose(stdout);

	return 0;
}
