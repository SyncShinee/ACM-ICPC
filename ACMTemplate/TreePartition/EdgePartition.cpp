/* 
树基于边的分治算法，计算树中距离小于等于k的点对数目
点的下标从1开始，树里实际的节点个数的上界是N*3
当点只有一个的时候，得到的是空树(这个需要注意)，
分治树有O(log(NUM))层，如果会动态改变树里的信息的话，
还需要记录每个的节点在每一层是在左子树还是右子树，以及在这一层
到根的距离信息(这里的根指的是这一层的分治边的两个点中到该点距离
较近的那个点)。
树重构后[1,n]为原树中的节点，[n+1,cnt]为虚拟节点
*/ 
#include <cstdio>
#include <algorithm>
#include <cmath>
#include <ctime>
using namespace std;
const int N = 10005;
const int NUM=N*3; //重构后树中的节点的个数最大值
typedef int wtype;  //边权的类型
const wtype INF = 0X7FFFFFFF;
struct e{
	int u, v;
	wtype len;
	e *nxt, *pair;
	bool used;  //标记一条边是否已经被选过了
	//分治树的数据结构
	e *ls, *rs;
}*fir[NUM], es[(NUM+N)*2];
int n, en, cnt, k; //cnt为重构后的树中的节点
int que[NUM], par[NUM], size[NUM];
e* eque[NUM];
wtype len[NUM];
wtype lens[2][NUM];
int nums[2], ans;
void clear(int n){
	en = 0;
	int i;
	for(i = 1; i <= n; i++){
		fir[i] = NULL;
	}
}
void add_e(int u, int v, e* pair, wtype len){
	es[en].u = u;
	es[en].v = v;
	es[en].pair = pair;
	es[en].len = len;
	es[en].used = false;
	es[en].nxt = fir[u];
	fir[u] = &es[en++];
}
void insert(int u, int v, wtype len){
	add_e(u, v, &es[en+1], len);
	add_e(v, u, &es[en-1], len);
}
void adjust(int l, int r, int f, int& cnt){
	if(r-l <= 1){
		while(l <= r){
			int u = que[l];
			par[u] = f;
			insert(u, f, eque[l++]->len);
		}
	}else{
		int mid = (l+r)>>1, ls, rs;
		fir[ls=++cnt] = NULL; insert(ls, f, 0);
		fir[rs=++cnt] = NULL; insert(rs, f, 0);
		par[ls]=par[rs]=f;
		adjust(l, mid, ls, cnt);
		adjust(mid+1, r, rs, cnt);
	}
}
void adjust(int n){ //重构树
	int l, r, u, v, mid;
	e* cur;
	cnt = n;
	for(l=r=0, par[1]=-1, que[r++]=1; l!=r; ){
		for(cur = fir[u=que[l++]], mid=r; cur; cur = cur->nxt){
			if(!cur->used && (v=cur->v) != par[u]){
				que[r] = v;
				par[v] = u;
				eque[r++] = cur;
			}
		}
		if(r-mid > 2){
			adjust(mid, r-1, u, cnt);
			//删边，只需把那些边的used标记为true即可
			while(mid<r){
				eque[mid]->used=true;
				eque[mid++]->pair->used=true;
			}
		}
	}
}
inline int ABS(int a){
	return a>0 ? a:-a;
}
e* getRoot(int s, bool isLeft){  //找根节点
	e *ans=NULL, *cur;
	int l, r, u, num, v, ds, i;
	nums[isLeft]=0;
	for(l=r=0, par[s]=-1, len[s]=0, que[r++]=s; l!=r; ){
		for(cur=fir[u=que[l++]]; cur; cur=cur->nxt){
			if(!cur->used && (v=cur->v) != par[u]){
				eque[r]=cur;
				que[r++]=v;
				par[v]=u;
				len[v]=len[u]+cur->len;
			}
		}
	}
	for(i=r-1; i>=0; i--){
		if(que[i] <= n){
			lens[isLeft][nums[isLeft]++]=len[que[i]];
		}
	}
	for(num=r, i=r-1; i>=1; i--){//队列里的第一个点不可能被选择
		u=que[i]; size[u]=1;
		for(cur=fir[u]; cur; cur=cur->nxt){
			if(!cur->used && (v=cur->v) != par[u]){
				size[u] += size[v];
			}
		}
		if(ans==NULL || ds > ABS(num-size[u]*2)){
			ans=eque[i];
			ds=ABS(num-size[u]*2);
		}
	}
	return ans;
}
void division(e*& r, int d){
	if(!r) return ;
	//r->u作为左孩子，r->v作为右孩子
	r->used = true; r->pair->used = true;
	r->ls = getRoot(r->u, true);
	r->rs = getRoot(r->v, false);
	int il, ir;
	//计算点对
	sort(lens[0], lens[0]+nums[0]);
	sort(lens[1], lens[1]+nums[1]);
	for(il=0, ir=nums[0]-1; il<nums[1]; il++){
		while(ir >= 0 && lens[1][il]+lens[0][ir]+r->len>k) ir--;
		ans += ir+1;
	}
	division(r->ls, d+1);
	division(r->rs, d+1);
}
//r为根节点(初始为空，s为一个起点，n为点的个数)
void build(e*& r, int s, int n){ //构建分治树
	adjust(n);  //首先得调整树的结构
	r = getRoot(s, false);
	division(r, 1);
}

//输入一个整数
template<typename T>
void getSNum(T& ans){
	char ch;
	int s;
	while(true){
		ch = getchar();
		if((ch >= '0' && ch <= '9') || ch == '-') break;
	}
	if(ch == '-'){
		s = -1;
		ans = 0;
	}else{
		s = 1;
		ans = ch -'0';
	}
	while(true){
		ch = getchar();
		if(!(ch >= '0' && ch <= '9')) break;
		ans = ans*10+ch-'0';
	}
	ans *= s;
}
bool input(){
	scanf("%d%d", &n, &k);
	if(n == 0 && k == 0) return false;
	int u, v, i;
	wtype len;
	clear(n);
	for(i = 1; i < n; i++){
		getSNum(u);
		getSNum(v);
		getSNum(len);
		insert(u, v, len);
	}
	return true;
}
void solve(){
	e* root=NULL;
	ans=0;
	if(n > 1){
		build(root, 1, n);
	}
	printf("%d\n", ans);
}
int main(){
	//freopen("in.txt", "r", stdin);
	while(input()) solve();
	return 0;
}
