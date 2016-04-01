#include <cstdio>
#include <cstring>

using namespace std;

int n;
int main(){
    int t;
    scanf("%d",&t);
    
    while (t--){
	scanf("%d",&n);
	static int ca = 0;
	printf("Case #%d: ",++ca);
	if (n == 0 || n == 14 || n == 34){
	    puts("UCOK");
	}else{
	    n = n % 34;
	    if (n == 4 || n == 8 || n == 20 || n == 24 || n == 28){
		puts("UCOK");
	    }else{
		puts("UDIN");
	    }
	}
    }
}
