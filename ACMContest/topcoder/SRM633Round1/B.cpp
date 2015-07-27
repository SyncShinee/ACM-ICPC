#include <cstdio>
#include <string>
#include <vector>
#include <cstring>
#include <algorithm>
#include <iostream>
using namespace std;
class ABBA {
public:
	string canObtain(string initial, string target) {
		int len;
		while (target.size() > 0 && target != initial) {
			len = target.size();
			if (target[len - 1] == 'A') {
				target.erase(len-1, 1);
			}
			else {
				target.erase(len-1, 1);
				target.assign(target.rbegin(), target.rend());
			}
		}
		if (target == initial) {
			return "Possible";
		}
		return "Impossible";
	}
};
int main() {

}