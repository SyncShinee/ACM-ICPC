#include <cstdio>
#include <cstring>
#include <list>
#define INSERT 0
#define OVERWT 1
#define NOTNG 0
#define START 1
using namespace std;
char s[10010];
list <char> mlist, tmplist, tt;
list<char>::iterator it, preit;
bool mode;
int state, n, pos, nowlen;
int main() {
	int T;
	freopen("in.txt", "r", stdin);
	scanf("%d", &T);
	while (T --) {
		scanf("%d%s", &n, s);
		int len = strlen(s);
		mlist.clear();
		tmplist.clear();
		it = mlist.begin();
		mode = INSERT;
		nowlen = 0;
		for (int i = 0; i < len; ++ i) {
			if (s[i] >= 'a' && s[i] <= 'z') {
				if (state == START) state = NOTNG;
				if (mlist.size() == n && (mode == INSERT || mode == OVERWT && it == mlist.end()))
					continue;
				mlist.insert(it, s[i]);
				nowlen++;
				if (mode == OVERWT) {
					if (it != mlist.end()) {
						it = mlist.erase(it);
					}
				}
			}
			else if (s[i] == 'L') {
				if (it != mlist.begin()) {
					it--;
					pos--;
					nowlen--;
				}
			}
			else if (s[i] == 'R') {
				if (it != mlist.end()) {
					it ++;
					pos++;
					nowlen++;
				}
			}
			else if (s[i] == 'S') {
				mode ^= 1;
				if (state == START) state = NOTNG;
			}
			else if (s[i] == 'D') {
				if (state == NOTNG) {
					if (it != mlist.end()) {
						it = mlist.erase(it);
					}
				}
				else {
					state = NOTNG;
					if (pos > 0) {
						it = tmplist.erase(preit, it);
						nowlen -= pos;
					}
					else {
						it = tmplist.erase(it, preit);
					}
				}
			}
			else if (s[i] == 'B') {
				if (state == START) state = NOTNG;
				if (it != mlist.begin()) {
					nowlen--;
					it --;
					it = mlist.erase(it);
				}
			}
			else if (s[i] == 'C') {
				if (state == NOTNG) {
					pos = 0;
					state = START;
					preit = it;//printf("---%c\n", *preit);
				}
				else if (state == START) {
					state = NOTNG;
					tmplist.clear();
					if (pos > 0) {
						tmplist.assign(preit, it);
					}
					else {
						tmplist.assign(it, preit);
					}
				}
			}
			else if (s[i] == 'V') {
				if (state == START) state = NOTNG;
				tt.clear();
				tt.assign(tmplist.begin(), tmplist.end());
				if (mode == INSERT && mlist.size() + tmplist.size() <= n) {
					mlist.splice(it, tt);
					nowlen += tmplist.size();
				}
				else if (mode == OVERWT && nowlen + tmplist.size() <= n) {
					mlist.splice(it, tt);
					nowlen += tmplist.size();
					for (int i = 0; i < tmplist.size(); ++ i) {
						if (it == mlist.end()) break;
						it = mlist.erase(it);
					}
				}
			}
		}
		if (mlist.size() > 0) {
			for (list<char>::iterator i = mlist.begin(); i != mlist.end(); ++ i) {
				printf("%c", *i);
			} 
		}
		else {
			printf("NOTHING");
		}
		printf("\n");
	}
	return 0;
}