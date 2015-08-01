#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <queue>
#include <cmath>
#include <map>
using namespace std;
typedef long long ll;
const ll LIMIT = 100000000000000, MID = 10000000;
ll n, k, num;
vector <ll> high, low;
vector <pair <ll, ll> > st[10][2];
map <int, int> mp[10][2];

ll sgn(ll x) {
    if (x < 0)
        return -1;
    if (x == 0)
        return 0;
    return 1;
}

bool check(ll x) {
    if (x < 10) {
        return true;
    }
    if (x < 100) {
        if (x / 10 % 10 - x % 10 != 0) {
            return true;
        }
        return false;
    }
    ll bit1 = sgn(x / 10 % 10 - x % 10), bit2;
    x /= 10;
    while (x >= 10) {
        bit2 = sgn(x / 10 % 10 - x % 10);
        if (bit1 * bit2 != -1) {
            return false;
        }
        bit1 = bit2;
        x /= 10;
    }
    return true;
}
void dfs(int k , int x , int large) {
    if (k == 7) {
        high.push_back(x);
        return;
    }
    for (int i = 0 ; i < 10 ; ++ i) {
        if (large > 1) {
            int a = x % 10 , b = x / 10 % 10;
            if (b > a && i <= a) continue;
            if (b < a && i >= a) continue;
        } else if (large == 1) {
            if (i == x % 10) continue;
        }
        dfs(k + 1 , x * 10 + i , large + (i > 0));
    }
}
void DFS(int k , int x) {
    if (k == 7) {
        int j = x / 1000000;
        int k = x / 100000 % 10;
        int tmp = 0;
        if (j > k)
            tmp = 1;
        st[j][tmp].push_back(make_pair(x % n , x));
        return;
    }
    for (int i = 0 ; i < 10 ; ++ i) {
        if (k > 1) {
            int a = x % 10 , b = x / 10 % 10;
            if (b > a && i <= a) continue;
            if (b < a && i >= a) continue;
        } else if (k == 1) {
            if (i == x % 10) continue;
        }
        DFS(k + 1 , x * 10 + i);
    }
}
int main() {
    scanf("%I64d%I64d", &n, &k);
    num = 0;
    if (n > MID) {
        for (ll now = n; now < LIMIT; now += n) {
            if (check(now)) {
                num++;
                if (num == k) {
                    printf("%I64d\n", now);
                    return 0;
                }
            }
        }
        printf("-1\n");
        return 0;
    }
    else {
        dfs(0, 0, 0);
        for (ll i = 1; i < high.size(); ++i) {
            if (high[i] % n == 0) {
                num++;
                if (num == k) {
                    printf("%I64d\n", high[i]);
                    return 0;
                }
            }
        }
        DFS(0, 0);
        for (ll i = 0; i < 10; ++i) {
            sort(st[i][0].begin(), st[i][0].end());
            sort(st[i][1].begin(), st[i][1].end());
        }
        for (int i = 1; i < high.size(); ++i) {
            int bit1 = high[i] % 10, bit2 = high[i] / 10 % 10;
            ll moddd = (n - high[i] % n * MID % n) % n;
            if (high[i] < 10) {

                for (int j = 0; j < bit1; ++j) {
                    int bg = lower_bound(st[j][0].begin(), st[j][0].end(), make_pair(moddd, 0ll)) - st[j][0].begin();
                    int ed = lower_bound(st[j][0].begin(), st[j][0].end(), make_pair(moddd, MID)) - st[j][0].begin();
                    if (num + ed - bg < k) {
                        num += ed - bg;
                    }
                    else {
                        for (int t = bg; t < ed; ++t) {
                            num++;
                            if (num == k) {
                                printf("%I64d\n", high[i]*MID + st[j][0][t].second);
                                return 0;
                            }
                        }
                    }
                }
                for (int j = bit1 + 1; j < 10; ++j) {
                    int bg = lower_bound(st[j][1].begin(), st[j][1].end(), make_pair(moddd, 0ll)) - st[j][1].begin();
                    int ed = lower_bound(st[j][1].begin(), st[j][1].end(), make_pair(moddd, MID)) - st[j][1].begin();
                    if (num + ed - bg < k) {
                        num += ed - bg;
                    }
                    else {
                        for (int t = bg; t < ed; ++t) {
                            num++;
                            if (num == k) {
                                printf("%I64d\n", high[i]*MID + st[j][1][t].second);
                                return 0;
                            }
                        }
                    }
                }
            }
            else if (bit1 < bit2) {

                for (int j = bit1 + 1; j < 10; ++j) {
                    int bg = lower_bound(st[j][1].begin(), st[j][1].end(), make_pair(moddd, 0ll)) - st[j][1].begin();
                    int ed = lower_bound(st[j][1].begin(), st[j][1].end(), make_pair(moddd, MID)) - st[j][1].begin();
                    if (num + ed - bg < k) {
                        num += ed - bg;
                    }
                    else {
                        for (int t = bg; t < ed; ++t) {
                            num++;
                            if (num == k) {
                                printf("%I64d\n", high[i]*MID + st[j][1][t].second);
                                return 0;
                            }
                        }
                    }
                }
            }
            else if (bit1 > bit2) {

                for (int j = 0; j < bit1; ++j) {
                    int bg = lower_bound(st[j][0].begin(), st[j][0].end(), make_pair(moddd, 0ll)) - st[j][0].begin();
                    int ed = lower_bound(st[j][0].begin(), st[j][0].end(), make_pair(moddd, MID)) - st[j][0].begin();
                    if (num + ed - bg < k) {
                        num += ed - bg;
                    }
                    else {
                        for (int t = bg; t < ed; ++t) {
                            num++;
                            if (num == k) {
                                printf("%I64d\n", high[i]*MID + st[j][0][t].second);
                                return 0;
                            }
                        }
                    }
                }
            }
        }
    }
    printf("-1\n");
    return 0;
}
