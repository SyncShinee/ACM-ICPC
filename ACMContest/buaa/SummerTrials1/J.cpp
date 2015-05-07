#include <cstdio>
#include <algorithm>
using namespace std;
int n, p, k;
struct node {
	int idx, grey, unfun;
}a[100010];
bool b[100010];
bool cmp1(node x, node y) {
	if (x.unfun > y.unfun || (x.unfun == y.unfun && x.grey < y.grey))
		return true;
	return false;
}
bool cmp2(node x, node y) {
	if (x.grey > y.grey || (x.grey == y.grey && x.unfun > y.unfun))
		return true;
	return false;
}
bool cmp3(node x, node y) {
	if (x.unfun > y.unfun || (x.unfun == y.unfun && x.grey < y.grey))
		return true;
	return false;
}
int main() {
	int mn, num, mk;
	scanf("%d%d%d", &n, &p, &k);
	for (int i = 0; i < n; ++i) {
		scanf("%d%d", &a[i].grey, &a[i].unfun);
		a[i].idx = i+1;
	}
	sort(a, a+n, cmp1);
	sort(a, a+n-p+k, cmp2);
	sort(a+k, a+n, cmp3);
	mn = 2000000000;
	mk = 0;
	num = k;
	for (int i = 0; i < k; ++i) {
		if (i != 0)
			printf(" ");
		printf("%d", a[i].idx);
		if (a[i].unfun < mn || (a[i].unfun == mn && a[i].grey > mk)) {
			mn = a[i].unfun;
			mk = a[i].grey;
		}
	}
	if (num == p)
		return 0;
	for (int i = k; i < n; ++i) {
		if (a[i].unfun < mn || (a[i].unfun == mn && a[i].grey >= mk)) {
			printf(" %d", a[i].idx);
			num++;
			if (num == p)
				break;
		}
	}
	return 0;
}