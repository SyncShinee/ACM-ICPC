#include <cstdio>
#include <algorithm>
#include <cstring>
#include <string>
#include <vector>
#include <map>
#include <set>
#include <cmath>
#include <queue>
#include <stack>
#define N 100010
using namespace std;
typedef long long ll;
struct node {
	int val, idx;
	friend bool operator < (node a, node b) {
		return a.val < b.val;
	}
}p[N];
int fst[N][32], n, vis[N], ans[N];
set <pair<int, int> > st;

int qurey(int l, int r) {
	int length = log(r - l + 1) / log(2);
	return max(fst[l][length], fst[r - (1 << length) + 1][length]);
}

int main() {
	int T;
	scanf("%d", &T);
	while (T--) {
		scanf("%d", &n);
		memset(fst, 0, sizeof fst);
		memset(vis, 0, sizeof vis);
		memset(ans, 0, sizeof ans);
		for (int i = 1; i <= n; ++i) {
			scanf("%d", &p[i].val);
			p[i].idx = i;
		}
		for (int i = 1; i <= n; ++i) {
			fst[i][0] = p[i].val;
		}
		for (int j = 1; (1 << j) <= n; ++j) {
			for (int i = 1; i + (1 << j) - 1 <= n; ++i) {
				fst[i][j] = max(fst[i][j - 1], fst[i + (1 << (j-1))][j - 1]);
			}
		}
		sort(p + 1, p + n + 1);
		st.clear();
		for (int i = 1; i <= n; ++i) {
			if (vis[p[i].idx]) {
				continue;
			}
			if (p[i].idx == 1) {
				if (!vis[2]) {
					if (fst[1][0] < fst[2][0]) {
						st.insert(make_pair(1, 0));
						st.insert(make_pair(2, 1));
						vis[1] = vis[2] = 1;
					}
				}
				else {
					vis[1] = true;
					st.insert(make_pair(1, 0));
					st.insert(make_pair(1, 1));
				}
			}
			else if (p[i].idx == n) {
				set <pair <int, int> > :: iterator iter = st.lower_bound(make_pair(p[i].idx, 0));
				if (iter == st.begin()) {
					int maxl = qurey(1, n);
					int pos;
					for (pos = n; fst[pos][0] != maxl; --pos) {
						vis[pos] = 1;
					}
					vis[pos] = 1;
					//printf("----%d\n", pos);
					st.insert(make_pair(pos, 0));
					st.insert(make_pair(n, 1));
				}
				else {
					iter--;
					int maxl = qurey((*iter).first + 1, n);
					int pos;
					for (pos = n; fst[pos][0] != maxl; --pos) {
						vis[pos] = 1;
					}
					vis[pos] = 1;
					//printf("----%d\n", pos);
					st.insert(make_pair(pos, 0));
					st.insert(make_pair(n, 1));
				}
			}
			else {
				set <pair <int ,int> > :: iterator iter = st.lower_bound(make_pair(p[i].idx, 0));
				int maxl, maxr;
				if (vis[p[i].idx + 1]) {
					if (iter == st.begin()) {
						maxl = qurey(1, p[i].idx);
					}
					else {
						iter--;
						maxl = qurey((*iter).first + 1, p[i].idx);
					}
					int pos;
					for (pos = p[i].idx; fst[pos][0] != maxl; --pos) {
						vis[pos] = 1;
					}
					vis[pos] = 1;
					//printf("----%d\n", pos);
					st.insert(make_pair(pos, 0));
					st.insert(make_pair(p[i].idx, 1));
				}
				else {
					if (iter == st.begin()) {
						maxl = qurey(1, p[i].idx);
					}
					else {
						iter--;
						maxl = qurey((*iter).first + 1, p[i].idx);
					}
					maxr = fst[p[i].idx + 1][0];
					if (maxr < maxl) {
						int pos;
						for (pos = p[i].idx; fst[pos][0] != maxl; --pos) {
							vis[pos] = 1;
						}
						vis[pos] = 1;
						//printf("----%d\n", pos);
						st.insert(make_pair(pos, 0));
						st.insert(make_pair(p[i].idx, 1));
					}
					else {
						st.insert(make_pair(p[i].idx, 0));
						st.insert(make_pair(p[i].idx + 1, 1));
						vis[p[i].idx] = vis[p[i].idx + 1] = 1;
					}
				}
			}
		}
		/*for (set <pair <int , int> > :: iterator it = st.begin(); it != st.end(); it++) {
			printf("--%d %d\n", (*it).first, (*it).second);
		}*/
		for (int i = 1; i <= n; ++i) {
		//	printf("^^^^%d\n", i);
			set <pair <int ,int> > :: iterator iter = st.find(make_pair(p[i].idx, 1)), itl, itr, itr0, itl0, itl1, itr1;
			if (iter != st.end()) {
				itr = iter;
				itl = --iter;
				itl0 = itr0 = itl1 = itr1 = st.end();
				if (iter != st.begin()) {
					itr0 = --iter;
					itl0 = --iter;
				}
				iter = itr;
				itl1 = ++ iter;
				if (iter != st.end()) {
					itr1 = ++iter;
				}
				if (itl0 == st.end()) {
					//printf("^^^111\n");
					if (itl1 == st.end()) {
						continue;
					}
				//	printf("^^^^^222\n");
				//	printf("%d %d %d %d\n", (*itr).first, (*itr1).first, (*itl).first, (*itl1).first);
					if (fst[(*itr).first][0] < fst[(*itr1).first][0]) {
						if (fst[(*itl).first][0] < fst[(*itl1).first][0]) {
							st.erase(itr);
							st.erase(itl1);
							continue;
						}
					}
					else if (fst[(*itr).first][0] > fst[(*itr1).first][0]) {
						if (fst[(*itl).first][0] > fst[(*itl1).first][0]) {
							st.erase(itr);
							st.erase(itl1);
							continue;
						}
					}
				}
				else if (itl1 == st.end()) {
					if (fst[(*itr).first][0] < fst[(*itr0).first][0]) {
						if (fst[(*itl).first][0] < fst[(*itl0).first][0]) {
							st.erase(itr0);
							st.erase(itl);
							continue;
						}
					}
					else if (fst[(*itr).first][0] > fst[(*itr0).first][0]) {
						if (fst[(*itl).first][0] > fst[(*itl0).first][0]) {
							st.erase(itr0);
							st.erase(itl);
							continue;
						}
					}

				}
				else {
					if (fst[(*itr).first][0] < fst[(*itr0).first][0] && fst[(*itr).first][0] < fst[(*itr1).first][0]) {
						if (fst[(*itl0).first][0] < fst[(*itl1).first][0]) {
							if (fst[(*itl).first][0] < fst[(*itl1).first][0]) {
								st.erase(itr);
								st.erase(itl1);
								continue;
							}
						}
						else {
							if (fst[(*itl).first][0] < fst[(*itl0).first][0]) {
								st.erase(itr0);
								st.erase(itl);
								continue;
							}
						}
					}
					else if (fst[(*itr).first][0] < fst[(*itr0).first][0]) {
						if (fst[(*itl).first][0] < fst[(*itl0).first][0]) {
							st.erase(itr0);
							st.erase(itl);
							continue;
						}
					}
					else if (fst[(*itr).first][0] < fst[(*itr1).first][0]) {
						if (fst[(*itl).first][0] < fst[(*itl1).first][0]) {
							st.erase(itr);
							st.erase(itl1);
							continue;
						}
					}
				}
			}
		}
		/*for (set <pair <int , int> > :: iterator it = st.begin(); it != st.end(); it++) {
			printf("%d %d\n", (*it).first, (*it).second);
		}*/
		for (int i = 1; i <= n; ++i) {
			set <pair <int ,int> > :: iterator iter = st.find(make_pair(i, 1));
			if (iter != st.end()) {
				iter--;
				ans[fst[i][0]] = fst[(*iter).first][0];
			}
			else {
				if (i == n)
					ans[fst[i][0]] = fst[n][0];
				else {
					ans[fst[i][0]] = fst[i + 1][0];
				}
			}
		}
		for (int i = 1; i <= n; ++i)
			printf("%d%c", ans[i], i == n ? '\n' : ' ');
	}
	return 0;
}