/*
 * CF 259 C. Little Elephant and Bits
 * */
#include <cstdio>
#include <cstring>

char b[100005];

int main() {
	scanf("%s", b);
	int i = 0;
	for (i = 0; b[i]; ++i) {
		if (b[i] == '0') break;
	}
	if (b[i]) {
		b[i] = 0;
	} else {
		b[i-1] = 0;
		b[i+1] = 0;
	}
	printf("%s%s\n", b, b+i+1);
	return 0;
}
