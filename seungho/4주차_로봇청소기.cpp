#include <iostream>
using namespace std;

int N, M;
int MAP[50][50];

// 방향배열
// 북동남서
int diry[4] = { -1,0,1,0 };
int dirx[4] = { 0,1,0,-1 };

int main() {
	cin >> N >> M;
	int sy, sx, sd;
	cin >> sy >> sx >> sd;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			cin >> MAP[i][j];
		}
	}
	int y = sy;
	int x = sx;
	int d = sd;

	int cnt = 0;

	while (true) {
		// 현재 칸이 청소돼있지 않았다면 cnt++, 청소
		if (MAP[y][x] != 2) {
			cnt++;
			MAP[y][x] = 2;	
		}
			
		

		// 탐색
		// 현재 방향 기준 왼쪽부터 4방향
		int flag = 1;	// 이동할 곳이 있다면 0
		for (int i = 3; i >= 0; i--) {
			int ni = (d + i) % 4; 
			int ny = y + diry[ni];
			int nx = x + dirx[ni];
			if (ny < 0 || nx < 0 || ny >= N || nx >= M) continue;
			// 청소 안된 빈 공간이 있으면 회전, 이동
			if (MAP[ny][nx] == 0) {
				flag = 0;
				d = ni;
				y = ny;
				x = nx;
				break;
			};
		}

		if (flag == 1) {
			int ny = y + diry[(d+2)%4];
			int nx = x + dirx[(d+2)%4];
			if (MAP[ny][nx] == 1) break;	//후진 시 벽이면 종료
			else {
				// 방향 유지한 채로 후진
				y = ny;
				x = nx;
			}
		}
	}
	cout << cnt;
	return 0;
}    
