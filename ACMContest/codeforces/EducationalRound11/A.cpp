#include <cstdio>
#include <algorithm>
#include <vector>
#include <cstring>
using namespace std;
vector <int> ans;
const int N = 1010;
int a[N];
int gcd(int x, int y) {
    if (y == 0) return x;
    return gcd(y, x % y);
}
int main() {
    int n;
    scanf("%d", &n);
    for (int i = 0; i < n; ++ i) {
	scanf("%d", &a[i]);
    }
    ans.push_back(a[0]);
    for (int i = 1; i < n; ++ i) {
	if (gcd(a[i], a[i - 1]) > 1) {
	    ans.push_back(1);
	}
	ans.push_back(a[i]);
    }
    printf("%d\n", ans.size() - n);
    for (int i = 0; i < ans.size(); ++ i) {
	printf("%d%c", ans[i]," \n"[i == ans.size() - 1]);
    }
    return 0;
}
