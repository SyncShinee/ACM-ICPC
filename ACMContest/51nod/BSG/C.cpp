#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <set>
#include <map>
#include <cmath>
using namespace std;
double pi = acos(-1.0);
int main() {
    double S;
    scanf("%lf", &S);
    double a = - 2. / 9. * pi * S;
    double b = 1. / 9. * S * S;
    double x = S / 4. / pi;
    printf("%f\n", sqrt(a * x * x + b * x));
    return 0;
}
