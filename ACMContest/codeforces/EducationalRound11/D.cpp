#include <cstdio>
#include <algorithm>
#include <cstring>
#include <map>
using namespace std;
const int N = 2048;
struct node {
    int x, y;
    node (int _x = 0, int _y = 0) : x(_x), y(_y) {}
}p[N];
bool operator < (const node &A, const node &B) {
    return A.x < B.x || A.x == B.x && A.y < B.y;
}
map<node, int> mp;
int main() {
    int n;
    scanf("%d", &n);
    for (int i = 0; i < n; ++ i) {
	scanf("%d%d", &p[i].x, &p[i].y);
    }
    int ans = 0;
    for (int i = 0; i < n; ++ i) {
	for (int j = i + 1; j < n; ++ j) {
	    int tx = p[i].x - p[j].x;
	    int ty = p[i].y - p[j].y;
	    if (tx < 0) {
		tx = -tx;
		ty = -ty;
	    }
	    else if (tx == 0) {
		ty = abs(ty);
	    }
	    mp[node(tx, ty)]++;
	}
    }
    for (map<node, int> :: iterator iter = mp.begin(); iter != mp.end(); ++ iter) {
	ans += iter->second * (iter->second - 1) / 2;
	//printf("%d %d %d\n", iter->first.x, iter->first.y, ans);
    }
    printf("%d\n", ans / 2);
    return 0;
}
