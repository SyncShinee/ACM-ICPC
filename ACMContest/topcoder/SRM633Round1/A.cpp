#include <cstdio>
#include <string>
#include <vector>
#include <cstring>
using namespace std;
class ChessFloor {
	public :
	int minimumChanges(vector <string> floor) {
		bool vis[32];
		int len = floor.size(), ans, num;
		memset(vis, 0, sizeof vis);
		for (int i = 0; i < len; ++i) {
			for (int j = 0; j < len; ++j) {
				vis[floor[i][j] - 'a'] = true;
			}
		}
		ans = 1000000;
		num = 0;
		for (int i = 0; i <= 26; ++i) {
			if (vis[i])
				num++;
		}
		if (num == 1)
			return len * len / 2;
		for (int i = 0; i <= 26; ++i) {
			if (vis[i]) {
				for (int j = 0; j <= 26; ++j) {
					if (i == j)
						continue;
					if (vis[j]) {
						int tmp = 0;
						for (int t = 0; t < len; ++t)
							for (int k = 0; k < len; ++k)
								if (((k + t) & 1) && floor[t][k] != i + 'a')
									tmp++;
								else if (((k + t) & 1) == 0 && floor[t][k] != j + 'a')
									tmp++;
						ans = min(ans, tmp);
					}
				}
			}
		}
		return ans;
	}
};
/*int main() {
	ChessFloor e;
}*/