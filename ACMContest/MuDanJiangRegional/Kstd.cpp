#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <queue>
#include <map>
#include <set>
using namespace std;
#define INF 1000000000
//pedef __int64 LL;
#define N 1111
int n;
string str;
int main()
{
	freopen("11Kin.txt", "r", stdin);
	freopen("stdKout.txt", "w", stdout);
	int t;
	scanf("%d", &t);
	while(t--) {
		cin>>str;
		int la , lb;
		la = lb = 0;
		for(int i = 0; i < str.length(); i ++) {
			if(str[i] == '*') lb ++;
			else la ++;
		}
		if(la == str.length()) {
			puts("0"); continue; //tice this ..
		}
		int ans = 0;
		if(lb >= la) {
			ans += lb - la + 1;
			for(int i = 0; i < lb - la + 1; i++) str = "1"+str;
		}
		int aa = 0;
		int flag = 0;
		for(int i = 0; i < str.length(); i++) {
			if(str[i] != '*') {
				aa ++;
			}
			else {
				flag = 1;
				if(aa >= 2) {
					aa--;
				}
				else {
					for(int j = str.length()-1; j>= 0; j--) {
						if(str[j] != '*') {
							str[j] = '*'; str[i] = '1';
							break;
						}
					}
					aa ++;
					ans ++;
				}
			}
		}
		int len = str.length();
		if(str[len-1] != '*')  ans ++;
		printf("%d\n", ans);
	}
	return 0;
}
