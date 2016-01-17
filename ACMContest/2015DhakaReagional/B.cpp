#include <iostream>
#include <cstdio>
#include <cstring>
#include <string>

using namespace std;

string m[20] = {"JAN", "FEB", "MAR", "APR", "MAY", "JUN", "JUL", "AUG", "SEP", "OCT", "NOV", "DEC"};
int num[20] = {31, 28, 31, 30, 31, 30, 31, 31, 30,31, 30, 31};
string d[20] = {"MON", "TUE", "WED", "THU", "FRI", "SAT", "SUN"};

int main() {
    freopen("b.txt", "r", stdin);
    string a, b;
    int n;
    scanf("%d", &n);
    while(n--) {
        cin >> a >> b;
        int month;
        for(int i = 0; i < 12; i++) {
            if(m[i] == a)
                month = i;
        }
        int tot = num[month];
        int ans = 0, now;
        for(int i = 0; i < 7; i++) {
            if(b == d[i]) {
                now = i;
            }
        }
        for(int i = 0; i < tot; i++) {
            if(now == 4 || now == 5)
                ans++;
            now++;
            now %= 7;
        }
        cout << ans << endl;
    }
    return 0;
}
