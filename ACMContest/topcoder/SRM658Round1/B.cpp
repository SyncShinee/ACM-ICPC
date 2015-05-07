#include <cstdio>
#include <iostream>
#include <string>
using namespace std;
class InfiniteString{
public:
	int gcd (int x, int y) {
		if(y == 0)
			return x;
		return gcd(y, x % y);
	}
	string equal(string s, string t) {
		string ts = s;
		string tt = t;
		int lens = s.length();
		int lent = t.length();
		int ttts = lens;
		int tttt = lent;
		int gc = gcd(lens, lent);
		int lcm = lens * lent / gc;
		while (lens < lcm) {
			lens += ttts;
			ts += s;
		}
		while (lent < lcm) {
			lent += tttt;
			tt += t;
		}
		if (ts.compare(tt) == 0)
			return "Equal";
		return "Not equal";
	}
};
int main() {
	InfiniteString t;
	cout << t.equal("bbb", "bbbb");
	return 0;
}