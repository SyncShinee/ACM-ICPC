#include <cstdio>
#include <algorithm>
#include <cstring>
#include <cmath>
#include <vector>
#include <map>
#include <queue>
#define PB push_back
using namespace std;
const int N = 512, M = 100010, NM = 1024, STOPVALVE = 0, INTERSECTION = 1;
const double EPS = 1e-9;
struct Point {
    double x, y;
    int type;
    int id;
    Point(double _x = 0, double _y = 0) : x(_x), y(_y) {}
}a[NM], p[M], STP, EDP;

int dcmp(const double &x, const double &y) {
    if (fabs(x - y) < EPS) return 0;
    if (x < y) return -1;
    return 1;
}

int dcmp(const double &x) {
    if (fabs(x) < EPS) return 0;
    if (x > EPS) return 1;
    return -1;
}

bool operator == (const Point &A, const Point &B) {
    return dcmp(A.x, B.x) == 0 && dcmp(A.y, B.y) == 0;
}

bool operator < (const Point &A, const Point &B) {
    return dcmp(A.x, B.x) == -1 || dcmp(A.x, B.x) == 0 && dcmp(A.y, B.y) == -1;
}

Point operator - (const Point &A, const Point &B) {
    return Point(A.x - B.x, A.y - B.y);
}

double operator ^ (const Point &A, const Point &B) {
    return A.x * B.y - A.y * B.x;
}

bool pcmp(const int &x, const int &y) {
    return p[x] < p[y];
}
struct Line {
    Point st, ed;
}line[N];

double dist(Point a, Point b) {
    return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}

int n, m, tot, st_node, ed_node;
int vis[M];
vector <int> gra[M], online[N];
map <Point, int> mp;

bool onSeg(Point P,Line L)
{
    return
        dcmp((L.st - P) ^ (L.ed - P)) == 0 &&
        dcmp((P.x - L.st.x) * (P.x - L.ed.x)) <= 0 &&
        dcmp((P.y - L.st.y) * (P.y - L.ed.y)) <= 0;
}
bool have_intersection(Line li, Line ln) {
    return
        max(li.st.x, li.ed.x) >= min(ln.st.x, ln.ed.x) &&
        max(ln.st.x, ln.ed.x) >= min(li.st.x, li.ed.x) &&
        max(li.st.y, li.ed.y) >= min(ln.st.y, ln.ed.y) &&
        max(ln.st.y, ln.ed.y) >= min(li.st.y, li.ed.y) &&
        dcmp((ln.st - li.ed) ^ (li.st - li.ed)) * dcmp((ln.ed - li.ed)^ (li.st - li.ed)) <= 0 &&
        dcmp((li.st - ln.ed) ^ (ln.st - ln.ed)) * dcmp((li.ed - ln.ed)^ (ln.st - ln.ed)) <= 0;
}
Point intersect(Line li, Line ln) {
    if (li.st == ln.st || li.st == ln.ed) return li.st;
    if (li.ed == ln.st || li.ed == ln.ed) return li.ed;
    Point di = li.ed - li.st, dn = ln.ed - ln.st;
    double t = ((li.st ^ di) - (ln.st ^ di)) / (dn ^ di);
    Point ret;
    ret.x = ln.st.x + t * dn.x;
    ret.y = ln.st.y + t * dn.y;
    return ret;
}
void get_graph() {
    tot = 1;
    // stopvalve
    for (int i = 0; i < n; ++ i) {
        for (int j = 0; j < m + 2; ++ j) {
            if (!onSeg(a[j], line[i])) continue;
            if (!mp.count(a[j])) {
                p[tot] = a[j];
                p[tot].type = j < m ? STOPVALVE : INTERSECTION;
                mp[a[j]] = tot ++;
            }
            online[i].PB(mp[a[j]]);
        }
    }
    // intersection
    for (int i = 0; i < n; ++ i) {
        for (int j = i + 1; j < n; ++ j) {
            if (have_intersection(line[i], line[j])) {
                Point tmp = intersect(line[i], line[j]);
                int pos;
                if (!mp.count(tmp)) {
                    p[tot] = tmp;
                    p[tot].type = INTERSECTION;
                    mp[tmp] = pos = tot ++;
                }
                else {
                    pos = mp[tmp];
                }
                online[i].PB(pos);
                online[j].PB(pos);
            }
        }
    }
    // end point
    for (int i = 0; i < n; ++ i) {
        int pos;
        if (!mp.count(line[i].st)) {
            p[tot] = line[i].st;
            p[tot].type = INTERSECTION;
            mp[line[i].st] = pos = tot ++;
        }
        else {
            pos = mp[line[i].st];
        }
        online[i].PB(pos);
        if (!mp.count(line[i].ed)) {
            p[tot] = line[i].ed;
            p[tot].type = INTERSECTION;
            mp[line[i].ed] = pos = tot ++;
        }
        else {
            pos = mp[line[i].ed];
        }
        online[i].PB(pos);
    }
    // unique
    for (int i = 0; i < n; ++ i) {
        sort(online[i].begin(), online[i].end(), pcmp);
        online[i].erase(unique(online[i].begin(), online[i].end()), online[i].end());
    }
    for (int i = 0; i < tot; ++ i) {
        gra[i].clear();
    }
    // build graph
    for (int i = 0; i < n; ++ i) {
        for (int j = 0; j < online[i].size() - 1; ++ j) {
            int u = online[i][j], v = online[i][j + 1];
            gra[u].PB(v);
            gra[v].PB(u);
        }
    }
    st_node = mp[STP];
    ed_node = mp[EDP];
}
queue <int> q;
void bfs1() {
    q.push(ed_node);
    vis[ed_node] = 1;
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        if (p[u].type == STOPVALVE) continue;
        //printf("debug---%f %f\n", p[u].x, p[u].y);
        for (int i = 0; i < gra[u].size(); ++ i) {
            int v = gra[u][i];
            //printf("%d----%d\n", u, v);
            if (!vis[v]) {
                //printf("biaoji ======= %d\n", v);
                vis[v] = 1;
                q.push(v);
            }
        }
    }
}
double bfs2() {
    double ret = 0;
    vis[st_node] = 2;
    q.push(st_node);
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        //printf("dfs2----%d-%f %f\n", u, p[u].x, p[u].y);
        if (vis[u] == 1) continue;
        //printf("111");
        for (int i = 0; i < gra[u].size(); ++ i) {
            int v = gra[u][i];
            //printf("%d %d\n", u, v);
            if (vis[v] < 2) {
                if (vis[v] == 0) vis[v] = 2;
                q.push(v);
                ret += dist(p[u], p[v]);
            }
        }
    }
    return ret;
}
double solve() {
    get_graph();
    /*
    printf("%d\n", tot);
    for (int i = 0; i < tot; ++ i) {
        printf("%d %f %f %d\n", i, p[i].x, p[i].y, p[i].type);
    }
    for (int i = 0; i < n; ++ i) {
        printf("online [%d] == %d\n", i + 1, online[i].size());
        for (int j = 0; j < online[i].size(); ++ j) {
            printf("%d %f %f\n", p[online[i][j]].type, p[online[i][j]].x, p[online[i][j]].y);
        }
    }
    */
    bfs1();
    if (vis[st_node]) return -1;
    double sum = 0;
    for (int i = 0; i < n; ++ i) {
        sum += dist(line[i].st, line[i].ed);
    }
    return sum - bfs2();
}
int main() {
    freopen("in.txt", "r", stdin);
    while (~scanf("%d%d", &n, &m)) {
        memset(vis, 0, sizeof vis);
        mp.clear();
        for (int i = 0; i < n; ++ i) {
            online[i].clear();
        }
        for (int i = 0; i < n; ++ i) {
            scanf("%lf%lf%lf%lf", &line[i].st.x, &line[i].st.y, &line[i].ed.x, &line[i].ed.y);
        }
        for (int i = 0; i < m + 2; ++ i) {
            scanf("%lf%lf", &a[i].x, &a[i].y);
        }
        STP = a[m];
        EDP = a[m + 1];
        double ans = solve();
        if (ans < -EPS) puts("-1");
        else printf("%.10f\n", ans);
    }
    return 0;
}