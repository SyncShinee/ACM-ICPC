#include <iostream>
#include <cstdio>
#include <cstring>
#include <string>
#include <cmath>
#include <ctype.h>
#include <limits.h>
#include <cstdlib>
#include <algorithm>
#include <vector>
#include <queue>
#include <map>
#include <stack>
#include <set>
#include <bitset>
#define CLR(a) memset(a, 0, sizeof(a))
#define REP(i, a, b) for(int i = a;i < b;i++)
#define REP_D(i, a, b) for(int i = a;i <= b;i++)

typedef long long ll;

using namespace std;

const int N = 10010;
const double EPS = 1e-9;

struct node{
    int id;
    double val;
    node (int _id = 0, double _val = 0) : id(_id), val(_val) {}
}a[N];

bool operator < (const node &A, const node &B) {
    return A.val < B.val;
}

bool flag[N];
vector <int> ans;
int n;
int main()
{
    freopen("Ein.txt", "r", stdin);
    while (~scanf("%d", &n)) {
        memset(flag, 0, sizeof flag);
        ans.clear();
        for (int i = 1; i <= n; ++ i) {
            scanf("%lf", &a[i].val);
            a[i].id = i;
        }
        if (n == 1) {
            puts("1");
            puts("1");
        }
        sort(a + 1, a + n + 1);
        int l = lower_bound(a + 1, a + n + 1, node(0, -1 - EPS)) - a;
        int r = upper_bound(a + 1, a + n + 1, node(0, 1 + EPS)) - a - 1;

        //printf("%d %d\n", l, r);
        if (l & 1) {
            for (int i = 1; i < l; ++ i) {
                flag[a[i].id] = true;
            }
        }
        else {
            for (int i = 1; i < l - 1; ++ i) {
                flag[a[i].id] = true;
            }
            if (l <= r) {
                if (a[l - 1].val * a[l].val > 1 + EPS) {
                    flag[a[l - 1].id] = flag[a[l].id] = true;
                }
            }
        }
        for (int i = r + 1; i <= n; ++ i) {
            flag[a[i].id] = true;
        }
        if (r == n) {
            if (l == 1) {
                if (a[l].val * a[l + 1].val > a[r].val + EPS) {
                    flag[a[l].id] = flag[a[l + 1].id] = true;
                }
                else {
                    flag[a[r].id] = true;
                }
            }
            else if (l == 2) {
                if (a[1].val * a[2].val > a[r].val + EPS) {
                    flag[a[1].id] = flag[a[2].id] = true;
                }
                else {
                    flag[a[r].id] = true;
                }
            }
        }
        for (int i = 1; i <= n; ++ i) {
            if (flag[i]) {
                ans.push_back(i);
            }
        }
        printf("%d\n", ans.size());
        for (int i = 0; i < ans.size(); ++ i) {
            printf("%d%c", ans[i], " \n"[i == ans.size() - 1]);
        }
    }
    //freopen("5Eout.txt", "w", stdout);
    return 0;
}