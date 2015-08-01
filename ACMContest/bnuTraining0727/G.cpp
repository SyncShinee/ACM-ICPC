#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
char start_mon[16], end_mon[16];
int start_d, start_y, end_d, end_y, start_m, end_m;
char mon[16][16] = {"123", "January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December"};
int main() {
	int T;
	scanf("%d", &T);
	for (int cas = 1; cas <= T; ++cas) {
		scanf("%s%d,%d", start_mon, &start_d, &start_y);
		scanf("%s%d,%d", end_mon, &end_d, &end_y);
		for (int j = 1; j <= 12; ++j) {
			if (strcmp(mon[j], start_mon) == 0) {
				start_m = j;
				break;
			}
		} 
		for (int j = 1; j <= 12; ++j) {
			if (strcmp(mon[j], end_mon) == 0) {
				end_m = j;
				break;
			}
		} 
		if (start_y % 400 == 0 || start_y % 100 != 0 && start_y % 4 == 0) {
			if (start_m > 2) {
				start_y ++;
			}
		}
		if (end_y % 400 == 0 || end_y % 100 != 0 && end_y % 4 == 0) {
			if (end_m < 2 || end_m == 2 && end_d < 29) {
				end_y--;
			}
		}
			
		if (end_y < start_y) {
			printf("Case %d: 0\n", cas);
		}
		else {
			if (start_y > 0) {
				start_y--;
			}
			int ans = 0;
			ans = end_y / 4 - end_y / 100 + end_y / 400;
			ans -= start_y / 4 - start_y / 100 + start_y / 400;
			printf("Case %d: %d\n", cas, ans);
		}
	}
}