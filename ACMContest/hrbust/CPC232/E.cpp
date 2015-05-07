#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
#include <stack>
using namespace std;
const double PI = acos(-1);
const double eps = 1e-8;
int dcmp(double a)
{
    if (a < -eps) return -1;
    else if (a > eps) return 1;
    else return 0;
}
struct data
{
    int x,ang,v;
    double vy(){return sin(ang*PI/180) * v;}
    bool operator < (const data a) const{return x < a.x;}
}a[100005];
stack <data> st;
int main()
{
    int T;
    scanf("%d", &T);
    while (T--)
    {
        int n;
        scanf("%d", &n);
        while (!st.empty()) st.pop();
        for (int i = 0; i < n; i ++)
            scanf("%d", &a[i].x);
        for (int i = 0; i < n; i ++)
            scanf("%d%d", &a[i].ang, &a[i].v);
        data tmp;
        sort(a,a+n);
        for (int i = 0 ; i < n; i ++)
        {
            if (st.empty())
                st.push(a[i]);
            else
            {
                data top = st.top();
                if (a[i].ang <= top.ang)
                    st.push(a[i]);
                else
                {
                    if (a[i].x == top.x)
                        st.push(a[i]);
                    else
                    {
                        while (!st.empty() && (top = st.top(),dcmp(a[i].vy() - top.vy()) > 0 && a[i].ang > top.ang))
                            st.pop();
                        if (st.empty() || a[i].ang <= top.ang)
                            st.push(a[i]);
                    }
                }
            }
        }
        printf("%d\n",st.size());
    }
}