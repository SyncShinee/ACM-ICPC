#include <cstdio>
#include <algorithm>
#include <vector>
using namespace std;
vector<pair<int, int> > p;
int x[256], y[256];
int n;
int main() {
    while (~scanf("%d", &n)) {
	p.clear();
	for (int i = 0; i < n; ++ i) {
	    scanf("%d%d", &x[i], &y[i]);
	}
	for (int i = 0; i < n; ++ i) {
	    bool flag = true;
	    for (int j = 0; j < n; ++ j) {
		if (x[i] < x[j] && y[j] < y[i]) {
		    flag = false;
		}
	    }
	    if (flag) {
		p.push_back(make_pair(x[i], y[i]));
	    }
	}
	sort(p.begin(), p.end());
	int nw = -1, ans = 0;
	for (int i = 0; i < p.size(); ++ i) {
	    if (nw < p[i].first) {
		nw = p[i].second;
		ans++;
	    }
	}
	printf("%d\n", ans);
    }
    return 0;
}
