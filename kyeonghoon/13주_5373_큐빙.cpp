#include<iostream>
#include<cstring>
using namespace std;


int T, n;

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cin >> T;
	while (T--) {
		int dice[6][3][3] = {
	{{0,0,0},
	 {0,0,0},
	 {0,0,0}},
	{{1,1,1},
	 {1,1,1},
	 {1,1,1}},
	{{2,2,2},
	 {2,2,2},
	 {2,2,2}},
	{{3,3,3},
	 {3,3,3},
	 {3,3,3}},
	{{4,4,4},
	 {4,4,4},
	 {4,4,4}},
	{{5,5,5},
	 {5,5,5},
	 {5,5,5}}
		};
		cin >> n;
		while (n--) {
			string s;
			cin >> s;
			if (s[0] == 'U') {
				if (s[1] == '+') {
					//윗면 시계방향
					int tmp[3][3] = { 0 };
					for (int i = 0; i < 3; i++) {
						for (int j = 0; j < 3; j++) {
							tmp[i][j] = dice[0][i][j];
						}
					}
					for (int i = 0; i < 3; i++) {
						for (int j = 0; j < 3; j++) {
							dice[0][i][j] = tmp[2 - j][i];
						}
					}
					for (int i = 0; i < 3; i++) {
						int mm = dice[1][0][0];
						dice[1][0][0] = dice[1][0][1];
						dice[1][0][1] = dice[1][0][2];
						dice[1][0][2] = dice[2][0][0];
						dice[2][0][0] = dice[2][0][1];
						dice[2][0][1] = dice[2][0][2];
						dice[2][0][2] = dice[3][0][0];
						dice[3][0][0] = dice[3][0][1];
						dice[3][0][1] = dice[3][0][2];
						dice[3][0][2] = dice[4][0][0];
						dice[4][0][0] = dice[4][0][1];
						dice[4][0][1] = dice[4][0][2];
						dice[4][0][2] = mm;
					}
				}
				else {
					//윗면 반시계방향
					int tmp[3][3] = { 0 };
					for (int i = 0; i < 3; i++) {
						for (int j = 0; j < 3; j++) {
							tmp[i][j] = dice[0][i][j];
						}
					}
					for (int i = 0; i < 3; i++) {
						for (int j = 0; j < 3; j++) {
							dice[0][i][j] = tmp[j][2 - i];
						}
					}
					for (int i = 0; i < 3; i++) {
						int mm = dice[4][0][2];
						dice[4][0][2] = dice[4][0][1];
						dice[4][0][1] = dice[4][0][0];
						dice[4][0][0] = dice[3][0][2];
						dice[3][0][2] = dice[3][0][1];
						dice[3][0][1] = dice[3][0][0];
						dice[3][0][0] = dice[2][0][2];
						dice[2][0][2] = dice[2][0][1];
						dice[2][0][1] = dice[2][0][0];
						dice[2][0][0] = dice[1][0][2];
						dice[1][0][2] = dice[1][0][1];
						dice[1][0][1] = dice[1][0][0];
						dice[1][0][0] = mm;
					}
				}
			}
			else if (s[0] == 'D') {
				if (s[1] == '+') {
					//아랫면 시계
					int tmp[3][3] = { 0 };
					for (int i = 0; i < 3; i++) {
						for (int j = 0; j < 3; j++) {
							tmp[i][j] = dice[5][i][j];
						}
					}
					for (int i = 0; i < 3; i++) {
						for (int j = 0; j < 3; j++) {
							dice[5][i][j] = tmp[2 - j][i];
						}
					}
					for (int i = 0; i < 3; i++) {
						int mm = dice[4][0][8];
						dice[4][0][8] = dice[4][0][7];
						dice[4][0][7] = dice[4][0][6];
						dice[4][0][6] = dice[3][0][8];
						dice[3][0][8] = dice[3][0][7];
						dice[3][0][7] = dice[3][0][6];
						dice[3][0][6] = dice[2][0][8];
						dice[2][0][8] = dice[2][0][7];
						dice[2][0][7] = dice[2][0][6];
						dice[2][0][6] = dice[1][0][8];
						dice[1][0][8] = dice[1][0][7];
						dice[1][0][7] = dice[1][0][6];
						dice[1][0][6] = mm;
					}
				}
				else {
					//아랫면 반시계
					int tmp[3][3] = { 0 };
					for (int i = 0; i < 3; i++) {
						for (int j = 0; j < 3; j++) {
							tmp[i][j] = dice[5][i][j];
						}
					}
					for (int i = 0; i < 3; i++) {
						for (int j = 0; j < 3; j++) {
							dice[5][i][j] = tmp[j][2 - i];
						}
					}
					for (int i = 0; i < 3; i++) {
						int mm = dice[1][0][6];
						dice[1][0][6] = dice[1][0][7];
						dice[1][0][7] = dice[1][0][8];
						dice[1][0][8] = dice[2][0][6];
						dice[2][0][6] = dice[2][0][7];
						dice[2][0][7] = dice[2][0][8];
						dice[2][0][8] = dice[3][0][6];
						dice[3][0][6] = dice[3][0][7];
						dice[3][0][7] = dice[3][0][8];
						dice[3][0][8] = dice[4][0][6];
						dice[4][0][6] = dice[4][0][7];
						dice[4][0][7] = dice[4][0][8];
						dice[4][0][8] = mm;
					}
				}
			}
			else if (s[0] == 'F') {
				//앞면 시계
				if (s[1] == '+') {
					int tmp[3][3] = { 0 };
					for (int i = 0; i < 3; i++) {
						for (int j = 0; j < 3; j++) {
							tmp[i][j] = dice[2][i][j];
						}
					}
					for (int i = 0; i < 3; i++) {
						for (int j = 0; j < 3; j++) {
							dice[2][i][j] = tmp[2 - j][i];
						}
					}
					for (int i = 0; i < 3; i++) {
						int mm = dice[1][0][2];
						dice[1][0][2] = dice[1][0][5];
						dice[1][0][5] = dice[1][0][8];
						dice[1][0][8] = dice[5][0][0];
						dice[5][0][0] = dice[5][0][1];
						dice[5][0][1] = dice[5][0][2];
						dice[5][0][2] = dice[3][0][6];
						dice[3][0][6] = dice[3][0][3];
						dice[3][0][3] = dice[3][0][0];
						dice[3][0][0] = dice[0][0][8];
						dice[0][0][8] = dice[0][0][7];
						dice[0][0][7] = dice[0][0][6];
						dice[0][0][6] = mm;
					}
				}
				else {
					//앞면 반시계
					int tmp[3][3] = { 0 };
					for (int i = 0; i < 3; i++) {
						for (int j = 0; j < 3; j++) {
							tmp[i][j] = dice[2][i][j];
						}
					}
					for (int i = 0; i < 3; i++) {
						for (int j = 0; j < 3; j++) {
							dice[2][i][j] = tmp[j][2 - i];
						}
					}
					for (int i = 0; i < 3; i++) {
						int mm = dice[0][0][6];
						dice[0][0][6] = dice[0][0][7];
						dice[0][0][7] = dice[0][0][8];
						dice[0][0][8] = dice[3][0][0];
						dice[3][0][0] = dice[3][0][3];
						dice[3][0][3] = dice[3][0][6];
						dice[3][0][6] = dice[5][0][2];
						dice[5][0][2] = dice[5][0][1];
						dice[5][0][1] = dice[5][0][0];
						dice[5][0][0] = dice[1][0][8];
						dice[1][0][8] = dice[1][0][5];
						dice[1][0][5] = dice[1][0][2];
						dice[1][0][2] = mm;
					}
				}
			}
			else if (s[0] == 'B') {
				if (s[1] == '+') {
					//뒷면 시계
					int tmp[3][3] = { 0 };
					for (int i = 0; i < 3; i++) {
						for (int j = 0; j < 3; j++) {
							tmp[i][j] = dice[4][i][j];
						}
					}
					for (int i = 0; i < 3; i++) {
						for (int j = 0; j < 3; j++) {
							dice[4][i][j] = tmp[2 - j][i];
						}
					}
					for (int i = 0; i < 3; i++) {
						int mm = dice[0][0][0];
						dice[0][0][0] = dice[0][0][1];
						dice[0][0][1] = dice[0][0][2];
						dice[0][0][2] = dice[3][0][2];
						dice[3][0][2] = dice[3][0][5];
						dice[3][0][5] = dice[3][0][8];
						dice[3][0][8] = dice[5][0][8];
						dice[5][0][8] = dice[5][0][7];
						dice[5][0][7] = dice[5][0][6];
						dice[5][0][6] = dice[1][0][6];
						dice[1][0][6] = dice[1][0][3];
						dice[1][0][3] = dice[1][0][0];
						dice[1][0][0] = mm;
					}
				}
				else {
					//뒷면 반시계
					int tmp[3][3] = { 0 };
					for (int i = 0; i < 3; i++) {
						for (int j = 0; j < 3; j++) {
							tmp[i][j] = dice[4][i][j];
						}
					}
					for (int i = 0; i < 3; i++) {
						for (int j = 0; j < 3; j++) {
							dice[4][i][j] = tmp[j][2 - i];
						}
					}
					for (int i = 0; i < 3; i++) {
						int mm = dice[1][0][0];
						dice[1][0][0] = dice[1][0][3];
						dice[1][0][3] = dice[1][0][6];
						dice[1][0][6] = dice[5][0][6];
						dice[5][0][6] = dice[5][0][7];
						dice[5][0][7] = dice[5][0][8];
						dice[5][0][8] = dice[3][0][8];
						dice[3][0][8] = dice[3][0][5];
						dice[3][0][5] = dice[3][0][2];
						dice[3][0][2] = dice[0][0][2];
						dice[0][0][2] = dice[0][0][1];
						dice[0][0][1] = dice[0][0][0];
						dice[0][0][0] = mm;
					}
				}
			}
			else if (s[0] == 'L') {
				if (s[1] == '+') {
					//왼쪽 시계
					int tmp[3][3] = { 0 };
					for (int i = 0; i < 3; i++) {
						for (int j = 0; j < 3; j++) {
							tmp[i][j] = dice[1][i][j];
						}
					}
					for (int i = 0; i < 3; i++) {
						for (int j = 0; j < 3; j++) {
							dice[1][i][j] = tmp[2 - j][i];
						}
					}
					for (int i = 0; i < 3; i++) {
						int mm = dice[4][0][2];
						dice[4][0][2] = dice[4][0][5];
						dice[4][0][5] = dice[4][0][8];
						dice[4][0][8] = dice[5][0][6];
						dice[5][0][6] = dice[5][0][3];
						dice[5][0][3] = dice[5][0][0];
						dice[5][0][0] = dice[2][0][6];
						dice[2][0][6] = dice[2][0][3];
						dice[2][0][3] = dice[2][0][0];
						dice[2][0][0] = dice[0][0][6];
						dice[0][0][6] = dice[0][0][3];
						dice[0][0][3] = dice[0][0][0];
						dice[0][0][0] = mm;
					}
				}
				else {
					//왼쪽 반시계
					int tmp[3][3] = { 0 };
					for (int i = 0; i < 3; i++) {
						for (int j = 0; j < 3; j++) {
							tmp[i][j] = dice[1][i][j];
						}
					}
					for (int i = 0; i < 3; i++) {
						for (int j = 0; j < 3; j++) {
							dice[1][i][j] = tmp[j][2 - i];
						}
					}
					for (int i = 0; i < 3; i++) {
						int mm = dice[0][0][0];
						dice[0][0][0] = dice[0][0][3];
						dice[0][0][3] = dice[0][0][6];
						dice[0][0][6] = dice[2][0][0];
						dice[2][0][0] = dice[2][0][3];
						dice[2][0][3] = dice[2][0][6];
						dice[2][0][6] = dice[5][0][0];
						dice[5][0][0] = dice[5][0][3];
						dice[5][0][3] = dice[5][0][6];
						dice[5][0][6] = dice[4][0][8];
						dice[4][0][8] = dice[4][0][5];
						dice[4][0][5] = dice[4][0][2];
						dice[4][0][2] = mm;
					}
				}
			}
			else if (s[0] == 'R') {
				if (s[1] == '+') {
					//오른쪽 시계
					int tmp[3][3] = { 0 };
					for (int i = 0; i < 3; i++) {
						for (int j = 0; j < 3; j++) {
							tmp[i][j] = dice[3][i][j];
						}
					}
					for (int i = 0; i < 3; i++) {
						for (int j = 0; j < 3; j++) {
							dice[3][i][j] = tmp[2 - j][i];
						}
					}
					for (int i = 0; i < 3; i++) {
						int mm = dice[0][0][2];
						dice[0][0][2] = dice[0][0][5];
						dice[0][0][5] = dice[0][0][8];
						dice[0][0][8] = dice[2][0][2];
						dice[2][0][2] = dice[2][0][5];
						dice[2][0][5] = dice[2][0][8];
						dice[2][0][8] = dice[5][0][2];
						dice[5][0][2] = dice[5][0][5];
						dice[5][0][5] = dice[5][0][8];
						dice[5][0][8] = dice[4][0][6];
						dice[4][0][6] = dice[4][0][3];
						dice[4][0][3] = dice[4][0][0];
						dice[4][0][0] = mm;
						
					}
				}
				else {
					//오른쪽 반시계
					int tmp[3][3] = { 0 };
					for (int i = 0; i < 3; i++) {
						for (int j = 0; j < 3; j++) {
							tmp[i][j] = dice[3][i][j];
						}
					}
					for (int i = 0; i < 3; i++) {
						for (int j = 0; j < 3; j++) {
							dice[3][i][j] = tmp[j][2 - i];
						}
					}
					for (int i = 0; i < 3; i++) {
						int mm = dice[4][0][0];
						dice[4][0][0] = dice[4][0][3];
						dice[4][0][3] = dice[4][0][6];
						dice[4][0][6] = dice[5][0][8];
						dice[5][0][8] = dice[5][0][5];
						dice[5][0][5] = dice[5][0][2];
						dice[5][0][2] = dice[2][0][8];
						dice[2][0][8] = dice[2][0][5];
						dice[2][0][5] = dice[2][0][2];
						dice[2][0][2] = dice[0][0][8];
						dice[0][0][8] = dice[0][0][5];
						dice[0][0][5] = dice[0][0][2];
						dice[0][0][2] = mm;
					}
				}
			}

		}
		// 0 w  1 g  2 r  3 b  4 o  5 y

		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
				if (dice[0][i][j] == 0) {
					cout << 'w';
				}
				else if (dice[0][i][j] == 1) {
					cout << "g";
				}
				else if (dice[0][i][j] == 2) {
					cout << "r";
				}
				else if (dice[0][i][j] == 3) {
					cout << "b";
				}
				else if (dice[0][i][j] == 4) {
					cout << "o";
				}
				else if (dice[0][i][j] == 5) {
					cout << "y";
				}
			}
			cout << '\n';
		}
	}
}
