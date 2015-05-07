#include <cstdio>
using namespace std;
int change[32][8];
char s[256];
bool judge(int x) {
	int tmp1 = 0;
	for (int i = 0; i < 7; ++i) {
		int sum = 0;
		for (int j = 0; j < 7; ++j) {
			if (x & (1 << change[i][j]))
				sum += (1<<j);
		}
		tmp1 |= (s[sum]-'0') << i;
	}
	int tmp2 = 0;
	int sum = 0;
	for (int j = 0; j < 7; ++j) {
		if (tmp1 & (1 << change[3][j]))
			sum += (1<<j);
	}
	if ((tmp1 & (1<<3)) ^ ((s[sum]-'0') << 3))
		return false;
	return true;
}
int main() {
	change[0][0] = 15; change[0][1] = 16; change[0][2] = 14; change[0][3] = 0; change[0][4] = 1; change[0][5] = 2; change[0][6] = 3;
	change[1][0] = 16; change[1][1] = 17; change[1][2] = 0; change[1][3] = 1; change[1][4] = 18; change[1][5] = 3; change[1][6] = 4;
	change[2][0] = 14; change[2][1] = 0; change[2][2] = 13; change[2][3] = 2; change[2][4] = 3; change[2][5] = 12; change[2][6] = 5;
	change[3][0] = 0;
	change[3][1] = 1;
	change[3][2] = 2;
	change[3][3] = 3;
	change[3][4] = 4;
	change[3][5] = 5;
	change[3][6] = 6;
	change[4][0] = 1;
	change[4][1] = 18;
	change[4][2] = 3;
	change[4][3] = 4;
	change[4][4] = 7;
	change[4][5] = 6;
	change[4][6] = 8;
	change[5][0] = 2;
	change[5][1] = 3;
	change[5][2] = 12;
	change[5][3] = 5;
	change[5][4] = 6;
	change[5][5] = 11;
	change[5][6] = 10;
	change[6][0] = 3;
	change[6][1] = 4;
	change[6][2] = 5;
	change[6][3] = 6;
	change[6][4] = 8;
	change[6][5] = 10;
	change[6][6] = 9;
	while (scanf("%s", s), s[0] != '#') {
		bool flag = true;
		int kkk = 1 << 19;
		for (int i = 0; i < kkk; ++i) {
			if (!judge(i)) {
				flag = false;
				break;
			}
		}
		if (flag)
			printf("yes\n");
		else
			printf("no\n");
	}
	return 0;
}