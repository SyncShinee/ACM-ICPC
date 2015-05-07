#include <cstdio>
#include <cstring>
#include <map>
#include <queue>
using namespace std;
struct node {
	int val, tm;
	friend bool operator < (node x, node y) {
		return x.val < y.val;
	}
}tnode;
map <int, int> sum, time;
priority_queue <node> heap;
int a[100010], n, k, tt;
int main() {
	scanf("%d%d", &n, &k);
	for (int i = 1; i <= n; ++i) {
		scanf("%d", &a[i]);
		time[i] = 0;
	}
	for (int i = 1; i <= k; ++i) {
		sum[a[i]]++;
		tt = ++time[a[i]];
		if (sum[a[i]] == 1) {
			tnode.val = a[i];
			tnode.tm = time[a[i]];
			heap.push(tnode);
		}
	}
	tnode = heap.top();
	while (!heap.empty() && tnode.tm != time[tnode.val]) {
		heap.pop();
		if (!heap.empty())
			tnode = heap.top();
	}
	if (heap.empty()) {
		printf("Nothing\n");
	}
	else {
		printf("%d\n", tnode.val);
	}
	for (int i = k+1; i <= n; ++i) {
		if (a[i] != a[i-k]) {
			sum[a[i]]++;
			tt = ++time[a[i]];
			if (sum[a[i]] == 1) {
				tnode.val = a[i];
				tnode.tm = tt;
				heap.push(tnode);
			}
			sum[a[i-k]]--;
			tt = --time[a[i-k]];
			if (sum[a[i-k]] == 1) {
				tnode.val = a[i-k];
				tnode.tm = tt;
				heap.push(tnode);
			}
		}
		if (heap.empty()) {
			printf("Nothing\n");
		}
		else {
			tnode = heap.top();
			while (!heap.empty() && tnode.tm != time[tnode.val]) {
				heap.pop();
				if (!heap.empty())
					tnode = heap.top();
			}
			if (heap.empty()) {
				printf("Nothing\n");
			}
			else {
				printf("%d\n", tnode.val);
			}
		}
	}
	return 0;
}