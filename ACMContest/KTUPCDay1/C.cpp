#include <cstdio>
#include <algorithm>
#include <cstring>
#include <queue>
using namespace std;
const int N = 32;
int n, m;
struct Point {
    int x, y;
    Point(int _x = 0, int _y = 0) : x(_x), y(_y) {}
}st, ed, ga;
struct node {
    int a, b, c, d, e;
    node(int _a = 0, int _b = 0, int _c = 0, int _d = 0, int _e = 0) {
        a = _a;
        b = _b;
        c = _c;
        d = _d;
        e = _e;
    }
};
bool vis[N][N][N][N];
char s[N][N];
queue<node> q;
int dx[] = {1, 0, -1, 0};
int dy[] = {0, 1, 0, -1};
int main() {
    scanf("%d%d", &n, &m);
    int ans = -1;
    for (int i = 0; i <= n + 1; ++ i) {
        for (int j = 0; j <= m + 1; ++ j) {
            s[i][j] = 'X';
        }
    }
    for (int i = 1; i <= n; ++ i) {
        scanf("%s", s[i] + 1);
        s[i][m + 1] = 'X';
    }
    for (int i = 1; i <= n; ++ i) {
        for (int j = 1; j <= m; ++ j) {
            if (s[i][j] == 'A') {
                st.x = i;
                st.y = j;
            }
            else if (s[i][j] == 'G') {
                ga.x = i;
                ga.y = j;
            }
            else if (s[i][j] == 'P') {
                ed.x = i;
                ed.y = j;
            }
        }
    }
    q.push(node(st.x, st.y, ga.x, ga.y, 0));
    while (!q.empty()) {
        node u = q.front();
        q.pop();
        Point A = Point(u.a, u.b);
        Point G = Point(u.c, u.d);
        for (int i = 0; i < 4; ++ i) {
            Point v = Point(A.x + dx[i], A.y + dy[i]);
            if (s[v.x][v.y] == 'X') {
                continue;
            }
            Point Gv;
            if (G.y < v.y) {
                Gv.x = G.x;
                Gv.y = G.y + 1;
                if (s[Gv.x][Gv.y] == 'X') {
                    if (G.x < v.x) {
                        Gv.x = G.x + 1;
                        Gv.y = G.y;
                        if (s[Gv.x][Gv.y] == 'X') {
                            Gv = G;
                        }
                    }
                    else if (G.x > v.x) {
                        Gv.x = G.x - 1;
                        Gv.y = G.y;
                        if (s[Gv.x][Gv.y] == 'X') {
                            Gv = G;
                        }
                    }
                    else {
                        Gv = G;
                    }
                }
            }
            else if (G.y > v.y) {
                Gv.x = G.x;
                Gv.y = G.y - 1;
                if (s[Gv.x][Gv.y] == 'X') {
                    if (G.x < v.x) {
                        Gv.x = G.x + 1;
                        Gv.y = G.y;
                        if (s[Gv.x][Gv.y] == 'X') {
                            Gv = G;
                        }
                    }
                    else if (G.x > v.x) {
                        Gv.x = G.x - 1;
                        Gv.y = G.y;
                        if (s[Gv.x][Gv.y] == 'X') {
                            Gv = G;
                        }
                    }
                    else {
                        Gv = G;
                    }
                }
            }
            else {
                if (G.x < v.x) {
                    Gv.x = G.x + 1;
                    Gv.y = G.y;
                    if (s[Gv.x][Gv.y] == 'X') {
                        Gv = G;
                    }
                }
                else if (G.x > v.x) {
                    Gv.x = G.x - 1;
                    Gv.y = G.y;
                    if (s[Gv.x][Gv.y] == 'X') {
                        Gv = G;
                    }
                }
                else {
                    Gv = G;
                }
            }
            if (Gv.x == v.x && Gv.y == v.y) {
                continue;
            }
            if (vis[v.x][v.y][Gv.x][Gv.y]) {
                continue;
            }
            vis[v.x][v.y][Gv.x][Gv.y] = true;
            q.push(node(v.x, v.y, Gv.x, Gv.y, u.e + 1));
            if (v.x == ed.x && v.y == ed.y) {
                if (ans == -1) {
                    ans = u.e + 1;
                }
                else {
                    ans = min(ans, u.e + 1);
                }
            }
        }
    }
    printf("%d\n", ans);
    return 0;
}