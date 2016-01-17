#include <iostream>
#include <cstdio>
#include <cstring>

using namespace std;

typedef long long ll;

const int M = 7340033;
const int maxn = 5e5 + 100;
const int key = 100000;

int c[5][maxn], num[5];
int a1[maxn], a2[maxn];
int x1[maxn], x2[maxn];
int rev[maxn], n;

int add(int a, int b) {
    int c = a + b;
    if(c >= M)
        c -= M;
    return c;
}
int sub(int a, int b) {
    if(a < b)
        a += M;
    return a - b;
}
int power(int x, int n) {
    int res = 1, tmp = x % M;
    while(n) {
        if(n & 1)
            res = (ll)res * (ll)tmp % M;
        tmp = (ll)tmp * (ll)tmp % M;
        n >>= 1;
    }
    return res;
}
int inverse(int x) {
    return power(x, M - 2);
}

void change(int y[], int len) {
    int i, j, k;
    for(i = 1, j = len / 2; i < len - 1; i++) {
        if(i < j) swap(y[i], y[j]);
        k = len / 2;
        while(j >= k) {
            j -= k;
            k /= 2;
        }
        if(j < k) j += k;
    }
}

void fft(int y[], int len, int on) {
    change(y, len);
    for(int h = 2; h <= len; h <<= 1) {
        int unit_p0 = power(3, (M - 1) / h);
        if(on == -1)
            unit_p0 = inverse(unit_p0);
        for(int j = 0; j < len; j += h) {
            int unit = 1;
            for(int k = j; k < j + h / 2; k++) {
                int u = y[k];
                int t = (ll)unit * (ll)y[k + h / 2] % M;
                y[k] = add(u, t);
                y[k + h / 2] = sub(u, t);
                unit = (ll)unit * (ll)unit_p0 % M;
            }
        }
    }
    if(on == -1) {
        int key = inverse(len);
        for(int i = 0; i < len; i++) {
            y[i] = (ll)y[i] * (ll)key %M;
        }
    }
}

void solve() {
    for(int i = 0; i < 4; i++) {
        int a = num[i];
        c[i][0] = 1;
        for(int j = 1; j <= key; j++) {
            if(j > a)
                c[i][j] = 0;
            else {
                c[i][j] = (ll)c[i][j - 1] * (ll)(a - j + 1) % M * (ll)rev[j] % M;
            }
        }
    }
    memset(a1, 0, sizeof(a1));
    memset(a2, 0, sizeof(a2));
    for(int i = 0; i <= key; i++) {
        a1[i] = (ll)c[0][i] * (ll)c[2][i] % M;
        a2[i] = (ll)c[1][i] * (ll)c[3][i] % M;
    }
     
    int len = key;
    int len1 = 1;
    while(len1 <2 * len) {
        len1 *= 2;
    }
    fft(a1, len1, 1);
    fft(a2, len1, 1);
    for(int i = 0; i < len1; i++) {
        a1[i] = (ll)a1[i] * (ll)a2[i] % M;
    }
    fft(a1, len1, -1);
    for(int i = 1; i <= n; i++) {
        if(i % 2 == 1)
            printf("0");
        else
            printf("%d", a1[i / 2]);
        if(i != n) printf(" ");
        else printf("\n");
    }
}

int main() {
    freopen("h.txt", "r", stdin);
    for(int i = 1; i <= key; i++)
        rev[i] = inverse(i);
    int ncase;
    scanf("%d", &ncase);
    for(int _ = 1; _ <= ncase; _++) {
        printf("Case %d:\n", _);
        scanf("%d", &n);
        memset(num, 0, sizeof(num));
        for(int i = 1; i <= n; i++) {
            int x, y;
            scanf("%d%d", &x, &y);
            if(x >= 0 && y >= 0)
                num[0]++;
            if(x <= 0 && y >= 0)
                num[1]++;
            if(x <=0 && y <= 0)
                num[2]++;
            if(x >=0 && y <= 0)
                num[3]++;
        }
        solve();
    }
    return 0;
}
