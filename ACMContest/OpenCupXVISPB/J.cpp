#include <bits/stdc++.h>

using namespace std;
char s[10][10];
void print(){
    for (int i = 0; i < 3; ++ i){
	printf("%s\n", s[i]);
	fflush(stdout);
    }
}
void read(){
    for (int i = 0; i < 3; ++ i) scanf("%s", s[i]);
}
int win(){
    for (int i = 0; i < 3; ++ i){
	int num1 = 0, num2 = 0;
	int dx, dy;
	for (int j = 0; j < 3; ++ j){
	    if (s[i][j] == 'o') num1 ++;
	    if (s[i][j] == 'x') num2 ++;
	    if (s[i][j] == '.') dx = i, dy = j;
	}
	if (num1 == 0 && num2 == 2){
	    s[dx][dy] = 'x';
	    print();
	    return 1;
	}
    }
    //  printf("1\n");
    for (int j = 0; j < 3; ++ j){
	int num1 = 0, num2 = 0;
	int dx = 0, dy = 0;
	for (int i = 0; i < 3; ++ i){
	    if (s[i][j] == 'o') num1 ++;
	    if (s[i][j] == 'x') num2 ++;
	    if (s[i][j] == '.') dx = i, dy = j;
	}
	if (num1 == 0 && num2 == 2){
	    s[dx][dy] = 'x';
	    print();
	    return 1;
	}
    }
    // printf("2\n");
    int dx, dy;
    int num1 = 0, num2 = 0;
    for (int i = 0; i < 3; ++ i){
	if (s[i][i] == 'o') num1 ++;
	if (s[i][i] == 'x') num2 ++;
	if (s[i][i] == '.') dx = i, dy = i;
    }
    if (num1 == 0 && num2 == 2){
	s[dx][dy] = 'x';
	print();
	return 1;
    }
    //  printf("3\n");
    num1 = 0, num2 = 0;
    for (int i = 0; i < 3; ++ i){
	if (s[i][2 - i] == 'o') num1 ++;
	if (s[i][2 - i] == 'x') num2 ++;
	if (s[i][2 - i] == '.') dx = i, dy = 2 - i;
    }
    // printf("%d %d\n", num1, num2);
    if (num1 == 0 && num2 == 2){
	s[dx][dy] = 'x';
	print();
	return 1;
    }
    return 0;
}
void solve(){
    read();
    int dx, dy, px, py;
    for (int i = 0; i < 3; ++ i){
	for (int j = 0; j < 3; ++ j){
	    if (s[i][j] == 'o'){
		px = i; py = j;
		break;
	    }
	}
    }
    dx = px;
    dy = 0;
    if (dy == py) dy = 2;
    if (px == 1) dx = 0, dy = 0;
    s[dx][dy] = 'x';
    print();
    read();
    if (win()) return;
    //puts("here");
    for (int i = 0; i < 3; ++ i){
	for (int j = 0; j < 3; ++ j){
	    if (i != 1 && j != 1) continue;
	    if (i == 1 && j == 1) continue;
	    if (s[i][j] != '.') continue;
	    int num1 = 0, num2 = 0;
	    for (int k = 0; k < 3; ++ k){
		if (i == 1){
		    if (s[k][j] == 'o') num1 ++;
		    if (s[k][j] == 'x') num2 ++;
		}else{
		    if (s[i][k] == 'o') num1 ++;
		    if (s[i][k] == 'x') num2 ++;
		}
	    }
	    if (num1 == 0 && num2 == 1){
		dx = i, dy = j;
	    }
	}
    }
    s[dx][dy] = 'x';
    print();
    read();
    win();
}
int main(){
    //  freopen("in.txt", "r", stdin);
    while (1){
	int flag = 1;
        read();
	for (int i = 0; i < 3; ++ i){
	    for (int j = 0; j < 3; ++ j){
		if (s[i][j] != 'x') flag = 0;
	    }
	}
	if (flag) break;
	s[1][1] = 'x';
	print();
        solve();
    }
    return 0;
}
