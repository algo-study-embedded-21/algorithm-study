#include <iostream>
using namespace std;


int greenMap[6][4]={0};
int blueMap[6][4]={0};

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
	for (int i = 0; i < 6; i++) {
		// 현재 행에 0이 하나도 없다면 -> 모두 차 있다면
		if (greenMap[i][0] * greenMap[i][1] * greenMap[i][2] * greenMap[i][3] != 0) {
			flag++;
			ans++;
			for (int j = 0; j < 4; j++) {
				greenMap[i][j] = 0;
			}
		}
	}
	return flag;
}

int bpang() {
	int flag = 0;
	for (int i = 0; i < 6; i++) {
		// 현재 열에 0이 하나도 없다면 -> 모두 차 있다면
		if (blueMap[i][0] * blueMap[i][1] * blueMap[i][2] * blueMap[i][3] != 0) {
			flag++;
			ans++;
			for (int j = 0; j < 4; j++) {
				blueMap[i][j] = 0;
			}
		}
	}
	return flag;
}

// 중력
void ggravity(int r) {
	for (int k = 0; k < r; k++) {
		int flag = 0;
		for (int i = 4; i >= 0; i--) {
			for (int j = 0; j < 4; j++) {
				if (greenMap[i][j] == 0) continue;
				if (greenMap[i + 1][j] != 0) continue;
				// 현재 블록이 오른쪽 블록과 연결돼있고 오른쪽 아래에 블록이 있다면 내려가지 않는다
				if (j < 3 && (greenMap[i][j] == greenMap[i][j + 1]) && (greenMap[i + 1][j + 1] > 0)) continue;

				// 현재 블록이 왼쪽 블록과 연결돼있고 왼쪽 블록이 내려가지 않았다면 내려가지 않는다
				if (j > 0 && (greenMap[i][j] == greenMap[i][j - 1])) continue;

				// 위의 경우가 모두 아니면 내려간다
				flag = 1;
				greenMap[i + 1][j] = greenMap[i][j];
				greenMap[i][j] = 0;
			}
		}
		// 더 이상 블록이 내려가지 않으면 break;
		if (flag == 0) break;
	}
}

void bgravity(int r) {
	for (int k = 0; k < r; k++) {
		int flag = 0;
		for (int i = 4; i >= 0; i--) {
			for (int j = 0; j < 4; j++) {
				if (blueMap[i][j] == 0) continue;
				if (blueMap[i + 1][j] != 0) continue;
				// 현재 블록이 오른쪽 블록과 연결돼있고 오른쪽 아래에 블록이 있다면 내려가지 않는다
				if (j < 3 && (blueMap[i][j] == blueMap[i][j + 1]) && (blueMap[i + 1][j + 1] > 0)) continue;

				// 현재 블록이 왼쪽 블록과 연결돼있고 왼쪽 블록이 내려가지 않았다면 내려가지 않는다
				if (j > 0 && (blueMap[i][j] == blueMap[i][j - 1])) continue;

				// 위의 경우가 모두 아니면 내려간다
				flag = 1;
				blueMap[i + 1][j] = blueMap[i][j];
				blueMap[i][j] = 0;
			}
		}
		// 더 이상 블록이 내려가지 않으면 break;
		if (flag == 0) break;
	}
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
		ggravity(1);
	}
	else if (cnt == 2) {
		for (int i = 4; i <= 5; i++) {
			for (int j = 0; j < 4; j++) {
				greenMap[i][j] = 0;
			}
		}
		ggravity(2);
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
		bgravity(1);
	}
	else if (cnt == 2) {
		for (int i = 4; i <= 5; i++) {
			for (int j = 0; j < 4; j++) {
				blueMap[i][j] = 0;
			}
		}
		bgravity(2);
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
			ggravity(result);
		}

		// 0, 1번째 줄에 블록이 있는 경우
		gspecial();

		// blueMap
		// 꽉 찬 줄 없을 때까지 제거
		while (true) {
			int result = bpang();
			if (result == 0) break;
			bgravity(result);
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
