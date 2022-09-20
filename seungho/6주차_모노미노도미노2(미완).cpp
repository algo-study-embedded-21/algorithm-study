#include <iostream>
using namespace std;


int greenMap[6][4];
int blueMap[4][6];



void stack1(int b, int t, int x, int y) {
	int flag = 0;
	for (int i = 2; i < 6; i++) {
		// 열에 블록이 있으면 가장 위에 블록 쌓기
		if (greenMap[i][y] != 0) {
			greenMap[i - 1][y] = b;
			flag = 1;
			break;
		}
	}
	// 열이 비어있으면 가장 아래칸에 블록 쌓기
	if (flag == 0) {
		greenMap[5][y] = b;
	}
}

void stack2(int b, int t, int x, int y) {
	int flag = 0;
	for (int i = 2; i < 6; i++) {
		// 열에 블록이 있으면 가장 위에 블록 쌓기
		if (greenMap[i][y] != 0 || greenMap[i][y+1] !=0) {
			greenMap[i - 1][y] = b;
			greenMap[i - 1][y + 1] = b;
			flag = 1;
			break;
		}
	}

	// 두 열이 모두 비어있으면 가장 아래칸에 블록 쌓기
	if (flag == 0) {
		greenMap[5][y] = b;
		greenMap[5][y + 1] = b;
	}
}

void stack3(int b, int t, int x, int y) {
	int flag = 0;
	for (int i = 2; i < 6; i++) {
		// 열에 블록이 있으면 가장 위에 블록 쌓기
		if (greenMap[i][y] != 0) {
			greenMap[i - 1][y] = b;
			greenMap[i - 2][y] = b;
			flag = 1;
			break;
		}
	}
	// 열이 비어있으면 가장 아래칸에 블록 쌓기
	if (flag == 0) {
		greenMap[5][y] = b;
	}
}


void pang() {
	for (int i = 0; i < 6; i++) {
		if (greenMap[i][0] * greenMap[i][1] * greenMap[i][2] * greenMap[i][3] != 0) {
			for (int j = 0; j < 4; j++) {
				greenMap[i][j] = 0;
			}
		}
	}
}

void gravity() {
	while (true) {
		int flag = 0;
		for (int i = 4; i >= 0; i--) {
			for (int j = 0; j < 4; j++) {
				if (greenMap[i][j] == 0) continue;
				if (greenMap[i + 1][j] != 0) continue;

			}
		}
	}
}



int main() {
	ios_base::sync_with_stdio(false);
	cin.tie();
	cout.tie();

	int N;
	cin >> N;

	for (int b = 0; b < N; b++) {
		int t, x, y;
		cin >> t >> x >> y;

		if (t == 1) {
			stack1(b, t, x, y);
		}
		else if (t == 2) {
			stack2(b, t, x, y);
		}
		else {
			stack3(b, t, x, y);
		}

	}




	return 0;
}
