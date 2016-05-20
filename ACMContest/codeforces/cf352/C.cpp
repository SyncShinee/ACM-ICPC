#include <cstdio>
#include <algorithm>
#include <set>
#include <vector>
#define PII pair <int, int>
#define PB push_back
#define MP make_pair
#define FI first
#define SE second
using namespace std;
typedef long long ll;
const int N = 200010;
int a[N];
ll sum;
set < PII > st;
int n;
bool cover(PII x, PII y) {
    return x.FI <= y.FI && x.SE >= y.SE;
}

PII cross(PII x, PII y) {
    return MP(max(x.FI, y.FI), min(x.SE, y.SE));
}

ll area(PII x) {
    int l = max(0, x.SE - x.FI + 1);
    return 1ll * l * (l + 1) / 2;
}

void insert(int x, int y) {
    if (x < 1 || x > n || y < 1 || y > n || x > y) {
        return;
    }
    PII p(x, y);
    PII pre(0, 0);
    set < PII > :: iterator it = st.lower_bound(p);
    if (it != st.end() && cover(*it, p)) {
        return;
    }
    if (it != st.begin()) {
        it --;
        pre = *it;
        if (cover(*it, p)) {
            return;
        }
        it ++;
    }
    sum += area(p);
    sum -= area(cross(p, pre));
    while (it != st.end() && cover(p, *it)) {
        sum -= area(*it);
        sum += area(cross(pre, *it));
        pre = *it;
        st.erase(it ++);
    }
    if (it != st.end()) {
        sum -= area(cross(*it, p));
        sum += area(cross(pre, *it));
    }
    st.insert(p);
}

int main() {
    int x;
    scanf("%d", &n);
    for (int i = 1; i <= n; ++ i) {
        scanf("%d", &x);
        a[x] = i;
    }
    ll ans = 0;
    sum = 0;
    for (int i = N - 1; i > 0; -- i) {
        vector <int> V;
        for (int j = i; j < N; j += i) {
            if (a[j]) {
                V.PB(a[j]);
            }
        }
        int s = V.size();
        if (s < 2) {
            continue;
        }
        sort(V.begin(), V.end());
        ll tmp = sum;
        insert(V[0] + 1, V[s - 1] - 1);
        insert(V[1] + 1, n);
        insert(1, V[s - 2] - 1);
        ans += (sum - tmp) * i;
    }
    printf("%lld\n", ans);
    return 0;
}
