#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <vector>
#include <algorithm>

using namespace std;

typedef long long ll;

const int maxn = 1e5 + 100;

struct node{
    ll num, id;
    node(ll _num = 0, ll _id = 0) {
	num = _num;
	id = _id;
    }
};
bool cmp(node a, node b) {
    return a.id > b.id;
}
vector<node> vec;
vector<node> ans;

void calcu(ll n, ll k, ll limit) {
    if(n == k) {
	vec.push_back(node(n, 1));
	return;
    }
    if(limit == 1) {
	vec.push_back(node(n, 1));
	return;
    }
    if(limit - 1 > n - k) {
	limit = n - k + 1;
    }
    ll num = (n - k) / (limit - 1);
    vec.push_back(node(num, limit));
    calcu(n - limit * num, k - num, limit - 1);
}
node a[maxn];
int l;

void solve() {
    int flag = 0;
    for(int i = l; i >= 1; i--) {
	if((i + 1 <= l && a[i].id != a[i + 1].id + 1) || (i + 2 <= l)) {
	    flag = 1;
	    ll lft = 0, lftk = 0;
	    for(int j = l; j > i; j--) {
		lft += a[j].num * a[j].id;
		lftk += a[j].num;
	    }
	    lft++;
	    vec.clear();
	    for(int j = 1; j <= i; j++) {
		vec.push_back(node(a[j].num, a[j].id));
		if(j == i) {
		    vec.back().num--;
		    vec.push_back(node(1, a[j].id - 1));
		}
	    }
	    //printf("11  %lld\n", a[i].id);
	    calcu(lft, lftk, a[i].id - 1);
	    break;
	}
    }
    //printf("222\n");
    if(flag == 0) {
	printf("-1\n");
    }
    else {
	ans.clear();
	for(int i = 0; i < vec.size(); i++) {
	    if(i >= 1 && vec[i].id == vec[i - 1].id) {
		ans.back().num += vec[i].num;
	    }
	    else {
		ans.push_back(vec[i]);
	    }
	}
	int cnt = 0;
	for(int i = 0; i < ans.size(); i++) {
	    if(ans[i].num != 0) {
		cnt++;
	    }
	}
	printf("%d\n", cnt);
	for(int i = 0; i < ans.size(); i++) {
	    if(ans[i].num != 0) {
		printf("%lld %lld\n", ans[i].num, ans[i].id);
	    }
	}
    }
}

int main() {
    //freopen("E.txt", "r", stdin);
    while(scanf("%d", &l) != EOF) {
	for(int i = 1; i <= l; i++) {
	    scanf("%lld%lld", &a[i].num, &a[i].id);
	}
	sort(a + 1, a + 1 + l, cmp);
	solve();
    }
    return 0;
}
