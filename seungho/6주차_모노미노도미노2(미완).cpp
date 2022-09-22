#include <iostream>
using namespace std;


int greenMap[6][4] = { 0 };
int blueMap[6][4] = { 0 };

int ans = 0;

void stack1(int b, int t, int x, int y) {
	// greenMap
	int gflag = 0;
	for (int i = 2; i < 6; i++) {
		// 열에 블록이 있으면 가장 위에 블록 쌓기
		if (greenMap[i][y] > 0) {
			greenMap[i - 1][y] = b;
			gflag = 1;
			break;
		}
	}
	// 열이 비어있으면 가장 아래칸에 블록 쌓기
	if (gflag == 0) {
		greenMap[5][y] = b;
	}

	// blueMap
	int bflag = 0;
	for (int i = 2; i < 6; i++) {
		// 열에 블록이 있으면 가장 위에 블록 쌓기
		if (blueMap[i][x] != 0) {
			blueMap[i - 1][x] = b;
			bflag = 1;
			break;
		}
	}
	// 열이 비어있으면 가장 아래칸에 블록 쌓기
	if (bflag == 0) {
		blueMap[5][x] = b;
	}

}

void stack2(int b, int t, int x, int y) {
	int gflag = 0;
	for (int i = 2; i < 6; i++) {
		// 열에 블록이 있으면 가장 위에 블록 쌓기
		if ((greenMap[i][y] > 0) || (greenMap[i][y + 1] > 0)) {
			greenMap[i - 1][y] = b;
			greenMap[i - 1][y + 1] = b;
			gflag = 1;
			break;
		}
	}

	// 두 열이 모두 비어있으면 가장 아래칸에 블록 쌓기
	if (gflag == 0) {
		greenMap[5][y] = b;
		greenMap[5][y + 1] = b;
	}

	// blueMap (stack3 greenMap에서 y만 x로 바꿔준다)
	int bflag = 0;
	for (int i = 2; i < 6; i++) {
		// 열에 블록이 있으면 가장 위에 블록 쌓기
		if (blueMap[i][x] > 0) {
			blueMap[i - 1][x] = b;
			blueMap[i - 2][x] = b;
			bflag = 1;
			break;
		}
	}
	// 열이 비어있으면 가장 아래칸에 블록 쌓기
	if (bflag == 0) {
		blueMap[5][x] = b;
		blueMap[4][x] = b;
	}


}

void stack3(int b, int t, int x, int y) {
	int gflag = 0;
	for (int i = 2; i < 6; i++) {
		// 열에 블록이 있으면 가장 위에 블록 쌓기
		if (greenMap[i][y] > 0) {
			greenMap[i - 1][y] = b;
			greenMap[i - 2][y] = b;
			gflag = 1;
			break;
		}
	}
	// 열이 비어있으면 가장 아래칸에 블록 쌓기
	if (gflag == 0) {
		greenMap[5][y] = b;
		greenMap[4][y] = b;
	}

	// blueMap (stack2 greenMap에서 y만 x로 바꿔준다)

	int bflag = 0;
	for (int i = 2; i < 6; i++) {
		// 열에 블록이 있으면 가장 위에 블록 쌓기
		if ((blueMap[i][x] > 0) || (blueMap[i][x + 1] > 0)) {
			blueMap[i - 1][x] = b;
			blueMap[i - 1][x + 1] = b;
			bflag = 1;
			break;
		}
	}

	// 두 열이 모두 비어있으면 가장 아래칸에 블록 쌓기
	if (bflag == 0) {
		blueMap[5][x] = b;
		blueMap[5][x + 1] = b;
	}


}

// 한 줄이 다 찬 경우
int gpang() {
	int flag = 0;
	int i = 5;
	while (i >= 0) {
		// 현재 행에 0이 하나도 없다면 -> 모두 차 있다면
		if (greenMap[i][0] * greenMap[i][1] * greenMap[i][2] * greenMap[i][3] != 0) {
			flag++;
			ans++;
			for (int j = 0; j < 4; j++) {
				greenMap[i][j] = 0;
			}
			if (i == 0) continue;
			for (int k = i; k > 0; k--) {
				for (int l = 0; l < 4; l++) {
					greenMap[k][l] = greenMap[k - 1][l];
					greenMap[k - 1][l] = 0;
				}
			}
		}
		// 현재 행이 모두 차 있었다면 그 위의 블록 한칸씩 내리고 다시 확인
		// 아니면 그 위의 행부터 계속 확인
		else i--;
	}
	return flag;
}

int bpang() {
	int flag = 0;
	int i = 5;
	while (i >= 0) {
		// 현재 행에 0이 하나도 없다면 -> 모두 차 있다면
		if (blueMap[i][0] * blueMap[i][1] * blueMap[i][2] * blueMap[i][3] != 0) {
			flag++;
			ans++;
			for (int j = 0; j < 4; j++) {
				blueMap[i][j] = 0;
			}
			if (i == 0) continue;
			for (int k = i; k > 0; k--) {
				for (int l = 0; l < 4; l++) {
					blueMap[k][l] = blueMap[k - 1][l];
					blueMap[k - 1][l] = 0;
				}
			}
		}
		// 현재 행이 모두 차 있었다면 그 위의 블록 한칸씩 내리고 다시 확인
		// 아니면 그 위의 행부터 계속 확인
		else i--;
	}
	return flag;
}

// 0, 1번째 줄에 블록이 있는 경우
void gspecial() {
	int cnt = 0;
	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < 4; j++) {
			if (greenMap[i][j] > 0) {
				cnt++;
				break;
			}
		}
	}
	if (cnt == 1) {
		for (int j = 0; j < 4; j++) {
			greenMap[5][j] = 0;
		}
		for (int k = 5; k > 0; k--) {
			for (int l = 0; l < 4; l++) {
				greenMap[k][l] = greenMap[k - 1][l];
			}
		}
	}
	else if (cnt == 2) {
		for (int i = 4; i <= 5; i++) {
			for (int j = 0; j < 4; j++) {
				greenMap[i][j] = 0;
			}
		}
		for (int k = 5; k > 1; k--) {
			for (int l = 0; l < 4; l++) {
				greenMap[k][l] = greenMap[k - 2][l];
			}
		}
	}
	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < 4; j++) {
			greenMap[i][j] = 0;
		}
	}
}

void bspecial() {
	int cnt = 0;
	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < 4; j++) {
			if (blueMap[i][j] > 0) {
				cnt++;
				break;
			}
		}
	}
	if (cnt == 1) {
		for (int j = 0; j < 4; j++) {
			blueMap[5][j] = 0;
		}
		for (int k = 5; k > 0; k--) {
			for (int l = 0; l < 4; l++) {
				blueMap[k][l] = blueMap[k - 1][l];
			}
		}
	}
	else if (cnt == 2) {
		for (int i = 4; i <= 5; i++) {
			for (int j = 0; j < 4; j++) {
				blueMap[i][j] = 0;
			}
		}
		for (int k = 5; k > 1; k--) {
			for (int l = 0; l < 4; l++) {
				blueMap[k][l] = blueMap[k - 2][l];
			}
		}
	}
	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < 4; j++) {
			blueMap[i][j] = 0;
		}
	}
}


int main() {
	ios_base::sync_with_stdio(false);
	cin.tie();
	cout.tie();

	int N;
	cin >> N;

	for (int b = 1; b <= N; b++) {
		int t, x, y;
		cin >> t >> x >> y;

		// 블록 놓기
		if (t == 1) {
			stack1(b, t, x, y);
		}
		else if (t == 2) {
			stack2(b, t, x, y);
		}
		else {
			stack3(b, t, x, y);
		}

		// 꽉 찬 줄 없을 때까지 제거
		while (true) {
			int result = gpang();
			if (result == 0) break;
			for (int i = 0; i < 6; i++) {
				for (int j = 0; j < 4; j++) {
				}
			}
		}

		// 0, 1번째 줄에 블록이 있는 경우
		gspecial();

		for (int i = 0; i < 6; i++) {
			for (int j = 0; j < 4; j++) {
			}
		}

		// blueMap
		// 꽉 찬 줄 없을 때까지 제거
		while (true) {
			int result = bpang();
			if (result == 0) break;
		}

		// 0, 1번째 줄에 블록이 있는 경우
		bspecial();

	}

	int cnttile = 0;

	for (int i = 0; i < 6; i++) {
		for (int j = 0; j < 4; j++) {
			if (greenMap[i][j] > 0) cnttile++;
			if (blueMap[i][j] > 0) cnttile++;
		}
	}

	cout << ans << "\n";
	cout << cnttile;

	return 0;
}
