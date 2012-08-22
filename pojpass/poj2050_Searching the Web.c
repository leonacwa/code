/*poj 2050 Searching the Web*/
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX_LINES 2048
#define MAX_DOCS 2048
#define MAX_LINE_LEN 128
#define MAX_WORDS 0x7fff

typedef unsigned int uint;

/* 关键字 key */
typedef struct _Word{
    char w[MAX_LINE_LEN];
    uint line[(MAX_LINES+31)/32];
} Word;
Word word[MAX_WORDS];
uint hash[MAX_WORDS];

void set_word_bit(uint idx, int line)
{
    word[idx].line[line/32] |= (1UL << (line % 32));
}

uint test_word_bit(uint idx, int line)
{
    return word[idx].line[line/32] & (1UL << (line % 32));
}

/* 字符串哈希  string hash */
uint str_hash(const char *s)
{
    uint h = 0;
    while (*s) {
        h <<= 5;
        h += tolower(*s);
        s++;
    }
    return h;
}

uint find_idx(const char *s)
{
    uint h = str_hash(s);
    uint i = h  % MAX_WORDS;
    while (hash[i]) {
        if (0 == strcmp(s, word[i].w)) return i;
        i = (i+1) % MAX_WORDS;
    }
    return i;
}

/* 文档存储 document struct */
typedef struct _Document {
    uint key[(MAX_WORDS+31)/32];
    int start_line, end_line;
} Document;
typedef struct _Base {
    int did;
    char buf[MAX_LINE_LEN];
} Base;

Document doc[MAX_DOCS];
int doc_count;
Base base[MAX_LINES];
int base_lines;

void init_doc(Document* d)
{
    memset(d, 0, sizeof(Document));
}
uint test_doc_bit(int did, uint idx)
{
    return doc[did].key[idx/32] & (1UL << (idx%32));
}
void set_doc_bit(int did, uint idx)
{
    doc[did].key[idx/32] |= (1UL << (idx%32));
}
/* 分词：连续的英文字母都要分为一个词, split words*/
int split(const char*s, char word[MAX_LINE_LEN][MAX_LINE_LEN], int ignore)
{
    int c = 0, len;
    const char *ptr;
    static char stop_word[] = "the,a,to,and,or,not,";
    for (ptr = s; *ptr; ptr++) {
        len = 0;
        if (isalpha(*ptr) /*&& (ptr == s || *(ptr-1) == ' ' || *(ptr-1) == '-')*/) {
            for (; *ptr && isalpha(*ptr); ptr++) {
                word[c][len++] = tolower(*ptr);
            }
            ptr--;
            //if (*ptr && *ptr == '-') continue;
            word[c][len] = ',';
            word[c][len+1] = '\0';
            //if (ignore && NULL != strstr(stop_word, word[c])) continue;
            word[c++][len] = '\0';
            //printf("%s :\n", word[c-1]);
        }
        if ('\0' == *ptr) break;
    }
    return c;
}

void insert_base(const char *s, int did, int line)
{
    uint h = str_hash(s);
    uint idx = find_idx(s);
    if (hash[idx] == 0UL) {
        hash[idx] = h;
        strcpy(word[idx].w, s);
    }
    set_word_bit(idx, line);
    set_doc_bit(did, idx);
}

int output(int line, int last_did)
{
    if (last_did != -1 && last_did != base[line].did) {
        printf("----------\n");
    }
    printf("%s\n", base[line].buf);
    return base[line].did;
}

int search_one(const char *s)
{
    uint idx = find_idx(s);
    if (hash[idx] == 0UL) return 0;
    int i, j, x, last_did = -1, output_cnt = 0;
    for (i = 0; i < (MAX_LINES+31)/32; i++) if (word[idx].line[i]) {
        for (x = word[idx].line[i]; x; x -= x&(-x)) {
            for (j = 0; !(x&(1<<j)); j++) ;
            last_did = output(i*32+j, last_did);
            output_cnt++;
        }
    }
    return output_cnt;
}

int search_not(const char *s)
{
    uint idx = find_idx(s);
    int i, j, last_did = -1, output_cnt = 0;
    for (i = 0; i < doc_count; i++) {
        if (!test_doc_bit(i, idx)) {
            for (j = doc[i].start_line; j <= doc[i].end_line; j++) {
                last_did = output(j, last_did);
                output_cnt++;
            }
        }
    }
    return output_cnt;
}

int search_and(const char *s1, const char *s2)
{
    uint idx1 = find_idx(s1), idx2 = find_idx(s2);
    if (hash[idx1] == 0UL || hash[idx2] == 0UL) return 0;
    int i, j, last_did = -1, output_cnt = 0;
    for (i = 0; i < doc_count; i++) {
        if (test_doc_bit(i, idx1) && test_doc_bit(i, idx2)) {
            for (j = doc[i].start_line; j <= doc[i].end_line; j++) {
                if (test_word_bit(idx1, j) || test_word_bit(idx2, j)) {
                    last_did = output(j, last_did);
                    output_cnt++;
                }
            }
        }
    }
    return output_cnt;
}

int search_or(const char *s1, const char *s2)
{
    uint idx1 = find_idx(s1), idx2 = find_idx(s2);
    if (hash[idx1] == 0UL && hash[idx2] == 0UL) return 0;
    int i, j, last_did = -1, output_cnt = 0;
    for (i = 0; i < doc_count; i++) {
        if (test_doc_bit(i, idx1) || test_doc_bit(i, idx2)) {
            for (j = doc[i].start_line; j <= doc[i].end_line; j++) {
                if (test_word_bit(idx1, j) || test_word_bit(idx2, j)) {
                    last_did = output(j, last_did);
                    output_cnt++;
                }
            }
        }
    }
    return output_cnt;
}

void mem_use()
{
    int mem = 0;
    mem = sizeof(word) + sizeof(base) + sizeof(doc);
    printf("%dkb\n", mem / 1024);
}


char key_word[MAX_LINE_LEN][MAX_LINE_LEN];
char query[MAX_LINE_LEN*3];

int main()
{
    //mem_use();
    int i, j, c, n, output_cnt, idx;
    scanf("%d", &doc_count);
    gets(query);
    base_lines = 0;
    for (i = 0; i < doc_count; i++) {
        init_doc(&doc[i]);
        doc[i].start_line = base_lines;
        while (gets(base[base_lines].buf) && strcmp("**********", base[base_lines].buf) != 0) {
            base[base_lines].did = i;
            c = split(base[base_lines].buf, key_word, 1);
            for (j = 0; j < c; j++) {
                //printf("%s\n", key_word[j]); /* ***************** */
                insert_base(key_word[j], i, base_lines);
            }
            base_lines++;
        }
        doc[i].end_line = base_lines-1;
    }
    scanf("%d", &n);
    gets(query);
    for (i = 0; i < n; i++) {
        output_cnt = 0;
        gets(query);
        c = split(query, key_word, 0);
        for(;c == 0;)puts("fuck you, no term exsit!");
        //printf("Query: %d, %s\n", c, query);
        if (c == 1) {
            for(;!strcmp(key_word[0], "not") || !strcmp(key_word[0], "and") || !strcmp(key_word[0], "or");)
                puts("fuck you, \"and\", \"or\" exsit!");
            output_cnt = search_one(key_word[0]);
        }
        else if (c == 2 && strcmp(key_word[0], "not") == 0) {
            output_cnt = search_not(key_word[1]);
        }
        else if (c == 3 && strcmp(key_word[1], "and") == 0) {
            output_cnt = search_and(key_word[0], key_word[2]);
        }
        else if (c == 3 && strcmp(key_word[1], "or") == 0) {
            output_cnt = search_or(key_word[0], key_word[2]);
        }
        else {
           for(;;)puts("fuck you, \"and\", \"or\" dosn't exsit!");
        }
        if (0 == output_cnt) {
            printf("Sorry, I found nothing.\n");
        }
        printf("==========\n");
    }
    //printf("%u\n", MAX_WORDS);
    return 0;
}
