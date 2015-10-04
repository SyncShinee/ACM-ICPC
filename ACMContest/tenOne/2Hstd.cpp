#include <bits/stdc++.h>
using namespace std;
const double eps = 1.0e-8;
const int MAXN=101505;
typedef complex<double> point;
point p[MAXN];
struct line: vector<point> {
	line() {}
	line(const point& a, const point& b) {
		push_back(a), push_back(b);
	}
};
namespace std {
	bool operator < (const point& a ,const point& b) {
		return a.real() == b.real() ? a.imag() < b.imag() : a.real() < b.real() ;
	}
	bool operator == (const point& a, const point& b) {
		return abs(a - b) < eps;
	}
};
inline double cross	(const point& a, const point& b) {
	return (conj(a) * b).imag();
}
inline double dot	(const point& a, const point& b) {
	return (a * conj(b)).real();
}
inline point vec(const line& s) {
	return s[1] - s[0];
}
inline point crosspoint(const line& l, const line& m) {
	double A = cross(vec(l), vec(m));
	double B = cross(vec(l), l[1]-m[0]);
	return m[0] + B / A * vec(m);
}
inline int ccw(const point& a, const point& b, const point& c) {
	point u = b - a, v = c - a;
	if(cross(u, v) > 0) return 1;
	if(cross(u, v) < 0) return -1;
	if(dot(u, v) < 0) return 2;
	if(abs(u) < abs(v)) return -2;
	return 0;
}
inline int ccw(const line& s, const point& p) {
	return ccw(s[0], s[1], p);
}
inline bool intersectSS(const line& s, const line& t) {
	return ccw(s, t[0]) * ccw(s, t[1]) <= 0 && ccw(t, s[0]) * ccw(t, s[1]);
}
inline bool intersectSP(const line& s, const point& p) {
	return abs(s[0] - p) + abs(s[1] - p) < abs(s[0] - s[1]) + eps;
}
map<point, int> mp;
int n, m, tot=0;
point A[MAXN];
line B[MAXN];
bool vis[MAXN], valve[MAXN];
queue<int> q;
vector< pair<double, int> > tmp;
vector< pair<double, pair<int, int> > > G[MAXN];
vector< bool > used[MAXN];
int insert(const point& p) {
	if(mp.find(p) == mp.end()) {
		mp[p] = ++tot;
		A[tot] = p;
	}
	return mp[p];
}
double solve(int src, int sink){
	q.push(sink);
	vis[sink]=true;
	while(!q.empty()){
		int now = q.front(); q.pop();
		if(valve[now]) continue;
		if(now == src) return -1;
		for(int i = 0; i < G[now].size(); i++){
			int idx = G[now][i].second.first;
			if(vis[idx]) continue;
			vis[idx] = true;
			q.push(idx);
		}
	}
	double ans = 0;
	for(int i = 0; i < n; i++){
		ans += abs(vec(B[i]));
	}
	for(int i = 1; i <= tot; i++){
		used[i].resize(G[i].size(),0);
	}
	q.push(src);
	vis[src] = true;
	while(!q.empty()){
		int now = q.front(); q.pop();
		for(int i = 0; i < G[now].size(); i++){
			int idx = G[now][i].second.first;
			if(used[now][i]) continue;
			ans -= G[now][i].first;
			used[now][i] = used[idx][G[now][i].second.second] = true;
			if(vis[idx]) continue;
			vis[idx] = true;
			q.push(idx);
		}
	}
	return ans;
}
int main() {
//	freopen("in", "r", stdin);
	cin>>n>>m;
	for(int i = 0, x1, x2, y1, y2; i < n; i++) {
		scanf("%d%d%d%d",&x1,&y1,&x2,&y2);
		B[i] = line(point(x1,y1), point(x2,y2));
		insert(point(x1, y1));
		insert(point(x2, y2));
	}
	for(int i = 1, x, y; i <= m; i++) {
		scanf("%d%d",&x,&y);
		int idx = insert(point(x, y));
		valve[idx] = true;
	}
	int x, y;
	scanf("%d%d", &x, &y);
	int src = insert(point(x, y));
	scanf("%d%d", &x, &y);
	int sink = insert(point(x, y));
	for(int i = 0; i < n; i++) {
		for(int j = i + 1; j < n; j ++) {
			if(intersectSS(B[i], B[j])) {
				insert(crosspoint(B[i], B[j]));
			}
		}
	}
//	for(int i = 1; i <= tot; i ++){
//		cout<< A[i] << endl;
//	}
	for(int i = 0; i < n; i++) {
		tmp.clear();
		for(int j = 1; j <= tot; j++) {
			if(intersectSP(B[i],A[j])) {
				tmp.push_back(make_pair(abs(A[j]-B[i][0]),j));
			}
		}
		sort(tmp.begin(),tmp.end());
		int sz = tmp.size();
		for(int j = 1; j < sz; j++){
			int u = tmp[j-1].second, v = tmp[j].second;
			double d = tmp[j].first - tmp[j-1].first;
			int pos1 = G[v].size(), pos2 = G[u].size();
			G[u].push_back(make_pair(d, make_pair(v, pos1)));
			G[v].push_back(make_pair(d, make_pair(u, pos2)));
		}
	}
	double ans = solve(src, sink);
	if(ans == -1) puts("-1");
	else printf("%f\n", ans);
	return 0;
}