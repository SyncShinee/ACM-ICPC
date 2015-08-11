#include <cstdio>
#include <algorithm>
#include <cstring>
#include <queue>
#include <stack>
#include <vector>
using namespace std;
char s[1024];
int a[1024];
bool field[16][16];
bool flag[16];
struct node {
	int x, y, tp, kind;
};
bool check1(node p) {
	int x = p.x, y = p.y;
	if (p.kind == 0) {
		return !field[x][y] && !field[x][y + 1] && !field[x][y + 2] && !field[x][y + 3];
	}
	else {
		return !field[x][y] && !field[x + 1][y] && !field[x + 2][y] && !field[x + 3][y];
	}
}
bool check2(node p) {
	int x = p.x, y = p.y;
	if (p.kind == 0) {
		return !field[x][y] && !field[x + 1][y] && !field[x + 2][y] && !field[x][y + 1];
	}
	if (p.kind == 1) {
		return !field[x][y] && !field[x + 1][y + 2] && !field[x][y + 1] && !field[x][y + 2];
	}
	if (p.kind == 2) {
		return !field[x][y + 1] && !field[x + 1][y + 1] && !field[x + 2][y] && !field[x + 2][y + 1];
	}
	return !field[x][y] && !field[x+ 1][y] && !field[x + 1][y + 1]  && !field[x + 1][y + 2];
}
bool check(node p) {
	int x = p.x, y = p.y;
	if (p.tp == 0) {
		return !field[x][y] && !field[x + 1][y] && !field[x][y + 1] && !field[x + 1][y + 1];
	}
	if (p.tp == 1) {
		return check1(p);
	}
	return check2(p);
}

bool can_move(node p, char ch) {
	if (ch == 'p')
		return false;
	if (ch == 'a') {
		node tmp = p;
		tmp.x = p.x - 1, tmp.y = p.y;
		return check(tmp);
	}
	if (ch == 'd') {
		node tmp = p;
		tmp.x = p.x + 1, tmp.y = p.y;
		return check(tmp);
	}
	if (ch == 's') {
		node tmp = p;
		tmp.x = p.x, tmp.y = p.y - 1;
		return check(tmp);
	}
	if (ch == 'w') {
		node tmp = p;
		if (tmp.tp == 1) {
			tmp.kind ^= 1;
		}
		else if (tmp.tp == 2){
			tmp.kind = (tmp.kind + 1) & 3;
		}
		return check(tmp);
	}
}
node move(node p, char ch) {
	if (ch == 'p') {
		return p;
	}
	if (ch == 'a') {
		node tmp = p;
		tmp.x = p.x - 1, tmp.y = p.y;
		return tmp;
	}
	if (ch == 'd') {
		node tmp = p;
		tmp.x = p.x + 1, tmp.y = p.y;
		return tmp;
	}
	if (ch == 's') {
		node tmp = p;
		tmp.x = p.x, tmp.y = p.y - 1;
		return tmp;
	}
	if (ch == 'w') {
		node tmp = p;
		if (tmp.tp == 1) {
			tmp.kind ^= 1;
		}
		else if (tmp.tp == 2){
			tmp.kind = (tmp.kind + 1) & 3;
		}
		return tmp;
	}
}
bool can_xiao(int x) {
	for (int i = 1; i <= 9; ++i) {
		if (!field[i][x])
			return false;
	}
	return true;
}
void xiao() {
	int now1 = 1;
	for (int i = 1; i < 16; ++i) {
		if (flag[i]) {
			flag[i] = false;
			continue;
		}
		if (now1 < i) {
			for (int j = 1; j <= 9; ++j) {
				field[j][now1] = field[j][i];
			}
		}
		now1++;
	}
	for (int i = now1; i < 16; ++i) {
		for (int j = 1; j <= 9; ++j)
			field[i][j] = false;
	}
}
void label1(node p) {
	int x = p.x, y = p.y;
	if (p.kind == 0) {
		field[x][y] = field[x][y + 1] = field[x][y + 2] = field[x][y + 3] = true;
	}
	else {
		field[x][y] = field[x + 1][y] = field[x + 2][y] = field[x + 3][y] = true;
	}
}
void label2(node p) {
	int x = p.x, y = p.y;
	if (p.kind == 0) {
		field[x][y] = field[x + 1][y] = field[x + 2][y] = field[x][y + 1] = true;
	}
	else if (p.kind == 1) {
		field[x][y] = field[x + 1][y + 2] = field[x][y + 1] = field[x][y + 2] = true;
	}
	else if (p.kind == 2) {
		field[x][y + 1] = field[x + 1][y + 1] = field[x + 2][y] = field[x + 2][y + 1] = true;
	}
	else field[x][y] = field[x+ 1][y] = field[x + 1][y + 1]  = field[x + 1][y + 2] = true;
}
void label(node p) {
	int x = p.x, y = p.y;
	if (p.tp == 0) {
		field[x][y] = field[x + 1][y] = field[x][y + 1] = field[x + 1][y + 1] = true;
		return;
	}
	if (p.tp == 1) {
		label1(p);
		return;
	}
	label2(p);
}
int main() {
	freopen("in.txt", "r", stdin);
	freopen("out.txt", "w", stdout);
	int T, n, tmp;
	node p;
	scanf("%d", &T);
	for (int cas = 1; cas <= T; ++ cas) {
		memset(field, 0, sizeof field);
		for (int i = 0; i <= 10; ++i)
			field[i][0] = true;
		for (int i = 0; i < 16; ++i)
			field[0][i] = true;
		for (int i = 0; i < 16; ++i)
			field[10][i] = true;
		scanf("%d", &n);
		scanf("%s", s);
		int ans = 0;
		int len = strlen(s), pos = 0;
		for (int i = 1; i <= n; ++i) {
			scanf("%d", &tmp);
			p.x = 4;
			p.y = 9;
			p.tp = tmp;
			p.kind = 0;
			while (can_move(p, 's')) {
				printf("%c---%d\n", s[pos], can_move(p, s[pos]));
				if (pos < len && can_move(p, s[pos])) {
					p = move(p, s[pos]);
				}
				if (pos < len) pos++;
				if (can_move(p, 's')) {
					p = move(p, 's');
				}
				printf("p.x = %d p.y = %d p.tp = %d, p.kind = %d\n", p.x, p.y, p.tp, p.kind);
			}
			label(p);
			for (int j = 1; j <= 12; ++j) {
				if (can_xiao(j)) {
					ans ++;
					flag[j] = true;
				}
			}
			xiao();
			printf("%d---%d\n",i, ans);
			for (int k = 15; k > 0; --k) {
				for (int j = 1; j <= 9; ++j)
					printf("%d", field[j][k]);
				printf("\n");
			}
		}
		printf("%d\n", ans);
	}
	return 0;
}