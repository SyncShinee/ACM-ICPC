#include <cstdio>
#include <list>
#include <algorithm>
#include <cstring>
#define INF 2e9
using namespace std;
struct node {
	int val, sum, idx;
}tnode;
int ans[1000010];
list <node> chain;
list <node> :: iterator iter, tmp;
char s[2];
int main() {
	int Q, x;
	while (~scanf("%d", &Q)) {
		memset(ans, 0, sizeof ans);
		ans[0] = - INF;
		chain.clear();
		iter = chain.end();
		while (Q--) {
			scanf("%s", s);
			if (s[0] == 'I') {
				scanf("%d", &x);
				tnode.val = x;
				if (iter == chain.begin()) {
					tnode.idx = 1;
					tnode.sum = x;
				}
				else {
					tmp = iter;
					tmp--;
					tnode.idx = tmp->idx + 1;
					tnode.sum = tmp->sum + x;
				}
				chain.insert(iter, tnode);
				ans[tnode.idx] = max(tnode.sum, ans[tnode.idx-1]);
			}
			else if (s[0] == 'D') {
				tmp = iter;
				tmp--;
				iter = chain.erase(tmp);
			}
			else if (s[0] == 'L') {
				if (iter != chain.begin())
					iter--;
			}
			else if (s[0] == 'R') {
				if (iter != chain.end()) {
					if (iter == chain.begin()) {
						iter->idx = 1;
						iter->sum = iter->val;
						ans[1] = iter->sum;
					}
					else {
						tmp = iter;
						tmp--;
						iter->idx = tmp->idx + 1;
						iter->sum = tmp->sum + iter->val;
						ans[iter->idx] = max(iter->sum, ans[tmp->idx]);
					}
					iter++;
				}
			}
			else if (s[0] == 'Q') {
				scanf("%d", &x);
				printf("%d\n", ans[x]);
			}

		}
	}
	return 0;
}