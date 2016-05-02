#include <iostream>
#include <cstdio>
#include <cstring>
#include <string>
#include <map>

using namespace std;

const int maxn = 1e3 + 100;

map<string, int> mp;
string name[maxn];
int num[maxn];
int n, m;

void solve() {
    m = 0;
    mp.clear();
    for(int i = 0; i < n; i++) {
	string a;
	cin >> a;
	string b = "";
	for(int j = a.size() - 1; j >= 0; j--) {
	    if(a[j] == '.') {
		break;
	    }
	    b = a[j] + b;
	}
	if(mp[b] == 0) {
	    m++;
	    mp[b] = m;
	    name[m] = b;
	    num[m] = 1;
	    
	}
	else {
	    num[mp[b]]++;
	}
    }
    for(int i = 1; i <= m; i++) {
	cout << name[i] << ": " << num[i] << endl;
    }
}

int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    while(scanf("%d", &n) != EOF) {
	solve();
    }
    return 0;
}
