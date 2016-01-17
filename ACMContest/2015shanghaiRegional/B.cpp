#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
typedef long long ll;
ll n;
int k;
int ans[101];
void solve(){
    memset(ans,0,sizeof ans);
    ans[k-1] = 1;
    for (int i = k - 1;i >= 1;i--){
        ll t = (1ll << i) & n;
        if (t){
            ans[i-1] = 1;
        }
        else{
            ans[i-1] = 0;
        }
    }
}
int main(){
    freopen("in.txt","r",stdin);
    int t;
    scanf("%d",&t);
    while (t--){
        static int ca = 0;
        printf("Case #%d:\n",++ca);
        scanf("%lld %d",&n,&k);
        //  printf("%d\n",k);
        if (n % 2 == 0){
             n--;
            solve();
            for (int i = 0;i < k - 1;i++){
                printf("%lld ",(1ll << i));
                if (ans[i]){
                    puts("+");
                }
                else{
                    puts("-");
                }
            }
            printf("%lld +\n",(1ll << (k-1)) + 1);
        }
        else{
            solve();
            for (int i = 0;i < k - 1;i++){
                printf("%lld ",(1ll << i));
                if (ans[i]){
                    puts("+");
                }
                else{
                    puts("-");
                }
            }
            printf("%lld +\n",(1ll << (k-1)));
        }
    }
}