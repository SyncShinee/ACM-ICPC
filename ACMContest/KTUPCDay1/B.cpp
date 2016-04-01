#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
using namespace std;
typedef long long ll;
const int N = 21;
const int MOD = 1e9 + 9;
int n,C;
ll m;
int a[N],c[N];
struct P{
    int n,m;
    int s[N][N];
    P (){
        n = m = 0;
        memset(s, 0, sizeof s);
    }
    P operator *(const P & o) const{
        P t;
        //    t.print();
        t.n = n; t.m = o.m;
        for (int i = 1;i <= n;i++){
            for (int j = 1;j <= o.m;j++){
                for (int k = 1;k <= m;k++){
                    t.s[i][j] = (t.s[i][j] + 1ll * s[i][k] * o.s[k][j] % MOD) % MOD;
                }
            }
        }
        //  t.print();
        return t;
    }
    void print(){
        for (int i = 1;i <= n;i++){
            for (int j = 1;j <= m;j++){
                printf("%d ",s[i][j]);
            }
            printf("\n");
        }
    }
};
P power(P t, ll n){
    P res;
    res.n = res.m = t.n;
    for (int i = 1;i <= t.n;i++) res.s[i][i] = 1;

    while (n){
        if (n & 1ll) res = res * t;
        n >>= 1ll;
        t = t * t;
    }
    return res;
}
int main(){
    freopen("in.txt","r",stdin);
    scanf("%d%I64d%d",&n,&m,&C);
    for (int i = 1;i <= n;i++) scanf("%d",&a[i]);
    for (int i = 1;i <= C;i++) scanf("%d",&c[i]);
    P ans;
    ans.n = 1;
    ans.m = n;
    for (int i = 1;i <= n;i++) ans.s[1][i] = a[i];

    P tmp;
    tmp.n = n;
    tmp.m = n;

    for (int i = 1;i <= C;i++) tmp.s[n + 1 - c[i]][n] = 1;
    for (int i = 1;i < n;i++) tmp.s[i + 1][i] = 1;
    tmp = power(tmp, m - 1);
    //  ans.print();
//    tmp.print();
    ans = ans * tmp;
//    ans.print();
    printf("%d\n",ans.s[1][1]);
    
}