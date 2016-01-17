#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>

using namespace std;

const int maxn = 300 + 10;
const double eps = 1e-8;
const double PI = acos(-1.0);

int dcmp(double x)
{
    if(fabs(x)<eps)
        return 0;
    if(x > 0)
        return 1;
    return -1;
}

struct Point
{
    double x, y;
    Point(double _x = 0, double _y = 0)
    {
        x = _x;
        y = _y;
    }
    Point operator + (const Point &b) const
    {
        return Point(x + b.x, y + b.y);
    }
    Point operator -(const Point &b)const
    {
        return Point(x - b.x,y - b.y);
    }
//叉积
    double operator ^(const Point &b)const
    {
        return x*b.y - y*b.x;
    }
    int operator ==(const Point &b)const
    {
        if(dcmp(x-b.x)==0&&dcmp(y-b.y)==0)
            return 1;
        return 0;
    }
//点积
    double operator *(const Point &b)const
    {
        return x*b.x + y*b.y;
    }
    Point operator *(const double &b)const
    {
        return Point(x*b, y*b);
    }
    Point operator /(const double &b)const
    {
        return Point(x/b, y/b);
    }
    double mo()
    {
        double ans = 0;
        ans = sqrt(x*x+y*y);
        return ans;
    }
//变成长度是r的向量
    void change(double r)
    {
        double k = r/mo();
        x *= k;
        y *= k;
    }
};

double dist(Point a, Point b)
{
    return sqrt((a.x-b.x)*(a.x-b.x)+(a.y-b.y)*(a.y-b.y));
}
struct Line
{
    Point s,e;
    double k;
    Line() {}
    Line(Point _s,Point _e)
    {
        s = _s;
        e = _e;
        k = atan2(e.y - s.y,e.x - s.x);
    }
    Point operator &(const Line &b)const//用到半平面交的时候
    {
        Point res = s;
        double t = ((s - b.s)^(b.s - b.e))/((s - e)^(b.s - b.e));
        res.x += (e.x - s.x)*t;
        res.y += (e.y - s.y)*t;
        return res;
    }
};


//半平面交，直线的左边代表有效区域
bool HPIcmp(Line a,Line b)
{
    if(fabs(a.k - b.k) > eps)return a.k < b.k;
    return ((a.s - b.s)^(b.e - b.s)) < 0;
}
Line Q[maxn];
void HPI(Line line[], int n, Point res[], int &resn)
{
    int tot = n;
    sort(line,line+n,HPIcmp);
    tot = 1;
    for(int i = 1; i < n; i++)
        if(fabs(line[i].k - line[i-1].k) > eps)
            line[tot++] = line[i];
    int head = 0, tail = 1;
    Q[0] = line[0];
    Q[1] = line[1];
    resn = 0;
    for(int i = 2; i < tot; i++)
    {
        if(fabs((Q[tail].e-Q[tail].s)^(Q[tail-1].e-Q[tail-1].s)) < eps || fabs((Q[head].e-Q[head].s)^(Q[head+1].e-Q[head+1].s)) < eps)
            return;
        while(head < tail && (((Q[tail]&Q[tail-1]) - line[i].s)^(line[i].e-line[i].s)) > eps)
            tail--;
        while(head < tail && (((Q[head]&Q[head+1]) - line[i].s)^(line[i].e-line[i].s)) > eps)
            head++;
        Q[++tail] = line[i];
    }
    while(head < tail && (((Q[tail]&Q[tail-1]) - Q[head].s)^(Q[head].e-Q[head].s)) > eps)
        tail--;
    while(head < tail && (((Q[head]&Q[head-1]) - Q[tail].s)^(Q[tail].e-Q[tail].e)) > eps)
        head++;
    if(tail <= head + 1)return;
    for(int i = head; i < tail; i++)
        res[resn++] = Q[i]&Q[i+1];
    if(head < tail - 1)
        res[resn++] = Q[head]&Q[tail];
}

int n, ln, resn;
Point p[maxn], res[maxn], a[maxn];
Line l[maxn], nl[maxn];

Line move(Line a, double d)
{
  Point v, u;
  u = (a.e - a.s);
  v.x = u.y;
  v.y = -u.x;
  if(dcmp(u ^ v) < 0)
    {
      v.x = -v.x;
      v.y = -v.y;
    }
  double m = v.mo();
  v = v / m;
  v = v * d;
  Line li;
  li.s = a.s + v;
  li.e = a.e + v;
  return li;
}

int check(double r, Point p[])
{
  for(int i = 0; i < ln; i++)
    {
      nl[i] = move(l[i], r);
      printf("%.4f %.4f %.4f %.4f\n", nl[i].s.x, nl[i].s.y, nl[i].e.x, nl[i].e.y); 
    }
  HPI(nl, ln, res, resn);

  for(int i = 0; i < resn; i++)
    {
      printf("**** %.4f  %.4f\n", res[i].x, res[i].y);
    }
  int flag = 0;
  for(int i = 0; i < resn; i++)
    {
      for(int j = 0; j < resn; j++)
	{
	  if(j == i)
	    continue;
	  if(dcmp(dist(res[i], res[j]) - 2*r ) >= 0)
	    {
	      flag = 1;
	      p[0] = res[i];
	      p[1] = res[j];
	      break;
	    }
	}
      if(flag)
	break;
    }
  return flag;
}

void solve()
{
  double lR = 0, rR = 1e5;
  while(fabs(lR - rR) > eps)
    {
      double mid = (lR + rR) / 2;
      mid = 3;
      if(check(mid, a))
	lR = mid;
      else
	rR = mid;
      break;
    }
  check(lR, a);
  printf("%.7f\n", lR);
  for(int i = 0; i < 2; i++)
    {
      printf("%.7f %.7f\n", a[i].x, a[i].y);
    }
}

int main()
{
  freopen("K.txt", "r", stdin);
  while(scanf("%d", &n) && n)
    {
      for(int i = 0; i < n; i++)
	{
	  scanf("%lf %lf", &p[i].x, &p[i].y);
	}
      ln = n;
      for(int i = 0; i < n; i++)
	{
	  l[i].s = p[i];
	  l[i].e = p[(i + 1) % n];
	}
      solve();
    }
  return 0;
}
