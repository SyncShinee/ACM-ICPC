#include <cstdio>
#include <algorithm>

using namespace std;
int gcd(int a,int b){
    if (b == 0) return a;
    return gcd(b,a%b);
}
int main(){
    freopen("in.txt","r",stdin);
    int t;
    scanf("%d",&t);
    while (t--){
        static int ca = 0;
        printf("Case #%d: ",++ca);
        int x,y;
        scanf("%d %d",&x,&y);
        int g = gcd(x,y);
        x /= g;
        y /= g;
        int cnt = 1;
        while (true){
            if (y < x) swap(x,y);
            if (y % (x + 1) == 0) {
                cnt++;
                y /= x + 1;
            }
            else{
                break;
            }
        }
        printf("%d\n",cnt);
    }
}