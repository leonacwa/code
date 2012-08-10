/* 树状数组
 * */
// 取最低位的1
inline int lowbit(int x) {
	return x & (-x);
}
// 修改, O(logN)
void add(int64 c[], int n, int i, int64 v) {
	for (; i <= n; i += lowbit(i)) c[i] += v;
}
// 求和 O(logN)
int64 sum(int64 c[], int n, int i) {
	int64 s = 0;
	for (; i > 0; i -= lowbit(i)) s += c[i];
	return s;
}
