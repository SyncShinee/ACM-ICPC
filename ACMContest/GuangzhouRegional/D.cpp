#include <cstdio>
#include <iostream>
#include <vector>
#include <cstring>
#include <queue>
#include <cmath>
#include <algorithm>

using namespace std;

const double EPS = 1e-8;
const int maxn = 500+19;

struct  Point
{
	double x, y;
	Point(double _x = 0, double _y = 0)
	{
		x = _x;
		y = _y;
	}
	double dianji(Point a)
	{
		double ans;
		ans = x*a.x+y*a.y;
		return ans;
	}
	double chaji(Point a)
	{
		return x*a.y - y*a.x;
	}
	double dist(Point a)
	{
		return (x-a.x)*(x-a.x)+(y-a.y)*(y-a.y);
	}
	double mo()
	{
		return sqrt(x*x + y*y);
	}
};
struct  erci
{
	double a, b, c;
	erci(double _a = 0, double _b = 0, double _c = 0)
	{
		a = _a;
		b = _b;
		c = _c;
	}
	void getT(int &flag, double &t1, double &t2)
	{
		double tmp = b*b-4*c*a;
		if(tmp+EPS>0)
		{
			t1 = (-b+sqrt(b*b-4*c*a+EPS))/(2*a);
			t2 = (-b-sqrt(b*b-4*c*a+EPS))/(2*a);
			if(fabs(t1-t2) < EPS)
			{
				flag = 1;
			}
			else
			{
				flag = 2;
			}
		}
		else
		{
			flag = 0;
		}
	}
};
Point d[maxn], o;
double r, k;
int n;

void getD(Point a, Point b, int &flag, Point &ans1, Point &ans2)
{
	double l = a.dist(b);
	double si = (b.y-a.y)/l, co = (b.x-a.x)/l;
	erci t(1, 2*co*(a.x)+2*si*(a.y), (a.x)*(a.x) + (a.y)*(a.y) - r*r);
	int tag;
	double t1, t2;
	t.getT(tag, t1, t2);
	if(tag==0)
	{
		flag = 0;
	}
	else if(tag == 1)
	{
		ans1.x = a.x+co*t1;
		ans1.y = a.y+si*t1;
		if(ans1.x >= min(a.x, b.x)-EPS && ans1.x <= max(a.x, b.x)+EPS)
		{
			flag = 1;
		}
		else
		{
			flag = 0;
		}
	}
	else
	{
		flag = 0;
		ans1.x = a.x+co*t1;
		ans1.y = a.y+si*t1;
		if(ans1.x >= min(a.x, b.x)-EPS && ans1.x <= max(a.x, b.x)+EPS)
		{
			flag = 1;
			ans2.x = a.x+co*t2;
			ans2.y = a.y+si*t2;
			if(ans2.x >= min(a.x, b.x)-EPS && ans2.x <= max(a.x, b.x)+EPS)
			{	
				flag = 2;
			}
		}
		else
		{
			ans1.x = a.x+co*t2;
			ans1.y = a.y+si*t2;
			if(ans1.x >= min(a.x, b.x)-EPS && ans1.x <= max(a.x, b.x)+EPS)
			{
				flag = 1;
			}
			else
			{
				flag = 0;
			}		
		}
	}
	if(flag==2&&fabs(ans1.x-ans2.x)<EPS)
		flag = 1;
	if(flag==1)
	{
		printf(" flag is  1 %f  %f \n", ans1.x, ans1.y);
	}
	else if(flag == 2)
	{
		printf(" flag is  2 %f  %f \n", ans1.x, ans1.y);
		printf(" flag is  2 %f  %f \n", ans2.x, ans2.y);	
	}
	else
	{
		printf("flag is 00000\n");
	}
}
double getS(Point a, Point b)
{
	double t = a.dianji(b);
	t = t/(a.mo()*b.mo());
	//printf("tttt is %f\n", t);
	t = acos(t);
	double ans = 0.5*t*r*r;
	//printf("******--------%lf--- %lf %lf %lf %lf\n", ans, a.x, a.y, b.x, b.y);
	return ans;
}
double getS(Point a, Point b, Point c)
{
	double la, lb, lc;
	la = a.dist(b);
	lb = a.dist(c);
	lc = b.dist(c);
	double p = (la+lb+lc)/2;
	double ans = p*(p-la)*(p-lb)*(p-lc);
	ans += EPS;
	ans = sqrt(ans);
	//printf("asdfasdfsadf%f\n", ans);
	return ans;
}
double gao(Point a, Point b)
{
	//printf("%lf  %lf   %lf  %lf\n", a.x, a.y, b.x, b.y);
	double tfu = a.chaji(b);
	//printf("ffffffffffffffff---    %f\n", tfu);
	int fu;
	if(tfu>EPS)
		fu = 1;
	else
		fu = -1;
	if(a.mo()<=r+EPS&&b.mo()<=r+EPS)
		return getS(Point(0,0), a, b)*fu;
	if(a.mo()>r+EPS&&b.mo()>r+EPS)
	{
		int flag;
		Point ansa, ansb;
		getD(a, b, flag, ansa, ansb);
		Point ata, atb, bta, btb;
		int ttag;
		getD(Point(0,0),a, ttag, ata, atb);
		if(ttag!=1)
		{
			while(1);
		}
		getD(Point(0,0),b, ttag, bta, btb);
		if(ttag!=1)
		{
			while(1);
		}
		//printf("BUGBUGBUGBUGBUGBUGBUGBUGBUGBUGBUG   %f  %f  %f  %f\n", ata.x, ata.y, bta.x, bta.y);
		if(flag==0 || flag == 1)
		{
			return getS(ata, bta)*fu;
		}
		else
		{
			//printf("BUGBUGBUGBUGBUGBUGBUGBUGBUGBUGBUG   %f  %f  %f  %f\n", ansa.x, ansa.y, ansb.x, ansb.y);
			double tmp1 = getS(ata, ansa)+getS(bta, ansb), tmp2 = getS(ata, ansb)+getS(bta, ansa);
			double ans;
			ans = min(tmp1, tmp2);
			ans += getS(Point(0, 0), ansa, ansb);
			return ans*fu;
		}
	}
	else
	{
		if(a.mo() < r+EPS)
		{
			swap(a, b);
		}
		int flag;
		Point ansa, ansb;
		getD(a, b, flag, ansa, ansb);
		if(flag != 1)
		{
			printf("asdfasdfdsafffffffffffffffffffff\n");
		}
		int flag2;
		Point ansa2, ansb2;
		getD(Point(0, 0), a, flag2, ansa2, ansb2);
		if(flag2 != 1)
		{
			printf("asdfasdfdsafffffffffffffffffffff\n");
		}
		return (getS(Point(0, 0), b, ansa)+getS(ansa, ansa2))*fu;
	}
}
Point _a, _b;
bool cmp(Point a, Point b)
{
	return a.chaji(b) > EPS;
}
void solve()
{
	k = k*k;
	double a = (1-k);
	double bx = 2*k*_a.x-2*_b.x;
	double by = 2*k*_a.y-2*_b.y;
	double c = _b.x*_b.x+_b.y*_b.y-k*_a.x*_a.x-k*_a.y*_a.y;
	o.x = bx/a/2*-1;
	o.y = by/a/2*-1;
	r = sqrt(-c+o.x*o.x+o.y*o.y+EPS);
	for(int i = 0;i<n;i++)
	{
		d[i].x -= o.x;
		d[i].y -= o.y;
	}
	o.x = 0;
	o.y = 0;
	sort(d, d+n, cmp);
	double ans = 0;
	for(int i = 0;i<=n-2;i++)
	{
		printf("i is %d--------------------%lf  %lf   %lf  %lf\n", i, d[i].x, d[i].y, d[i+1].x, d[i+1].y);
		ans += gao(d[i], d[i+1]);
		//printf("----%f\n", gao(d[i], d[i+1]));
	}
	ans += gao(d[n-1], d[0]);
	printf("%.10f\n", ans);
}
int main()
{
	freopen("Din.txt", "r", stdin);
	while(scanf("%d%lf", &n, &k) != EOF)
	{
		for(int i = 0;i<n;i++)
			scanf("%lf%lf", &d[i].x, &d[i].y);
		scanf("%lf%lf", &_a.x, &_a.y);
		scanf("%lf%lf", &_b.x, &_b.y);
		solve();
	}
	return 0;
}