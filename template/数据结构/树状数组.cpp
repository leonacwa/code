/* ��״����
 * */
// ȡ���λ��1
inline int lowbit(int x) {
	return x & (-x);
}
// �޸�, O(logN)
void add(int64 c[], int n, int i, int64 v) {
	for (; i <= n; i += lowbit(i)) c[i] += v;
}
// ��� O(logN)
int64 sum(int64 c[], int n, int i) {
	int64 s = 0;
	for (; i > 0; i -= lowbit(i)) s += c[i];
	return s;
}
