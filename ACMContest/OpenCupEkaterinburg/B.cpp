#include <bits/stdc++.h>

using namespace std;
const int N = 1100;
typedef pair<int, int> pii;
int n;
int a[N], it[1100];
vector <int> g[N];
int main(){
    // freopen("in.txt", "r", stdin);
    scanf("%d", &n);
    for (int i = 1; i <= n; ++ i) scanf("%d", &a[i]);
    sort(a + 1, a + n + 1);
    for (int i = 1; i <= n; ++ i){
	g[i].push_back(a[i]);
	for (int j = 2; j * j <= a[i]; ++ j){
	    if (a[i] % j == 0) g[i].push_back(j);
	    if (a[i] % j == 0) g[i].push_back(a[i] / j);
	}
    }
   
    for (int i = 1; i <= n; ++ i) sort(g[i].begin(), g[i].end());
    priority_queue <pii, vector<pii>, greater<pii> > q;
    // puts("here");
    for (int i = 1; i <= n; ++ i){
	q.push(make_pair(g[i][0], i));
	it[i] = 0;
    }
    //  puts("here");
    int now = 2;
    while (!q.empty()){
	pii h = q.top(); q.pop();
	if (h.first > now) break;
	if (h.first == now) now ++;
	if (it[h.second] + 1 < g[h.second].size())
	    q.push(make_pair(g[h.second][++it[h.second]], h.second));
    }
    printf("%d\n", now);
}
