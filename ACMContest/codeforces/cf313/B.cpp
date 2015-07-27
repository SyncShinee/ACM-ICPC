/*
#include <cstdio>
#include <cstring>
using namespace std;
char s1[200010], s2[200010];
bool judge(int l1, int r1, int l2, int r2) {
	if (r1 - l1 != r2 - l2) {
		return false;
	}
	bool flag = true;
	for (int i = 0; i < r1 - l1; ++i) {
		if (s1[l1 + i] != s2[l2 + i]) {
			flag = false;
			break;
		}
	}
	if (flag)
		return true;
	if ((r1 - l1) & 1)
		return false;
	int mid1 = (l1 + r1) >> 1, mid2 = (l2 + r2) >> 1;
	if (judge(l1, mid1, l2, mid2)) {
		if (judge(mid1, r1, mid2, r2))
			return true;
		else
			return false;
	}
	else {
		return judge(l1, mid1, mid2, r2) && judge(mid1, r1, l2, mid2);
	}
}
int main() {
	scanf("%s%s", s1, s2);
	int len1 = strlen(s1), len2 = strlen(s2);
	if (judge(0, len1, 0, len2)) {
		printf("YES\n");
	}
	else {
		printf("NO\n");
	}
	return 0;
} 
*/

#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
char s1[200010], s2[200010], s3[200010], s4[200010];
void min_prs(char s[], int l, int r) {
	if ((r - l) & 1) {
		return;
	}
	int mid = (l + r) >> 1;
	min_prs(s, l, mid);
	min_prs(s, mid, r);
	int flag = 0;
	for (int i = l, j = mid; i < mid; ++i, ++j) {
		if (s[i] > s[j]) {
			flag = 1;
			break;
		}
		else if (s[i] < s[j]) {
			break;
		}
	}
	if (flag) {
		for (int i = l, j = mid; i < mid; ++i, ++j) {
			s[i] ^= s[j] ^= s[i] ^= s[j];
		}
	}
}

int main() {
	scanf("%s%s", s1, s2);
	int len1 = strlen(s1), len2 = strlen(s2);
	min_prs(s1, 0, len1);
	min_prs(s2, 0, len2);
	if (strcmp(s1, s2) == 0) {
		printf("YES\n");
	}
	else {
		printf("NO\n");
	}
	return 0;
}