#include <cstdio>
#include <algorithm>
#include <cstring>
#include <cmath>
using namespace std;
typedef long long ll;
const int N = 128;
const long double EPS = 1e-10;
long double a[N][N], x[N];
int equ, var;
double ans[N];
ll p[N][N];

int n;

int main() {
    freopen("in.txt","r",stdin);
    scanf("%d", &n);
    for (int i = 0; i < n; ++ i) {
        for (int j = 0; j < n; ++ j) {
            scanf("%I64d", &p[i][j]);
        }
    }
    equ = var = n;
    for (int i = 0; i < n; ++ i) {
        for (int j = 0; j < n; ++ j) {
            a[i][j] = i != j;
        }
        ll tmp = 0;
        for (int j = 0; j < n; ++ j) {
            tmp += p[i][j];
        }
        x[i] = tmp;
    }
    for (int k = 0, col = 0; k < equ && col < var; k ++, col ++) {
        int max_k = k;
        for (int i = k + 1; i < equ; ++ i) {
            if (fabs(a[i][col]) > fabs(a[max_k][col])) {
                max_k = i;
            }
        }
        if(fabs(a[max_k][col]) < EPS) {
            break;
        }
        if (max_k != k) {
            swap(x[k], x[max_k]);
            for (int i = col; i < var; ++ i) {
                swap(a[k][i], a[max_k][i]);
            }
        }
        x[k] /= a[k][col];
        for (int i = col + 1; i < var; ++ i) {
            a[k][i] /= a[k][col];
        }
        a[k][col] = 1;
        for (int i = 0; i < equ; ++ i) {
            if (i != k) {
                x[i] -= a[i][col] * x[k];
                for (int j = col + 1; j < var; ++ j) {
                    a[i][j] -= a[i][col] * a[k][j];
                }
                a[i][col] = 0;
            }
        }
    }
    for (int i = 0; i < n; ++ i) {
        ans[i] = x[i];
    }
    for (int i = 0; i < n; ++ i) {
        for (int j = 0; j < n; ++ j) {
            if (i == j) {
                printf("%.0f", ans[i]);
            }
            else {
                printf("%I64d", p[i][j]);
            }
            printf("%c", " \n"[j == n - 1]);
        }
    }
    return 0;
}