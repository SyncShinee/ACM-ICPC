#include <iostream>
#include <cstdio>
#include <cstring>

using namespace std;

const int maxn = 2000 + 10;
int f[maxn];

int main() {
    f[0] = 0;
    f[1] = 1;
    f[2] = 1;
    f[3] = 1;
    for(int i = 4; i <= 1100; i++) { 
	f[i] = 0;
	if(f[i - 2] == 0)
	    f[i] = 1;
	for(int j = 0; j + 3 <= i; j++) {
	    int a = j, b = i - 3 - a;
	    if(f[a] == f[b]) {
		f[i] = 1;
		break;
	    }
	}
    }
    for(int i = 0; i <= 1100;i++) {
	if(f[i] == 0)
	    printf("%d  -- --  %d\n", i, f[i]);
    }
    return 0;
}
