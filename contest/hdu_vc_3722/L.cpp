#include <cstdio>
#include <iostream>
#include <map>
#include <string>
using namespace std;

int main()
{
	map<string, int> ma;
	ma["I"] = 1;
	ma["II"] = 2;
	ma["III"] = 3;
	ma["IV"] = 4;
	ma["V"] = 5;
	ma["VI"] = 6;
	ma["VII"] = 7;
	ma["VIII"] = 8;
	ma["IX"] = 9;
	ma["X"] = 10;
	ma["XI"] = 11;
	ma["XII"] = 12;
	int nCase = 0;
	char str[1024];
	while (EOF != scanf("%s", str)) {
		printf("Case %d: %d\n", ++nCase, ma[str]);
	}
	return 0;
}

