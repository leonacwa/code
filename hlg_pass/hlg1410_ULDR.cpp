/* 终点集合在平移，平终点集类似于矩形
 * */
#include <cstdio>
#include <cstring>
#include <iostream>
using namespace std;

int main()
{
	int n;
	while (EOF != scanf("%d", &n)) {
		char cmd[32];
		long long l = 1, w = 1;
		while (n--) {
			scanf("%s", cmd);
			if (0 == strcmp("ULDR", cmd)) {
				++l, ++w;
			} else if (0 == strcmp("UL", cmd)) {
				++l;
			} else if (0 == strcmp("UR", cmd)) {
				++w;
			} else if (0 == strcmp("DL", cmd)) {
				++w;
			} else if (0 == strcmp("DR", cmd)) {
				++l;
			}
		}
		printf("%lld\n", l * w);
	}
	return 0;
}

