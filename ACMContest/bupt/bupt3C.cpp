/**
 * hash版
 */
#include <cstdio>
#include <cstring>
#include <vector>
#define M 100007
using namespace std;
int elfhash(char *str) {
	int len = strlen(str), g, sum=0;
	for(int i = 0; i < len; ++i) {
		sum = (sum<<4) + str[i];
		g = sum & 0xf0000000;
		if (g) 
			sum ^= g>>24;
		sum &= ~g;
	}
	return sum % M;
}
struct node{
	int num;
	char sh[128];
}k;
vector<node> a[100010];
char s[128];
int main() {
	int t, i;
	while (~scanf("%s", s)) {
		t = elfhash(s);
		for (i = 0; i < a[t].size(); ++i){
			if (strcmp(a[t][i].sh, s) == 0)
				break;
		}
		if (i == a[t].size()) {
			k.num = 1;
			strcpy(k.sh, s);
			a[t].push_back(k);
			printf("1\n");
		}
		else {
			a[t][i].num++;
			printf("%d\n", a[t][i].num);
		}
	}
	return 0;
}
/**
 * map版
 */
#include <cstdio>
#include <cstring>
#include <map>
using namespace std;
struct node {
	char s[128];
	friend bool operator <(node a, node b) {
		if (strcmp(a.s, b.s) < 0)
			return true;
		return false;
	}
}e;
map<node, int> mp;
int main() {
	char s[128];
	while(~scanf("%s", s)) {
		strcpy(e.s, s);
		mp[e]++;
		printf("%d\n", mp[e]);
	}
	return 0;
}