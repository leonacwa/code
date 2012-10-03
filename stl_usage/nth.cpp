// nth_element example
#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

bool myfunction (int i,int j) { return (i<j); }

int main () {
	vector<int> myvector;
	vector<int>::iterator it;

	// set some values:
	for (int i=1; i<10; i++) myvector.push_back(i);   // 1 2 3 4 5 6 7 8 9

	random_shuffle (myvector.begin(), myvector.end());

	cout << "random contains:";
	for (it=myvector.begin(); it!=myvector.end(); ++it)
		cout << " " << *it;

	cout << endl;


	// using default comparison (operator <):
	nth_element (myvector.begin(), myvector.begin()+5, myvector.end());

	// using function as comp, begin()+5的元素，也就是从1到5，第5个数是序列中排名为5的元素
	nth_element (myvector.begin(), myvector.begin()+5, myvector.end(),myfunction);

	// print out content:
	cout << "myvector contains:";
	for (it=myvector.begin(); it!=myvector.end(); ++it)
		cout << " " << *it;

	cout << endl;

	return 0;
}
