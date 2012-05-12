/*
 * implementate by Trie-Tree
 * Concat:791066719@qq.com
 * */

#include <cstdio>
#include <cstring>
#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <vector>
using namespace std;

typedef unsigned long long file_list_t;
struct KeywordTrieNode;
class KeywordsTrie;
struct WordNode;
class FileInfo;

const int CHARSET = 64;
const int MAX_DOC = 64;

int chtoi(char ch)
{
	if ('A' <= ch && ch <= 'Z') return ch - 'A';
	if ('a' <= ch && ch <= 'z') return 26 + ch - 'a';
	return -1;
}

struct WordNode {
	int count;
	WordNode * ptr[CHARSET];
	WordNode(int cnt = 0) {
		count = cnt;
		memset(ptr, 0, sizeof(ptr[0]) * (CHARSET));
	}
	~WordNode() {
		for (int i = 0; i < CHARSET; ++i) {
			if (!ptr[i]) {
				delete ptr[i];
			}
		}
	}
};

/* File Info
 * @include filepath, keywords and keywords-count
 * */
class FileInfo {
	public:
		FileInfo(const string str = "") :path(str) {
		}
		string getFilePath() const {
			return path;
		}
		int find(const char *s) const {
			const WordNode *p = &root;
			while (*s) {
				int a = chtoi(*s);
				if (a == -1) {
					++s;
					continue;
				}
				if (p->ptr[a] == NULL) {
					return 0;
				}
				p = p->ptr[a];
				++s;
			}
			return p->count;
		}
		bool set(const char *s, int cnt) {
			WordNode *p = &root;
			while (*s) {
				int a = chtoi(*s);
				if (a == -1) {
					++s;
					continue;
				}
				if (p->ptr[a] == NULL) {
					WordNode *tmp = new WordNode;
					if (!tmp) return false;
					p->ptr[a] = tmp;
				}
				p = p->ptr[a];
				++s;
			}
			p->count = cnt;
			return true;
		}
		bool add(const char *s, int cnt) {
			WordNode *p = &root;
			//cout << "start add key " ;
			while (*s) {
				int a = chtoi(*s);
				if (a == -1) {
					++s;
					continue;
				}
			//	cout << *s;
				if (p->ptr[a] == NULL) {
					WordNode *tmp = new WordNode;
					if (!tmp) {
						//cout << "Can add !" << endl;
						return false;
					}
					p->ptr[a] = tmp;
				}
				p = p->ptr[a];
				++s;
			}
		//	cout << endl;
			p->count += cnt;
			return true;
		}
	protected:
	private:
		string path;
		WordNode root;
};

struct KeywordTrieNode {

	file_list_t list;
	KeywordTrieNode *ptr[CHARSET];

	KeywordTrieNode(file_list_t l = 0) {
		list = l;
		memset(ptr, 0, sizeof(ptr[0]) * CHARSET);
	}

	~KeywordTrieNode() {
		for (int i = 0; i < CHARSET; ++i) {
			if (!ptr[i]) {
				delete ptr[i];
			}
		}
	}
};

/* Key Word Tree, 
 * keyword -> filelist
 * */

class KeywordsTrie {
	public:
		KeywordsTrie() {
		}
		file_list_t find(const char *s) const {
			const KeywordTrieNode *p = &root;
			//cout << "Tire Find :";
			while (*s) {
				int a = chtoi(*s);
				if (a == -1) {
					++s;
					continue;
				}
				//cout << *s ;
				if (p->ptr[a] == NULL) {
					cout << "No Key!" << endl;
					return 0UL;
				}
				p = p->ptr[a];
				++s;
			}
			//cout << "." << endl;
			//cout << "Find list: " << p->list << endl;
			return p->list;
		}
		bool set(const char *s, file_list_t l) {
			KeywordTrieNode *p = &root;
			while (*s) {
				int a = chtoi(*s);
				if (a == -1) {
					++s;
					continue;
				}
				if (p->ptr[a] == NULL) {
					KeywordTrieNode * tmp = new KeywordTrieNode;
					if (!tmp) return false;
					p->ptr[a] = tmp;
				}
				p = p->ptr[a];
				++s;
			}
			p->list = l;
			return true;
		}
		bool add(const char *s, file_list_t l) {
			//cout << "Tree add key " << s << " " << l << endl;
			KeywordTrieNode *p = &root;
			while (*s) {
				int a = chtoi(*s);
				if (a == -1) {
					++s;
					continue;
				}
				if (p->ptr[a] == NULL) {
					KeywordTrieNode * tmp = new KeywordTrieNode;
					if (!tmp) return false;
					p->ptr[a] = tmp;
				}
				p = p->ptr[a];
				++s;
			}
			p->list |= l;
			return true;
		}
	protected:
	private:
		KeywordTrieNode root;
};

/* Search Engine
 * */
class SearchEngine {
	public:
		SearchEngine() : doc_count(0), res(0) {
			memset(doc, 0, sizeof(doc[0]) * MAX_DOC);
		}
		FileInfo* extractDoc(const char *path) {
			cout << "extractDoc " << path << "  ID:" << doc_count << endl;
			if (doc_count >= MAX_DOC) return NULL;
			ifstream fin(path);
			if (fin.bad()) return NULL;
			FileInfo *pfile = new FileInfo(path);
			if (pfile == NULL) return NULL;
			string str;
			file_list_t l = 1 << doc_count;
			while (fin >> str) {
				pfile->add(str.c_str(), 1);
				tree.add(str.c_str(), l);
			}
			fin.close();
			doc[doc_count++] = pfile;
			return pfile;
		}
		const FileInfo * getDocInfo(int i) const {
			/*
			   int i = 0;
			   while (!(l & (1<<i)) && i < MAX_DOC) ++i;
			   */
			if (i < 0 || i >= MAX_DOC) return NULL;
			return doc[i];
		}
		const void displayDoc(int i) const {
			if (i < 0 || i >= MAX_DOC) {
				return;
			}
			if (doc[i] == NULL) {
				return;
			}
			if (doc[i]->getFilePath().length() == 0) {
				return;
			}
			/*
			ifstream fin(doc[i]->getFilePath().c_str());
			if (fin.bad()) {
				return;
			}
			string str;
			while (fin >> str) {
				cout << str << endl;
			}
			fin.close();
			*/
			FILE * fdoc = fopen(doc[i]->getFilePath().c_str(), "r");
			if (fdoc == NULL) {
				return;
				cout << "Open " << doc[i]->getFilePath().c_str() << " Error!" << endl;
			}
			cout << "Display " << doc[i]->getFilePath().c_str() << ":" << endl;
			int ch;
			while (EOF != (ch = fgetc(fdoc))) {
				putchar(ch);
			}
			cout << endl;
		}
		file_list_t find(const char *s) const {
			file_list_t ret = tree.find(s);
			cout << "Tree Find " << s << ", " << ret << endl;
			return ret;
		}
		file_list_t search(const char *str_in) {
			char s[strlen(str_in)];
			strcpy(s, str_in);
			//while (*s && isspace(*s)) ++s;
			cout << "Search " << s << endl;
			this->str = s;
			const char delims[] = " ";
			char *str;
			file_list_t a = 0, b = 0;
			// first
			str = strtok(s, delims);
			if (0 == strcmp(str, "NOT")) {
				str = strtok(NULL, delims);
				a = this->tree.find(str);
				a = ~a;
			} else if(str) {
				a = this->tree.find(str);
			}
			// operator
			int op = 0;
			str = strtok(NULL, delims);

			if (str == NULL) return res = a;

			if (0 == strcmp(str, "AND")) {
				op = 1;
			} else if (0 == strcmp(str, "OR")) {
				op = 2;
			}
			// second
			str = strtok(NULL, delims);

			if (str == NULL) return res = a;

			if (0 == strcmp(str, "NOT")) {
				str = strtok(NULL, delims);
				if (str) {
					b = this->tree.find(str);
					b = ~b;
				}
			} else if(str) {
				b = this->tree.find(str);
			}
			if (op == 0) {
				res = a;
			} else if (op == 1) {
				res = a & b;
			} else if (op == 2) {
				res = a | b;
			}
			res_count = 0;
			for (int i = 0; i < MAX_DOC; ++i) {
				if (res & (1 << i)) {
					++res_count;
				}
			}
			return res;
		}
		bool displayResult() const {
			//if (str.length() == 0) return false;
			const FileInfo * pfile;
			cout << "Search For \"" << str << "\"" << " " << res << endl;
			for (int i = 0; i < MAX_DOC; ++i) {
				if (res & (1 << i)) {
					pfile = this->getDocInfo(i);
					if (pfile) {
						cout << i << ":" << pfile->getFilePath() << " ";
					} else {
					}
				}
			}
			cout << endl;
		}
	protected:
	private:
		int doc_count;
		KeywordsTrie tree;
		FileInfo* doc[MAX_DOC];
		vector<string> key;
		string str;
		file_list_t res;
		int res_count;
};

int main(int argc, const char *argv[])
{
	if (argc < 2) {
		cout << "File List Need!" << endl;
		cout << "Usage:" << argv[0] << "filelist.txt" << endl;
		cout << "filelsit.txt format" << endl;
		cout << "n\n" 
			"file1.txt\n"
			"file2.txt\n"
			"....\n"
			"file_n.txt\n";
		return 0;
	}
	ifstream fin(argv[1]);
	SearchEngine se;
	int n;
	string str;
	cout << "start" << endl;
	fin >> n;
	cout << "Input " << n << " docs" << endl;
	for (int i = 0; i < n; ++i) {
		fin >> str;
		cout << "doc " << str << endl;
		if (NULL == se.extractDoc(str.c_str())) {
			cout << " can't add doc!" << endl;
			break;
		}
	}
	cout << "Done." << endl;
	cout << "Key Word:" << endl;
	while (getline(cin, str)) {
		file_list_t res = se.search(str.c_str());
		int c = 0;
		while (1) {
			se.displayResult();
			cout << "Please Input the doc ID to view or -1 to quit this result:" << endl;
			if (cin >> c) {
				if (c < 0) break;
				se.displayDoc(c);
				cout << endl;
			} else {
				cin >> str;
				break;
			}
		}
		cout << endl;
		cout << "Key Word:" << endl;
		cin.ignore();
	}
	return 0;
}

