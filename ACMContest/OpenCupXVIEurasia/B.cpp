#include <iostream>
#include <cstdio>
#include <cstring>
#include <string>
#include <cmath>
#include <map>
#include <vector>

using namespace std;

const int maxn =  3e6 + 100;

map<string, int> mp;
int p[maxn], pn;
string r;
vector<int> G[maxn];
int n, m;
int p2[maxn];
char str[maxn];

void solve() {
    // n = (1 << n);
    for(int i = 0; i < n; i++) {
	G[i].clear();
    }
    for(int i = 0; i < n; i++) {
	p[i] = i;
    }
    pn = n;
    int len = r.size();
    int now = 0;
    for(int i = 0; i < len; i++) {
	if(r[i] == 'W') {
	    G[p[now]].push_back(p[now + 1]);
	    p[pn] = p[now];
	    pn++;
	}
	else {
	    G[p[now + 1]].push_back(p[now]);
	    p[pn] = p[now + 1];
	    pn++;
	}
	now += 2;
    }
    //printf("%d  %d\n", now, pn);
    for(int i = 0; i < m; i++) {
	string a, b;
	scanf("%s", str);
	a = str;
	scanf("%s", str);
	b = str;
	int na = mp[a], nb = mp[b];
	if(G[na].size() == G[nb].size()) {
	    printf("Unknown\n");
	}
	else if(G[na].size() > G[nb].size()) {
	    int l = ((na >> G[na].size()) << (G[na].size()));
	    int r = l + (1 << G[na].size()) - 1;
	    if(nb >= l && nb <= r) {
		printf("Win\n");
	    }
	    else {
		printf("Unknown\n");
	    }
	}
	else {
	    int l = ((nb >> G[nb].size()) << G[nb].size());
	    int r = l + (1 << G[nb].size()) - 1;
	    if(na >= l && na <= r) {
		printf("Lose\n");
	    }
	    else {
		printf("Unknown\n");
	    }
	}
    }
}


int main() {
    //freopen("B.txt", "r", stdin);
    while(scanf("%d", &n) != EOF) {
	n = (1 << n);
	mp.clear();
	for(int i = 0; i < n; i++) {
	    scanf("%s", str);
	    string a;
	    a = str;
	    mp[a] = i;
	    //cout << a << endl;
	}
	scanf("%s", str);
	r = str;
	scanf("%d", &m);
	solve();
    }
    return 0;
}
