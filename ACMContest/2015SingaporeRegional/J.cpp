#include <cstdio>
#include <algorithm>
#include <cstring>
#include <bitset>
#include <vector>
#include <stack>

using namespace std;

const int maxn = 3e5 + 100;
const int N = maxn;

bitset<128> C[N];
vector<int> G[maxn];
int n, color[maxn], m;

struct node {
    int id, iter;
    node(int _id = 0, int _iter = 0) {
	id = _id;
	iter = _iter;
    }
};

bitset<128> getSum(int x) {
    bitset<128> ret;
    ret.reset();
    while (x) {
	ret ^= C[x];
	x -= x & -x;
    }
    return ret;
}
bitset<128> getSum(int l, int r) {
    return (getSum(r)^getSum(l - 1));
}

void update(int x, int k) {
    while (x <= n) {
	C[x] ^= (1 << k);
	x += x & -x;
    }
}
int cnt, no[maxn], first[maxn], last[maxn];

void bfs(int u) {
    stack<node> s;
    s.push(node(u, 0));
    cnt = 1;
    first[u] = 1;
    update(1, color[u]);
    no[u] = 1;
    while(!s.empty()) {
	node t = s.top();
	//printf("____     %d\n", t.id);
	if(t.iter == G[t.id].size()) {
	    last[t.id] = cnt;
	    s.pop();
	}
	else {
	    //printf("**   %d\n", G[t.id][t.iter]);
	    ++cnt;
	    no[G[t.id][t.iter]] = cnt;
	    first[G[t.id][t.iter]] = cnt;
	    update(cnt, color[G[t.id][t.iter]]);
	    s.pop();
	    t.iter++;
	    s.push(t);
	    s.push(node(G[t.id][t.iter - 1], 0));
	}
    }
}
void dfs(int u, int fa) {
    cnt++;
    no[u] = cnt;
    first[u] = cnt;
    update(cnt, color[u]);
    for(int i = 0; i < G[u].size(); i++) {
	int v = G[u][i];
	if(v != fa) {
	    dfs(v, u);
	}
    }
    last[u] = cnt;
}
void solve() {
    for(int i = 0; i <= n; i++) {
	C[i].reset();
    }
    cnt = 0;
    bfs(1);
    
    //printf("******\n");
    for(int i = 0; i < m; i++) {
	int a, b;
	scanf("%d%d", &a, &b); 
	if(a == 0) {
	    int ans = 0;
	    // printf("**  %d\n", b);
	    // printf("%d  %d\n", first[b], last[b]);
	    bitset<128> t = getSum(first[b], last[b]);
	    printf("%d\n", t.count());
	}
	else {
	    a--;
	    update(no[b], color[b]);
	    color[b] = a;
	    update(no[b], color[b]);
	}
    }
    //printf("&&&&&&&&&&&&&&&&&&&&&\n");
}

int main() {
    freopen("j.txt", "r", stdin);
    while(scanf("%d%d", &n, &m) != EOF){
	for(int i = 1; i <= n; i++)
	    G[i].clear();
	for(int i = 1; i <= n; i++) {
	    scanf("%d", &color[i]);
	    color[i]--;
	}
	for(int i = 2; i <= n; i++) {
	    int t;
	    scanf("%d", &t);
	    G[t].push_back(i);
	    //G[i].push_back(t);
	}
	solve();
	//printf("df");
    }
    return 0;
}
