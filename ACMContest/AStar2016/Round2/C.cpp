#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
using namespace std;
const int N = 100010;
struct node {
    int x, id;
    node (int _l = 0, int _r = 0) : x(_l), id(_r) {}
};
bool operator < (const node &A, const node &B) {
    return A.x < B.x || A.x == B.x && A.id < B.id;
}
vector <node> ship[2];

int main() {
    int T, n, x, y, d, drt;
    scanf("%d", &T);
    for (int cas = 1; cas <= T; ++ cas) {
        scanf("%d", &n);
        ship[0].clear();
        ship[1].clear();
        for (int i = 0; i < n; ++ i) {
            scanf("%d%d%d%d", &x, &y, &d, &drt);
            if (d - y < - d - x) continue;
            ship[drt == 1].push_back(node(- d - x, 0));
            ship[drt == 1].push_back(node(d - y, 1));
        }
        sort(ship[0].begin(), ship[0].end());
        sort(ship[1].begin(), ship[1].end());
        int mx = 0, ans = 0, nw0 = 0, nw1 = 0, j = 0;
        for (int i = 0; i < ship[0].size(); ++ i) {
            if (ship[0][i].id == 0) nw0 ++;
            else nw0 --;
            while (j < ship[1].size() && ship[1][j].x <= ship[0][i].x) {
                if (ship[1][j].id == 0) nw1 ++;
                else nw1 --;
                mx = max(mx, nw1);
                j ++;
            }
            ans = max(ans, nw0 + mx);
        }
        printf("Case #%d:\n", cas);
        printf("%d\n", ans);
    }
    return 0;
}
