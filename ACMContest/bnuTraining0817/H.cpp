#include <cstdio>
#include <algorithm>
#include <cstring>
#include <queue>
#include <vector>
#include <cmath>
#define EPS 1e-9
using namespace std;
const int N = 1024;
int n, s, f;
double a, b;
struct point {
    int x, y;
}p[N];
double dis(int i, int j) {
    return  (p[i].x*1.0 - p[j].x*1.0) * (p[i].x*1.0 - p[j].x*1.0) + (p[i].y*1.0 - p[j].y*1.0) * (p[i].y*1.0 - p[j].y*1.0);
}
int vis[N];
vector <int> gra[N];
queue<int> q;
int main() {
    freopen("in.txt", "r", stdin);
    int T;
    scanf("%d", &T);
    while (T--){
        scanf("%d%d%d%lf%lf", &n, &s, &f, &a, &b);
        a += b;
        for (int i = 1; i <= n; ++ i) {
            scanf("%d%d", &p[i].x, &p[i].y);
            gra[i].clear();
        }
        for (int i = 1; i <= n; ++ i) {
            for (int j = i + 1; j <= n; ++ j) {
                if (dis(i, j) < a*a + EPS) {
                    // printf("%f %f---%d, %d\n" ,a, dis(i,j), i,j);
                    //printf("%d %d---%d %d\n" ,p[i].x, p[i].y, p[j].x, p[j].y);
                    gra[i].push_back(j);
                    gra[j].push_back(i);
                }
            }
        }
        memset(vis, 0, sizeof vis);
        q.push(s);
        vis[s] = 1;
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            for (int i = 0; i < gra[u].size(); ++ i){
                if (vis[gra[u][i]]){
                    continue;
                }
                vis[gra[u][i]] = vis[u] + 1;
                //printf("%d %d\n" ,u, gra[u][i]);
                q.push(gra[u][i]);
            }
        }
        if (vis[f]) {
            printf("%d\n", vis[f] - 1);
        }
        else {
            printf("Impossible\n");
        }
    }
    return 0;
}