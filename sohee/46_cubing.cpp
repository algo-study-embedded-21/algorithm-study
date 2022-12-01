#include <iostream>
#include <string>
#include <vector>
using namespace std;

char side, dir;
int cnt;

char cube_origin[6][3][3] = {
	{	// 위
		{'w','w','w'},
		{'w','w','w'},
		{'w','w','w'},
	},
	{	// 앞
		{'r','r','r'},
		{'r','r','r'},
		{'r','r','r'}
	},
	{	// 아래
		{'y','y','y'},
		{'y','y','y'},
		{'y','y','y'}
	},
	{	// 뒤
		{'o','o','o'},
		{'o','o','o'},
		{'o','o','o'}
	},
	{	// 왼
		{'g','g','g'},
		{'g','g','g'},
		{'g','g','g'}
	},
	{	// 오
		{'b','b','b'},
		{'b','b','b'},
		{'b','b','b'}
	}
};

char cube[6][3][3];

void setCube() {
	for (int i = 0; i < 6; i++) {
		for (int j = 0; j < 3; j++) {
			for (int k = 0; k < 3; k++) {
				cube[i][j][k] = cube_origin[i][j][k];
			}
		}
	}
}

vector<vector<char>> getSide(int num, int op) {
	vector<vector<char>> v(3, vector <char> (3));
	if (op == 0) {
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
				v[i][j] = cube[num][i][j];
			}
		}
	}
	else if (op == 1) {
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
				v[i][j] = cube[num][2 - i][2 - j];
			}
		}
	}
	else if (op == 2) {
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
				v[i][j] = cube[num][j][2 - i];
			}
		}
	}
	else if (op == 3) {
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
				v[i][j] = cube[num][2 - j][i];
			}
		}
	}
	return v;
}

void setSide(int num, vector<vector<char>> v, int op) {
	if (op == 0) {
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
				cube[num][i][j] = v[i][j];
			}
		}
	}
	else if (op == 1) {
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
				cube[num][i][j] = v[2 - i][2 - j];
			}
		}
	}
	else if (op == 2) {
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
				cube[num][i][j] = v[2 - j][i];
			}
		}
	}
	else if (op == 3) {
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
				cube[num][i][j] = v[j][2 - i];
			}
		}
	}
}

void getAns() {
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			cout << cube[0][i][j];
		}
		cout << "\n";
	}
}

void roll(int main, int main_option, int sub[4], int sub_option[4]) {
	// 돌릴 면 구하기
	vector<vector<char>> center;
	vector<vector<char>> v[4];

	for (int i = 0; i < 4; i++) {
		v[i] = getSide(sub[i], sub_option[i]);
	}

	// 돌리기
	// 시계
	if (main_option == 0) {
		center = getSide(main, 3);
		char temp[3];
		for (int i = 0; i < 3; i++) temp[i] = v[3][2][i];
		for (int i = 3; i > 0; i--) {
			for (int j = 0; j < 3; j++) {
				v[i][2][j] = v[i - 1][2][j];
			}
		}
		for (int i = 0; i < 3; i++) {
			v[0][2][i] = temp[i];
		}
	}
	// 반시계
	else {
		center = getSide(main, 2);
		char temp[3];
		for (int i = 0; i < 3; i++) temp[i] = v[0][2][i];
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
				v[i][2][j] = v[i + 1][2][j];
			}
		}
		for (int i = 0; i < 3; i++) {
			v[3][2][i] = temp[i];
		}
	}

	// 전개도에 다시 저장하기
	setSide(main, center, 0);
	for (int i = 0; i < 4; i++) {
		setSide(sub[i], v[i], sub_option[i]);
	}
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie();
	cout.tie();

	int test;
	cin >> test;
	for (int t = 0; t < test; t++) {
		cin >> cnt;
		setCube();

		for (int i = 0; i < cnt; i++) {
			string cmd = "";
			cin >> cmd;
			side = cmd[0];
			dir = cmd[1];
			int option = dir == '+' ? 0 : 1;

			// 0 : 그대로, 1 : 반대로, 2 : 반시계, 3 : 시계
			switch (side) {
			case 'U': {
				int nums[4] = { 3, 5, 1, 4 };
				int ops[4] = { 0, 1, 1, 1 };
				roll(0, option, nums, ops);
				break;
			}
			case 'F': {
				int nums[4] = { 0, 5, 2, 4 };
				int ops[4] = { 0, 2, 1, 3 };
				roll(1, option, nums, ops);
				break;
			}
			case 'D': {
				int nums[4] = { 1, 5, 3, 4 };
				int ops[4] = { 0, 0, 1, 0 };
				roll(2, option, nums, ops);
				break;
			}
			case 'B': {
				int nums[4] = { 2, 5, 0, 4 };
				int ops[4] = { 0, 3, 1, 2 };
				roll(3, option, nums, ops);
				break;
			}
			case 'L': {
				int nums[4] = { 0, 1, 2, 3 };
				int ops[4] = { 2, 2, 2, 2 };
				roll(4, option, nums, ops);
				break;
			}
			case 'R': {
				int nums[4] = { 0, 3, 2, 1 };
				int ops[4] = { 3, 3, 3, 3 };
				roll(5, option, nums, ops);
				break;
			}
			}
		}

		getAns();
	}

	return 0;
}