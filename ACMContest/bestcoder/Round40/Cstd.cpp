#include<stdio.h>
#include<string.h>
#include<math.h>
#include<algorithm>
#include<vector>
using namespace std;
typedef __int64 ll;
const int M=100005;
int mo;
int f[M],invf[M];
int powmod(int a,int b)
{
    int res=1;
    for(;b;b>>=1,a=(ll)a*a%mo)
        if(b&1)
            res=(ll)res*a%mo;
    return res;
}
int C(int a,int b)
{
    if(a<b)
        return 0;
    if(a==b||b==0)
        return 1;
    return (ll)f[a]*invf[a-b]%mo*invf[b]%mo;
}
int Lucas(int a,int b)
{
    if(a<b)
        return 0;
    if(a==b||b==0)
        return 1;
    return (ll)C(a%mo,b%mo)*Lucas(a/mo,b/mo)%mo;        
}
int main()
{
    int i,j;
    int x1,x2,y1,y2;
    while(~scanf("%d%d%d%d%d",&x1,&y1,&x2,&y2,&mo))
    {
        f[0]=1;
        int now=min(M,mo);
        
        for(i=1;i<now;i++)
            f[i]=(ll)f[i-1]*i%mo;
        invf[now-1]=powmod(f[now-1],mo-2);
        for(i=now-2;i>=0;i--)
            invf[i]=(ll)invf[i+1]*(i+1)%mo;
        //printf("%d*********\n",Lucas(2,1));
        //printf("%d*********\n",C(2,1));
        ll ans=0;
        for(i=y1;i<=y2;i++)
        {
            ans=ans+Lucas(x2+1,i+1)-Lucas(x1,i+1);
            //printf("%d**%d\n",Lucas(x2+1,i+1),Lucas(x1+1,i+1));
            ans%=mo;                
        }
        ans=(ans+mo)%mo;
        printf("%I64d\n",ans);
    }
    return 0;
}