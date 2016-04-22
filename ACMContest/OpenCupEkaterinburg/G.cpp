#include <iostream>
#include <string>

using namespace std;

string a;

int main() {
    while(cin >> a) {
	cin >> a;
	cin >> a;
	int len = 0;
	for(int i = a.size() - 1; i >= 0; i--) {
	    if(a[i] == '!') {
		len++;
	    }
	}
	if(len == 0) {
	    cout << "Pfff" << endl;
	}
	else {
	    cout << "W";
	    for(int i = 0; i < len; i++) {
		cout << "o";
	    }
	    cout << "w" << endl;
	}
    }
    return 0;
}
