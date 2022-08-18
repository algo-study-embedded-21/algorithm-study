/*

1. 구현 문제다,, 
2. 주사위의 숫자를 어떻게 저장하면 좋을까? 
	- 방향에 대한 정보나 각 면 사이의 관계를 알 수 있는 정보가 필요할 것 같은데,,
	- 전개도를 두 개의 dat를 이용해 표현해보자
3. 자잘한 구현 사항들 구현

*/
#include <iostream>
using namespace std;

// 방향 배열
// 커맨드가 1부터라 0번 인덱스 0으로 둠
int dx[] = { 0, 0, 0, -1, 1 };
int dy[] = { 0, 1, -1, 0, 0 };

// 처음엔 전개도의 가로 부분을 3으로 뒀었는데
// 그럼 동쪽이나 서쪽으로 회전시켰을 떄에는 바닥 정보를 갱신할 수 없음
int row[4];
int col[4];
int n, m, k;
int x, y;
int map[21][21];

// 회전하는 방향에 따라 배열을 수정
void goToEast() {
	int a = row[3];
	for (int i = 3; i > 0; i--) {
		row[i] = row[i - 1];
	}
	row[0] = a;
	col[1] = row[1];
	col[3] = row[3];
}

void goToWest() {
	int a = row[0];
	for (int i = 0; i < 3; i++) {
		row[i] = row[i + 1];
	}
	row[3] = a;
	col[1] = row[1];
	col[3] = row[3];
}

void goToSouth() {
	int a = col[3];
	for (int i = 3; i > 0; i--) {
		col[i] = col[i - 1];
	}
	col[0] = a;
	row[1] = col[1];
	row[3] = col[3];
}

void goToNorth() {
	int a = col[0];
	for (int i = 0; i < 3; i++) {
		col[i] = col[i + 1];
	}
	col[3] = a;
	row[1] = col[1];
	row[3] = col[3];
}

void playDice(int cmd) {
	int nx = x + dx[cmd];
	int ny = y + dy[cmd];

	// 벽이면 실행 명령 무시
	if (nx < 0 || nx >= n || ny < 0 || ny >= m) return;

	x = nx;
	y = ny;

	// 주사위 굴리고
	switch (cmd) {
	case 1: {
		goToEast();
		break;
	}
	case 2: {
		goToWest();
		break;
	}
	case 3: {
		goToNorth();
		break;
	}
	case 4: {
		goToSouth();
		break;
	}
	}

	// 상단 숫자 출력
	cout << row[1] << '\n';

	// 바닥 숫자 바꾸기
	if (map[x][y] == 0) {
		map[x][y] = col[3];
	}
	else {
		// col 배열과 row 배열에 저장한 바닥 정보 함께 갱신
		col[3] = map[x][y];
		row[3] = map[x][y];
		map[x][y] = 0;
	}
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie();
	cout.tie();

	cin >> n >> m >> x >> y >> k;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			cin >> map[i][j];
		}
	}

	for (int i = 0; i < k; i++) {
		int cmd;
		cin >> cmd;
		playDice(cmd);
	}

	return 0;
}
