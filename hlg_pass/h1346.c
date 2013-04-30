#include <stdio.h>
#include <string.h>

//const int MAXN = (1<<20) + 1;
#define MAXN ((1<<20)+1)

typedef unsigned int uint;

char b[MAXN];
int a[MAXN];


uint hash32shift(uint key)
{
	key = ~key + (key << 15); // key = (key << 15) - key - 1;
	key = key ^ (key >> 12);
	key = key + (key << 2);
	key = key ^ (key >> 4);
	key = key * 2057; // key = (key + (key << 3)) + (key << 11);
	key = key ^ (key >> 16);
	return key;
}

uint hash(uint a)
{
	a = (a+0x7ed55d16) + (a<<12);
	a = (a^0xc761c23c) ^ (a>>19);
	a = (a+0x165667b1) + (a<<5);
	a = (a+0xd3a2646c) ^ (a<<9);
	a =(a+0xfd7046c5) + (a<<3); // <<和 +的组合是可逆的
	a = (a^0xb55a4f09) ^ (a>>16);
	return a;
}
uint address_hash(uint addr) {
	register uint key; 
	key = (uint) addr; 
	return (key >> 3) * 2654435761U; //这个3是对齐边界为8 
}

int key(int i) {
	return address_hash(hash(i)) % MAXN;
	return hash(i) % MAXN;
	return address_hash((char*)i) % MAXN;
	/*
	int mask = ((1<<20) - 1);
	return hash32shift(i) % MAXN;
	return ((i & mask) ^ (i>>20)) & mask;
	*/
	//return ((i & 0xff) * 131 + ((i>>8)&0xff)*131*131 + ((i>>16)&0xff)*131*131*131 + ((i>>24)&0xff)*131*131*131*131) & mask;
}

void ins(int n) {
	int k = key(n);
	for (;;) {
		if (b[k] == 0) {
			a[k] = n;
			b[k] = 1;
			break;
		} else if (a[k] == n) {
			b[k] = 2;
			break;
		} else {
			k++;
			if (k >= MAXN) k -= MAXN;
		}
	}
}

int main() {
	int n, i;
	memset(b, 0, sizeof(b));
	while (EOF != scanf("%d", &n)) {
		ins(n);
	}
	for (i = 0; i < MAXN; ++i) {
		if (b[i] == 1) {
			n = a[i];
			break;
		}
	}
	printf("%d\n", n);
	return 0;
}
