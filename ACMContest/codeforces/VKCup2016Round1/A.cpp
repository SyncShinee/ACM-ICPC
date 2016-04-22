#include <cstdio>
#include <algorithm>
#include <set>
using namespace std;
const int N = 150010;
bool ap[N];
struct node {
    int id, val;
    node (int _i, int _v) : id(_i), val(_v) {}
};
bool operator < (const node &A, const node &B) {
    return A.val > B.val;
}
set<node> st;
int t[N];
int n, k, q;
bool find(int idx) {
    int i;
    set<node>::iterator iter;
    for (iter = st.begin(), i = 0; i < k; ++ i, iter++) {
	if ((*iter).id == idx) return true;
    }
    return false;
}
int main() {
    int type, idx;
    scanf("%d%d%d", &n, &k, &q);
    for (int i = 1; i <= n; ++ i) {
	scanf("%d", &t[i]);
    }
    while (q--) {
	scanf("%d%d", &type, &idx);
	if (type == 1) {
	    ap[idx] = true;
	    st.insert(node(idx, t[idx]));
	}
	else {
	    if (!ap[idx] || !find(idx)) {
		puts("NO");
	    }
	    else {
		puts("YES");
	    }
	}
    }
    return 0;
}
