#include <bits/stdc++.h>
using namespace std;
char s[10240];
char a[10240], b[10240], c[10240];
int la, lb, lc;
int main() {
    scanf("%s", s);
    int len = strlen(s);
    int sum = 0;
    la = lb = lc = 0;
    int na = 0, nb = 0, nc = 0;
    memset(a, 0, sizeof a);
    memset(b, 0, sizeof b);
    memset(c, 0, sizeof c);
    for (int i = 0; i < len; ++ i) {
        if ((s[i] - '0') % 3) {
            sum += s[i] - '0';
        }
    }
    if (sum % 3) {
        puts("-1");
    } else {
        sum /= 3;
        for (int i = 0; i < len; ++ i) {
            int tmp = s[i] - '0';
            if (tmp % 3) {
                if (na + tmp <= sum) {
                    a[la ++] = tmp + '0';
                    b[lb ++] = '0';
                    c[lc ++] = '0';
                    na += tmp;
                } else if (na < sum) {
                    a[la ++] = sum - na + '0';
                    b[lb ++] = tmp - sum + na + '0';
                    c[lc ++] = '0';
                    nb += tmp - sum + na;
                    na = sum;
                } else if (nb + tmp <= sum) {
                    a[la ++] = '0';
                    b[lb ++] = tmp + '0';
                    c[lc ++] = '0';
                    nb += tmp;
                } else if (nb < sum) {
                    a[la ++] = '0';
                    b[lb ++] = sum - nb + '0';
                    c[lc ++] = tmp - sum + nb + '0';
                    nc += tmp - sum + nb;
                    nb = sum;
                } else {
                    a[la ++] = '0';
                    b[lb ++] = '0';
                    c[lc ++] = tmp + '0';
                    nc += tmp;
                }
            } else {
                a[la ++] = tmp / 3 + '0';
                b[lb ++] = tmp / 3 + '0';
                c[lc ++] = tmp / 3 + '0';
            }
        }
        int ta = 0, tb = 0, tc = 0;
        while (a[ta] == '0') ta ++;
        while (b[tb] == '0') tb ++;
        while (c[tc] == '0') tc ++;
        if (a[ta] == '\0') {
            printf("0 ");
        } else {
            printf("%s ", a + ta);
        }
        if (b[tb] == '\0') {
            printf("0 ");
        } else {
            printf("%s ", b + tb);
        }
        if (c[tc] == '\0') {
            printf("0\n");
        } else {
            printf("%s\n", c + tc);
        }
    }
    return 0;
}
