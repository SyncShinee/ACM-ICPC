#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <map>
#include <algorithm>

using namespace std;

const int maxn = 1000 + 10;
const double Pi = acos(-1.0);
double alp[maxn], r, th, a;
int alpn, n;
map<int, map<int, int> > mp; 

double f(double aa, double bb) {
    return a * a / 6 * (bb * bb * bb - aa * aa * aa);
}

int getk(double r, double th) {
    //printf("222 %f %f %f\n", r, th, a);
    int low = 0, high = 1e9;
    while(low  <=  high) {
        int mid = (low + high) / 2;
        if(a * (th + mid * 2 * Pi) > r)
            high = mid - 1;
        else
            low = mid + 1;
    }
    /* for(int i = 0; ;i++) {
        printf("333  %f\n", a * (th + i * 2 * Pi));
        if(a * (th + i * 2 * Pi) > r) {
            printf("111  %lf\n",  i - 1);
            return i - 1;
        }
        }*/
    //    printf("****  %f\n", high - 1);
    return high;
}
void solve() {
    mp.clear();
    double ans = 0;
    scanf("%d", &alpn);
    for(int i = 0; i < alpn; i++) {
        scanf("%lf", &alp[i]);
    }
    if(alpn == 0) {
        scanf("%d", &n);
        for(int i = 0; i < n; i++) {
            double a, b;
            scanf("%lf%lf", &a, &b);
        }
        printf("-1\n");
        return ;
    }
    sort(alp, alp + alpn);
    alp[alpn] = alp[0] + 2 * Pi;
    alpn++;
    
    scanf("%d", &n);
    for(int i = 0; i < n; i++) {
        scanf("%lf %lf", &r, &th);
        int key;
        for(int j = 0;;j++) {
            if(alp[j] > th) {
                key = j;
                break;
            }
        }
        double a1, a2;
        a2 = alp[key];
        if(key != 0)
            a1 = alp[key - 1];
        else {
            a1 = alp[alpn - 2] - 2 * Pi;
            // swap(a1, a2);
        }
        //            a2 = alp[alpn - 2] - 2 * Pi;
        int k = getk(r, th);
        if(mp[key][k])
            continue;
        else {
            mp[key][k] = 1;
            if(k == -1 && a1 < 0) {
                ans += f(0, a2);
                printf("fadsfasd");
            }
            else {
            ans += f(a1 + (k + 1) * 2 * Pi, a2 + (k + 1) * 2 * Pi);
            ans -= f(a1 + k * 2 * Pi, a2 + k * 2 * Pi);
            }
        }
    }
    printf("%.10f liters\n", ans/10);
}

int main() {
    freopen("j.txt", "r", stdin);
    int ncase;
    scanf("%d", &ncase);
    for(int _ = 1; _ <= ncase; _++) {
        printf("Spiral %d: ", _);
        scanf("%lf", &a);
        solve();
    }
    return 0;
}
