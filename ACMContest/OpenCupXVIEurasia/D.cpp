#include <bits/stdc++.h>

using namespace std;
const int N = 1e5 + 100;
struct P{
    int x, y;
    P(int _x = 0, int _y = 0){
	x = _x; y = _y;
    }
    bool operator < (const P& o) const{
	return x < o.x || x == o.x && y < o.y;
    }
}a[N];
vector <P> vs;
int d, n;
int check(double x){
    double now = 0;
    double nowx = x;
    for (int i = 0; i < vs.size(); ++ i){
	if (vs[i].x <= nowx) continue;
	double del = (0.0 + vs[i].x - nowx) / (vs[i].y);
	nowx = vs[i].x;
	now += del;
	//	printf("%f %f\n", x, now);
	if (now >= d) return 1;
    }
    // if (x == 400) printf("%f\n", now);
    return 0;
}
int main(){
    // freopen("in.txt", "r", stdin);
    scanf("%d%d", &d, &n);
    for (int i = 1; i <= n; ++ i){
	int q, w, e;
	scanf("%d %d %d", &q, &w, &e);
	a[i] = P(q * e, w * q);
    }
    sort(a + 1, a + n + 1);
    for (int i = 1; i <= n; ++ i){
	while (vs.size() > 0 && vs.back().y >= a[i].y) vs.pop_back();
	vs.push_back(a[i]);
    }
    double l = 0, r = 1e6 + 10;
    for (int i = 1; i <= 200; ++ i){
	//	printf("%f %f\n", l, r);
	double m = (l + r) / 2;
	if (check(m)) l = m;
	else
	    r = m;
    }
    printf("%f\n", l);
}
