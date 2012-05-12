/* Xiaoqian’s Invitation */
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <functional>
using namespace std;

#define INF 999999
#define MAXN 201
#define MAXM 10001
#define MAXD 201

int n, m, d;
bool used[MAXD];
int price[MAXD];

int bill[MAXD], bill_id[MAXD];
int tmp_order[MAXN], order[MAXN];
int order_person, cur_max, fee, min_fee, dish;
int sum[MAXD+1];

void max_fee(int n_person, int k, int n_money, int fee)
{
    int i;
    if (k == dish || n_person == n-1 || n_money < bill[dish-1]) {
        if (fee > cur_max) {
            for (i = 0; i < n_person; i++) order[i] = tmp_order[i];
            order_person = n_person;
            cur_max = fee;
        }
        return;
    }

    if (n_money <= m-min_fee) return;

    if (n-n_person-1 >= dish-k && n_money-sum[dish]+sum[k] >= m-cur_max)  return;
    if (n-n_person-1 <= dish-k && n_money-sum[n]+sum[k] >= m-cur_max)  return;
/*
    if (n-n_person-1 >= dish-k && fee+sum[dish]-sum[k] <= cur_max)  return;
    if (n-n_person-1 <= dish-k && fee+sum[n]-sum[k] <= cur_max)  return;
*/
    // buy all
    if (n-n_person-1 >= dish-k && n_money-sum[dish]+sum[k] >= 0) {
        n_money -= sum[dish]-sum[k];
        for (i = k; i < dish; i++) {
            tmp_order[n_person] = i;
            fee += bill[i];
            n_person++;
        }
        max_fee(n_person, dish, n_money, fee);
        return;
    }

    if (n-n_person-1 <= dish-k && n_money-sum[k+n-n_person-1]+sum[k] >= 0) {
        n_money -= sum[n-n_person-1]-sum[k];
        for (i = n_person; i < n-1; i++) {
            tmp_order[i] = k;
            fee += bill[k];
            k++;
        }
        max_fee(i, k, n_money, fee);
        return;
    }

    for (i = k; i < dish; i++) {
        if (n_money >= bill[i]) {
            tmp_order[n_person] = i;
            max_fee(n_person+1, i+1, n_money-bill[i], bill[i]+fee);
        }
    }
}

int main()
{
    int n_case;
    int i, j;
    scanf("%d", &n_case);
    while (n_case--) {
        scanf("%d %d %d", &n, &m, &d);
        for (i = 0; i < d; i++) scanf("%d", &price[i]);
        sort(price, price+d, greater<int>());

        memset(used, false, sizeof(used));
        min_fee = INF;
        for (i = 0; i < d; i++) {
            if (price[i] > m || used[i]) continue;
            used[i] = true;
            dish = 0;
            for (j = 0; j < d; j++) {
                if (price[j] > m || i == j) continue;
                bill[dish] = price[j];
                bill_id[dish] = j;
                dish++;
            }
            for (j = 0, sum[0]=0; j < dish; j++) sum[j+1] = sum[j] + bill[j];
            cur_max = 0;
            max_fee(0, 0, m-price[i], price[i]);
            min_fee = min(cur_max, min_fee);

            for (j = 0; j < order_person; j++) used[bill_id[order[j]]] = true;
        }
        printf("%d\n", min_fee);
    }
    return 0;
}
