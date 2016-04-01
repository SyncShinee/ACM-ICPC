#include <cstdio>
#include <algorithm>
#include <cstring>
#include <vector>

using namespace std;
const int N = 31;
const int M = 210;
vector <int> g[M];
char s1[N], s2[M][10];
int n, match[M], used[M];
void add(int u, int v){
    g[u].push_back(v);
    g[v].push_back(u);
}
int dfs(int v){
    used[v] = 1;
    for (int i = 0;i < g[v].size();i++){
        int u = g[v][i], w = match[u];
        if (w < 0 || (!used[w] && dfs(w))){
            match[u] = v;
            match[v] = u;
            return 1;
        }
    }
    return 0;
}
int bmatch(){
    int res = 0;
    memset(match, -1, sizeof match);
    for (int i = 1;i <= n;i++) {
        if (match[i] < 0){
            memset(used, 0, sizeof used);
            if (dfs(i)){
                res++;
            }
        }
    }
    return res;
}
int main(){
    freopen("in.txt","r",stdin);
    scanf("%s",s1);
    scanf("%d",&n);
    for (int i = 1;i <= n;i++){
        for (int j = 1;j <= 6;j++){
            scanf(" %c",&s2[i][j]);
        }
    }
    int len = strlen(s1);
    for (int i = 0;i < len;i++){
        for (int j = 1;j <= n;j++){
            int flag = 0;
            for (int k = 1;k <= 6;k++){
                if (s1[i] == s2[j][k]){
                    flag = 1;
                    break;
                }
            }
            if (flag) add(i + 1, j + len);
        }
    }
  
    n = len;
    // printf("%d\n",n);
    int ans = bmatch();
    if (ans == len){
        printf("YES\n");
    }else{
        printf("NO\n");
    }
}