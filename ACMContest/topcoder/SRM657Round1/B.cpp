#include <cstdio>
using namespace std;
class ProblemSetsEasy {
public:
	bool judge(int x, int E, int EM, int M, int MH, int H) {
		if (E+EM < x)
			return false;
		if (E < x) 
			EM = EM - (x-E);
		if (H + MH < x)
			return false;
		if (H < x) 
			MH = MH - (x-H);
		if (M+EM+MH < x)
			return false;
		return true;
	}
	int maxSets(int E, int EM, int M, int MH, int H) {
		int l = 0, r = E+EM+M+MH+H, mid;
		while (l <= r) {
			mid = (l + r) >>1;
			if (judge(mid, E, EM, M, MH, H))
				l = mid+1;
			else 
				r = mid-1;
		}
		return r;
	}
};
int main() {
	ProblemSetsEasy s;
	printf("%d",s.maxSets(1,2,3,4,5));
}