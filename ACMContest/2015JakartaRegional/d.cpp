#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>

using namespace std;

const int maxn = 1e5 + 100;
int n, A, B;
int a[maxn];
int ans[maxn], val, tag;
int b[20], number[10], have[20];
int num;
int change(int x) {
    if(x == 2)
	return 0;
    if(x == -2)
	return 1;
    if(x == 1)
	return 2;
    if(x == -1)
	return 3;
    return 4;
}
void dfs(int pos, int now) {
    if(pos == 4) {
	if(now + have[number[pos]] < num)
	    return;
	int t = num - now;
	if(t == 0) {
	    int tval = b[0] + b[1];
	    int ttag = (b[1] + b[3]) % 2;
	    if(ttag == 1)
		ttag = -1;
	    else
		ttag = 1;
	    if(ttag > tag || (ttag == tag && (tag == 1 && tval > val || tag == -1 && tval < val)))
		{
		    tag = ttag;
		    val = tval;
		    for(int i = 0; i <= 3; i++) {
			ans[i] = b[i];
		    }
		    ans[4] = num - now;
		}
		
	}
	else {
	    if(tag < 0) {
		tag = 0;
		val = 0;
		for(int i = 0; i <= 3; i++) {
		    ans[i] = b[i];
		}
		ans[4] = num - now;
	    }
	}
	return;
    }
    int tmp = min(num - now, have[number[pos]]);
    b[pos] = tmp;
    dfs(pos + 1, now + tmp);
    if(tmp > 0) {
	b[pos] = tmp - 1;
	dfs(pos + 1, now + tmp - 1);
    }
}
vector<int> res;

void solve() {
    tag = -2;
    for(num = A; num <= B; num++)
	dfs(0, 0);
    /*printf("%d  %d\n", tag, val);
      for(int i = 0; i <= 4; i++) {
      printf("%d ", ans[i]);
      }*/
    res.clear();
    if(tag >= 0) {
	;
    }
    else {
	if(A == n && A == B) {
	    for(int i = 0; i <= 4; i++)
		ans[i] = have[i];
	}
	else {
	    for(int i = 0; i <= 4; i++)
		ans[i] = 0;
	    ans[3] = min(A, have[3]);
	    ans[1] = A - ans[3];
	}
    }
    for(int i = 0; i < n; i++) {
	if(ans[change(a[i])] > 0) {
	    res.push_back(i);
	    ans[change(a[i])]--;
	}
    }
    printf("%d\n", res.size());
    for(int i = 0; i < res.size(); i++) {
	printf("%d%c", res[i] + 1, (i == res.size() - 1 ? '\n' : ' '));
    }
}

int main() {
    freopen("d.txt", "r" ,stdin);
    number[0] = 0;
    number[1] = 1;
    number[2] = 2;
    number[3] = 3;
    number[4] = 4;
    int ncase;
    scanf("%d", &ncase);
    for(int _ = 1; _ <= ncase; _++) {
	printf("Case #%d:\n", _);
	scanf("%d %d %d", &n, &A, &B);
	for(int i = 0; i <= 4; i++)
	    have[i] = 0;
	for(int i = 0; i < n; i++) {
	    scanf("%d", &a[i]);
	    have[change(a[i])]++;
	}
	solve();
    }
    return 0;
}
