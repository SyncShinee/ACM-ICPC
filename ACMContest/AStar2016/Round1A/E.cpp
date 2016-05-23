#include <cstdio>
#include <algorithm>
#include <cstring>
#include <vector>
using namespace std;
const int N = 64;
typedef long long ll;
ll PO[N];
ll numB[N];
ll numD[N];
ll gaoD(ll x);
ll gaoB(ll x);

ll gaoB(ll x) {
    if (x == 0) return 0;
    int pos = upper_bound(PO, PO + 61, x) - PO - 1;
    if (x == PO[pos]) {
        return numB[pos];
    }
    ll remain = x - PO[pos] - 1;
    return numB[pos] + 1 + numD[pos] - gaoD(PO[pos] - remain);
}

ll gaoD(ll x) {
    if (x == 0) return 0;
    int pos = upper_bound(PO, PO + 61, x) - PO - 1;
    return x - gaoB(x);
}

void pre() {
    for (int i = 0; i <= 60; ++ i) {
        PO[i] = (1ll << i) - 1;
    }
    numB[0] = numD[0] = numD[1] = 0, numB[1] = 1;
    for (int i = 2; i <= 60; ++ i) {
        numB[i] = numB[i - 1] + 1 + numD[i - 1];
        numD[i] = PO[i] - numB[i];
    }
}
int main() {
    int T;
    ll l, r;
    scanf("%d", &T);
    pre();
    while (T --) {
        scanf("%lld%lld", &l, &r);
        printf("%lld\n", gaoB(r) - gaoB(l - 1));
    }
    return 0;
}
