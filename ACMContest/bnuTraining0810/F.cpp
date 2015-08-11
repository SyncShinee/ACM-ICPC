#include <cstdio>
#include <algorithm>
#include <cstring>
#include <queue>
using namespace std;
int q[1000010], n;
deque<int> que;
int main() {
	//freopen("in.txt", "r", stdin);
	//freopen("out.txt", "w", stdout);
	deque<int>::iterator pos; 
	deque <int> :: reverse_iterator pos1;
	scanf("%d", &n);
	int sz = 0, num = 0, flag = 0;
	for (int i = 0; i < n; ++i) {
		scanf("%d", &q[i]);
		if (q[i] == -1)
			sz++;
	}
	for (int i = 0; i < n; ++i) {
		if (q[i] > 0) {
			que.push_back(q[i]);
			num++;
			if (num > sz) {
				num--;
				flag = 1;
				que.pop_front();
			}
			//printf("13246\n");
		}
		else if (q[i] == -1) {
			//printf("12346----%d\n", num);
			printf("%d\n", que.back());
			que.pop_back();
			num--;
			//printf("132456---%d\n", num);
		}
		else {
			if (flag == 1)
				continue;
			if (num * 2 <= sz) {
				int tmp = 0;
				for (pos = que.begin(); tmp < num && pos != que.end(); ++ pos) {
					que.push_back(*pos);
					tmp++;
				}
				num *= 2;
			}
			else if (num < sz) {
				flag = 1;
				for (pos1 = que.rbegin(); num < sz && pos1 != que.rend(); ++ pos1) {
					//printf("----%d\n", *pos1);
					num ++;
					que.push_front(*pos1);
				}
			}
		}
	}
	return 0;
}