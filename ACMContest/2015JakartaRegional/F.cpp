#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>

using namespace std;
const int N = 110;
struct P{
    int t, type, id;
    P(int _t = 0,int _type = 0,int _id = 0){
	t = _t;
	type = _type;
	id = _id;
    }
    bool operator <(const P & o)const{
	return t > o.t;
    }
};
int n, a[N][3];
int ok[10];
void solve(){
    scanf("%d",&n);
    for (int i = 1;i <= n;i++)
	scanf("%d %d %d",&a[i][0],&a[i][1],&a[i][2]);

    priority_queue<int, vector<int>, greater<int> > q[3];
    priority_queue<P> p;
    for (int i = 1;i <= n;i++){
	int x = 0;
	while (x <= 2 && a[i][x] == 0) x++;
	if (x <= 2) 
	    q[x].push(i);
    }
    memset(ok, 0, sizeof ok);
    p.push(P(0, 0, 0));
    p.push(P(0, 1, 0));
    p.push(P(0, 2, 0));
    int ans = 0;
    while (!p.empty()){
	P h = p.top(); p.pop();
	//	printf("%d %d\n",h.type, h.t);
	ans = max(ans, h.t);
	ok[h.type] = 1;
	if (h.type != 2 && h.id){
	    int x = h.type + 1;
	    while (x <= 2 && a[h.id][x] == 0) x++;
	    if (x <= 2) 
		q[x].push(h.id);
	}
	for (int i = 0;i < 3;i++){
	    if (!q[i].empty() && ok[i]){
		int id = q[i].top(); q[i].pop();
		ok[i] = 0;
		p.push(P(h.t + a[id][i], i, id));
	    }
	}
    }
    static int ca = 0;
    printf("Case #%d: %d\n",++ca,ans);
    
}
int main(){
    freopen("d.txt","r",stdin);
    int t;
    scanf("%d",&t);
    while (t--){
	solve();
    }
}
