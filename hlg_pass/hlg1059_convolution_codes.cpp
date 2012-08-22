#include <stdio.h>
#include <string.h>

char p[2][8] = {"1011011", "1111001"};

int main()
{
	char in[1000+5];
	char out[2][1007+5];
	char buf[2*1007+5];
	int caseN = 0;

	while (EOF != scanf("%s", in)) {
		caseN++;
		memset(out, 0, sizeof(out));
		int in_len = strlen(in);
		int out_len = in_len + 6;
		for (int i = 0; i < in_len; i++) {
			for (int j = 0; j < 7; j++) {
				out[0][i+j] += (in[i] - '0')*(p[0][j] - '0');
				out[1][i+j] += (in[i] - '0')*(p[1][j] - '0');
			}
		}
		for (int i = 0; i < out_len; i++) {
			buf[2*i] = (out[0][i] % 2) + '0';
			buf[2*i+1] = (out[1][i] % 2) + '0';
		}
		buf[2*out_len] = '\0';
		printf("Case %d: %s\n", caseN, buf);
	}

	return 0;
}

