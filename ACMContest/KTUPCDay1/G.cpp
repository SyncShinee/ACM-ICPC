#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
const int N = 1e5 + 100;
char s[N];
int n;
int main(){
    scanf("%s",s);
    n = strlen(s);
    int ans = 0;
    for (int i = 0;i < n;i++){
        if (s[i] == '0') ans++;
    }
    ans = min(ans, n - ans);
    printf("%d\n",ans);
}