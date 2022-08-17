#include <iostream>
using namespace std;

int N, M, x, y, K;
int MAP[21][21];

int dice[6] = { 0,0,0,0,0,0 };		// 주사위에 적힌 숫자
int dir[6] = { 0,1,2,3,4,5 };		// 0~5:위,아래,북,남,동,서


void roll(int order) {		// 주사위 이동
	int temp;

	switch (order) {
	case 1:							// 동쪽으로 이동			
		if (y + 1 > M - 1) return;
		y++;
		temp = dice[0];			
		dice[0] = dice[5];
		dice[5] = dice[1];
		dice[1] = dice[4];
		dice[4] = temp;
		break;

	case 2:							// 서쪽으로 이동
		if (y - 1 < 0) return;
		y--;
		temp = dice[0];			
		dice[0] = dice[4];
		dice[4] = dice[1];
		dice[1] = dice[5];
		dice[5] = temp;
		break;

	case 3:							// 북쪽으로 이동
		if (x - 1 < 0) return;
		temp = dice[0];			
		x--;
		dice[0] = dice[3];
		dice[3] = dice[1];
		dice[1] = dice[2];
		dice[2] = temp;
		break;

	case 4:							// 남쪽으로 이동
		if (x + 1 > N - 1) return;
		x++;
		temp = dice[0];			
		dice[0] = dice[2];
		dice[2] = dice[1];
		dice[1] = dice[3];
		dice[3] = temp;
		break;
	}
	if (MAP[x][y] == 0) {		// 이동할 칸 숫자가 0이면
		MAP[x][y] = dice[1];	// 주사위 바닥면 복사
	}
	else {						// 이동할 칸 숫자가 0 아니면
		dice[1] = MAP[x][y];	// 주사위 바닥면으로 복사
		MAP[x][y] = 0;			// 칸 숫자 -> 0
	}
	cout << dice[0]<<"\n";
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie();
	cout.tie();

	cin >> N >> M >> x >> y >> K;
	for (int j = 0; j < N; j++) {
		for (int i = 0; i < M; i++) {
			cin >> MAP[j][i];
		}
	}

	for (int i = 0; i < K; i++) {
		int order;
		cin >> order;
		roll(order);
	}

	return 0;
}
