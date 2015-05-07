#include <cstdio>
#include <string>
#include <vector>
using namespace std;
class EightRooks {
	int col[16], row[16], sum;
	public :
	string isCorrect(vector <string> board) {
		sum = 0;
		for (int i = 0; i < 8; ++i) {
			col[i] = 0;
			row[i] = 0;
		}
		for (int i = 0; i < 8; ++i)
			for (int j = 0; j < 8; ++j) {
				if (board[i][j] == 'R') {
					sum++;
					col[i]++;
					row[j]++;
				}
			}
		for (int i = 0; i < 8; ++i)
			if (col[i] != 1 || row[i] != 1) {
				return "Incorrect";
			}
		if (sum != 8)
			return "Incorrect";
		return "Correct";
	}
};
int main() {
	EightRooks s;

}