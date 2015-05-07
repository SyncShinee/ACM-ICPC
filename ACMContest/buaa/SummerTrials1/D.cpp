#include <string>
#include <iostream>
#include <algorithm>
using namespace std;
struct node {
	string s;
	friend bool operator < (node x, node y) {
		string s1 = x.s+y.s;
		string s2 = y.s+x.s;
		if (s1 < s2)
			return true;
		return false;
	}
}a[128];
using namespace std;
int main() {
	int n;
	cin >> n;
	for (int i = 0; i < n; ++i)
		cin >> a[i].s;
	sort(a, a+n);
	for (int i = 0; i < n; ++i)
		cout << a[i].s;
	cout << endl;
}