#include<cstdio>
#include<cstring>
using namespace std;
int n, t[4][5];
char s[4];
bool flag = false;
int main() {
	scanf("%d", &n);
	while (1) {
		scanf("%s",s);
		for (int i = 0; i < 4; ++i) {
			switch(s[i]) {
			case '1': {
				t[i][0] = t[i][2] = t[i][4] = 0;
				t[i][1] = t[i][3] = 2;
				break;
			}
			case '2': {
				t[i][0] = t[i][2] = t[i][3] = t[i][4] = 1;
				t[i][1] = 2;
				break;
			}
			case '3': {
				t[i][0] = t[i][2] = t[i][4] = 1;
				t[i][1] = t[i][3] = 2;
				break;
			}
			case '4': {
				t[i][0] = t[i][4] = 0;
				t[i][1] = 3;
				t[i][2] = 1;
				t[i][3] = 2;
				break;
			}
			case '5': {
				t[i][0] = t[i][1] = t[i][2] = t[i][4] = 1;
				t[i][3] = 2;
				break;
			}
			case '6': {
				t[i][0] = t[i][1] = t[i][2] = t[i][4] = 1;
				t[i][3] = 3;
				break;
			}
			case '7':{
				t[i][0] = 1;
				t[i][1] = t[i][3] = 2;
				t[i][2] = t[i][4] = 0;
				break;
			}
			case '8':{
				t[i][0] = t[i][2] = t[i][4] = 1;
				t[i][1] = t[i][3] = 3;
				break;
			}
			case '9': {
				t[i][0] = t[i][2] = t[i][4] = 1;
				t[i][1] = 3;
				t[i][3] = 2;				
				break;
			}
			case '0': {
				t[i][0] = t[i][4] = 1;
				t[i][1] = t[i][3] = 3;
				t[i][2] = 0;
				break;
			}
			case '.': {
				t[i][0] = t[i][1] = t[i][2] = t[i][3] = t[i][4] = 10;
				break;
			}
			}
		}
		for (int i = 0; i < 4; ++i){
			if (t[i][0] == 0) {
				if (t[i][1] == 2) {
					for (int j = 1; j < n; ++j)
						printf(" ");
					printf("#");
				}
				else if (t[i][1] == 3) {
					printf("#");
					for (int j = 2; j < n; ++j)
						printf(" ");
					printf("#");
				}
			}
			else if (t[i][0] == 1)
				for (int j = 0; j < n; ++j)
					printf("#");
			else if (t[i][0] == 10)
						printf(" ");
			if (i != 3)
				printf(" ");
			else printf("\n");
		}
		for (int k = 1; k < n; ++k){
			for (int i = 0; i < 4; ++i){
				if(t[i][1] == 1) {
					printf("#");
					for (int j = 1; j < n; ++j)
						printf(" ");
				}
				else if (t[i][1] == 2) {
					for (int j = 1; j < n; ++j)
						printf(" ");
					printf("#");
				}
				else if (t[i][1] == 3) {
					printf("#");
					for (int j = 2; j < n; ++j)
						printf(" ");
					printf("#");
				}
				else if (t[i][1] == 10)
							printf(" ");
				if (i != 3)
					printf(" ");
				else printf("\n");
			}
		}
		for (int i = 0; i < 4; ++i){
			if (t[i][2] == 0){
				if (t[i][4] == 1) {
					printf("#");
					for (int j = 2; j < n; ++j)
						printf(" ");
					printf("#");
				}
				else {
					for (int j = 1; j < n; ++j)
						printf(" ");
					printf("#");
				}
			}
			else if (t[i][2] == 1)
				for (int j = 0; j < n; ++j)
					printf("#");
			else if (t[i][2] == 10)
						printf(" ");
			if (i != 3)
				printf(" ");
			else printf("\n");
		}
		for (int k = 1; k < n; ++k){
			for (int i = 0; i < 4; ++i){
				if(t[i][3] == 1) {
					printf("#");
					for (int j = 1; j < n; ++j)
						printf(" ");
				}
				else if (t[i][3] == 2) {
					for (int j = 1; j < n; ++j)
						printf(" ");
					printf("#");
				}
				else if (t[i][3] == 3) {
					printf("#");
					for (int j = 2; j < n; ++j)
						printf(" ");
					printf("#");
				}
				else if (t[i][3] == 10)
						printf(" ");
				if (i != 3)
					printf(" ");
				else printf("\n");
			}
		}
		for (int i = 0; i < 4; ++i){
			if (t[i][4] == 0){
				for (int j = 1; j < n; ++j)
					printf(" ");
				printf("#");
			}
			else if (t[i][4] == 1)
				for (int j = 0; j < n; ++j)
					printf("#");
			else if (t[i][4] == 10) {
				printf("#");
			}

			if (i != 3)
				printf(" ");
		}
		if (scanf("%d", &n) != EOF){
			printf("\n\n");
		}
		else break;
	}
	return 0;
}