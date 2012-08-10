
/* 效率未经测试
 * */
 
// Tomas Wang
uint32_t hash32shift(uint32_t key)
{
	key = ~key + (key << 15); // key = (key << 15) - key - 1;
	key = key ^ (key >> 12);
	key = key + (key << 2);
	key = key ^ (key >> 4);
	key = key * 2057; // key = (key + (key << 3)) + (key << 11);
	key = key ^ (key >> 16);
	return key;
}

// Bob Jenkins' 32 bit integer hash function
// 这六个数是随机数， 通过设置合理的6个数，你可以找到对应的perfect hash.
uint32_t hash( uint32_t a)
{
	a = (a+0x7ed55d16) + (a<<12);
	a = (a^0xc761c23c) ^ (a>>19);
	a = (a+0x165667b1) + (a<<5);
	a = (a+0xd3a2646c) ^ (a<<9);
	a =(a+0xfd7046c5) + (a<<3); // <<和 +的组合是可逆的
	a = (a^0xb55a4f09) ^ (a>>16);
	return a;
}

// 64 bit Mix Functions
uint64_t hash64shift(uint64_t key)
{
	key = (~key) + (key << 21); // key = (key << 21) - key - 1;
	key = key ^ (key >> 24);
	key = (key + (key << 3)) + (key << 8); // key * 265
	key = key ^ (key >> 14);
	key = (key + (key << 2)) + (key << 4); // key * 21
	key = key ^ (key >> 28);
	key = key + (key << 31);
	return key;
}
// 64 bit to 32 bit Mix Functions
uint32_t hash64_32shift(uint64_t key)
{
	key = (~key) + (key << 18); // key = (key << 18) - key - 1;
	key = key ^ (key >> 31);
	key = key * 21; // key = (key + (key << 2)) + (key << 4);
	key = key ^ (key >> 11);
	key = key + (key << 6);
	key = key ^ (key >> 22);
	return (int) key;
}

// Bob Jenkins' 96 bit Mix Function
uint32_t mix(uint32_t a, uint32_t b, uint32_t c)
{
	a=a-b; a=a-c; a=a^(c >> 13);
	b=b-c; b=b-a; b=b^(a << 8);
	c=c-a; c=c-b; c=c^(b >> 13);
	a=a-b; a=a-c; a=a^(c >> 12);
	b=b-c; b=b-a; b=b^(a << 16);
	c=c-a; c=c-b; c=c^(b >> 5);
	a=a-b; a=a-c; a=a^(c >> 3);
	b=b-c; b=b-a; b=b^(a << 10);
	c=c-a; c=c-b; c=c^(b >> 15);
	return c;

}

int main() {
	return 0;
}
