#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
using namespace std;
const int N = 20;
int f[1<<N], n, a[N];
vector <int> g;
int main(){
    scanf("%d",&n);
    for (int i = 0;i < n;i++) scanf("%d",&a[i]);

    for (int i = 0;i < n;i++){
        for (int j = 0;j < n;j++){
            for (int k = 0;k < n;k++){
                if (i == j || j == k || i == k) continue;
                if (a[i] >= a[j] + a[k]) continue;
                if (a[j] >= a[i] + a[k]) continue;
                if (a[k] >= a[i] + a[j]) continue;
                g.push_back((1<<i)|(1<<j)|(1<<k));
            }
        }
    }
    f[0] = 0;
    int ans = 0;
    for (int i = 0;i < (1<<n);i++){
        for (int j = 0;j < g.size();j++){
            int mask = g[j];
            if (mask & i) continue;
            f[mask|i] = f[i] + 1;
            ans = max(ans, f[i] + 1);
        }
    }
    printf("%d\n",ans);
}