#include <cstdio>
#include <algorithm>
#include <cstring>
#include <cmath>
using namespace std;
int n;
Point {
    double x, y;
}
double r, ans;
double solve(int i, int j) {
    
}
int main() {
    ans = 0;
    scanf("%d%lf", &n, &r);
    for (int i = 1; i <= n; ++ i) {
        scanf("%lf%lf", &p[i].x, &p[i].y);
    }
    for (int i = 1; i <= n; ++ i) {
        for (int j = i + 1; j <= n; ++ j){
            ans = max(ans, solve(i, j));
        }
    }
    printf("%f", ans);
    return 0;
}