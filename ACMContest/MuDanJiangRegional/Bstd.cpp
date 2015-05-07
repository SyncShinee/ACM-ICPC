#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <algorithm>
#include <queue>
#include <map>
#include <vector>
#include <string>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <set>
using namespace std;

#define inf 1000000000

int T;
int n;

vector <int> g[200001];

int fa[200001];
int dis[200001];
int qq[200001], o;
queue <int> q;
bool vis[200001];

void init() {
    while(!q.empty()) q.pop();
    q.push(1);
    for(int i = 1; i <= n; i++) vis[i] = 0;
    vis[1] = 1;
    o = 1;
    fa[1] = 0;
    qq[o] = 1;
    while(!q.empty()) {
        int a = q.front(); q.pop();
        for(int i = 0; i < g[a].size(); i++) {
            int v = g[a][i];
            if(!vis[v]) {
                vis[v] = 1;
                fa[v] = a;
                qq[++o] = v;
                q.push(v);
            }
        }
    }
}

vector <int> ans;

bool ok(int mid) {
    ans.clear();
    int cnt = 0;
    for(int i = o; i >= 1; i--) {
        int x = qq[i];
        int s1 = 0; int s2 = 0;
        for(int j = 0; j < g[x].size(); j++) {
            int v = g[x][j];
            if(v == fa[x]) continue;
            s1 = max(s1, dis[v]);
            s2 = min(s2, dis[v]);
        }

        if(-s2 > s1) {
            dis[x] = s2 + 1;
        } else if(s1 < mid) {
            if(x == 1) {
                cnt++;
                ans.push_back(x);
            }
            dis[x] = s1 + 1;
        } else if(s1 == mid) {
            cnt++;
            ans.push_back(x);
            dis[x] = -mid;
        }
    }
    if(cnt <= 2) return 1;
    else return 0;
}


int main()
{
    freopen("2Bin.txt", "r", stdin);
    freopen("Boutstd.txt", "w", stdout);
    scanf("%d", &T);
    while(T--) {
        scanf("%d", &n);
        for(int i = 1; i <= n; i++) {
            g[i].clear();
        }
        for(int i = 1, a, b; i < n; i++) {
            scanf("%d%d", &a, &b);
            g[a].push_back(b);
            g[b].push_back(a);
        }
        init();
        int l = 0; int r = n; int mid, f_ans;
        while(l <= r) {
            mid = (l + r) / 2;
            if(ok(mid)) {
                f_ans = mid;
                r = mid - 1;
            } else {
                l = mid + 1;
            }
        }
        ok(f_ans);
        if(ans.size() == 1) {
            if(ans[0] == 1) ans.push_back(2);
            else ans.push_back(1);
        }
        printf("%d %d %d\n", f_ans, ans[0], ans[1]);
    }

    return 0;
}