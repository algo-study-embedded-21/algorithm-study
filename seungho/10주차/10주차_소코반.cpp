#include <iostream>
#include <string.h>
using namespace std;

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie();
	cout.tie();

	int t = 1;

	while (1) {
		int R, C;

		// 캐릭터 현재 위치
		int wy = 0;
		int wx = 0;
		int MAP2[20][20] = { 0 };
		int endgame = 0;
		cin >> R >> C;
		if (R == 0 && C == 0) break;
		string MAP[20];
		for (int i = 0; i < R; i++) {
			cin >> MAP[i];
		}

		// 플레이어 위치 찾기
		for (int i = 0; i < R; i++) {
			for (int j = 0; j < C; j++) {
				if (MAP[i][j] == 'w' || MAP[i][j] == 'W') {
					wy = i;
					wx = j;
				}
				if (MAP[i][j] == '+' || MAP[i][j] == 'W' || MAP[i][j] == 'B') MAP2[i][j] = 3;
			}
		}
		string cmd;		// 방향입력
		cin >> cmd;
		for (int c = 0; c < cmd.length(); c++) {
			if (cmd[c] == 'U') {
				int ny = wy - 1;
				if (ny < 0) continue;
				if (MAP[ny][wx] == '#') continue;	// 다음 칸 벽이면 continue
				if (MAP[ny][wx] == 'b' || MAP[ny][wx] == 'B') {		// 다음 칸 상자인 경우
					if (MAP[ny - 1][wx] == 'b' || MAP[ny - 1][wx] == 'B' || MAP[ny - 1][wx] == '#') continue;	// 두 칸 뒤가 상자나 벽인 경우
					if (MAP2[ny - 1][wx] == 3) MAP[ny - 1][wx] = 'B';	// 상자가 밀릴 칸이 +면 'B'
					else MAP[ny - 1][wx] = 'b';
				}
				if (MAP2[ny][wx] == 3) MAP[ny][wx] = 'W';	// 캐릭터가 이동할 칸이 +면 'W'
				else MAP[ny][wx] = 'w';
				if (MAP2[wy][wx] == 3) {		// 원래 캐릭터 위치가 +면 +
					MAP[wy][wx] = '+';
				}
				else MAP[wy][wx] = '.';
				wy = ny;
			}
			else if (cmd[c] == 'D') {
				int ny = wy + 1;
				if (ny >= R) continue;
				if (MAP[ny][wx] == '#') continue;
				if (MAP[ny][wx] == 'b' || MAP[ny][wx] == 'B') {
					if (MAP[ny + 1][wx] == 'b' || MAP[ny + 1][wx] == 'B' || MAP[ny + 1][wx] == '#') continue;
					if (MAP2[ny + 1][wx] == 3) MAP[ny + 1][wx] = 'B';
					else MAP[ny + 1][wx] = 'b';
				}
				if (MAP2[ny][wx] == 3) MAP[ny][wx] = 'W';
				else MAP[ny][wx] = 'w';
				if (MAP2[wy][wx] == 3) {
					MAP[wy][wx] = '+';
				}
				else MAP[wy][wx] = '.';
				wy = ny;
			}
			else if (cmd[c] == 'L') {
				int nx = wx - 1;
				if (nx < 0) continue;
				if (MAP[wy][nx] == '#') continue;
				if (MAP[wy][nx] == 'b' || MAP[wy][nx] == 'B') {
					if (MAP[wy][nx - 1] == 'b' || MAP[wy][nx - 1] == 'B' || MAP[wy][nx - 1] == '#') continue;
					if (MAP2[wy][nx - 1] == 3) MAP[wy][nx - 1] = 'B';
					else MAP[wy][nx - 1] = 'b';
				}
				if (MAP2[wy][nx] == 3) MAP[wy][nx] = 'W';
				else MAP[wy][nx] = 'w';
				if (MAP2[wy][wx] == 3) {
					MAP[wy][wx] = '+';
				}
				else MAP[wy][wx] = '.';
				wx = nx;
			}
			else if (cmd[c] == 'R') {
				int nx = wx + 1;
				if (nx >= C) continue;
				if (MAP[wy][nx] == '#') continue;
				if (MAP[wy][nx] == 'b' || MAP[wy][nx] == 'B') {
					if (MAP[wy][nx + 1] == 'b' || MAP[wy][nx + 1] == 'B' || MAP[wy][nx + 1] == '#') continue;
					if (MAP2[wy][nx + 1] == 3) MAP[wy][nx + 1] = 'B';
					else MAP[wy][nx + 1] = 'b';
				}
				if (MAP2[wy][nx] == 3) MAP[wy][nx] = 'W';
				else MAP[wy][nx] = 'w';
				if (MAP2[wy][wx] == 3) {
					MAP[wy][wx] = '+';
				}
				else MAP[wy][wx] = '.';
				wx = nx;
			}

			int flag = 1;
			for (int i = 0; i < R; i++) {
				for (int j = 0; j < C; j++) {
					if (MAP[i][j] == 'b') {
						flag = 0;
						break;
					}
				}
				if (flag == 0) break;
			}
			if (flag == 1) {
				endgame = 1;
				break;
			}
		}

		cout << "Game " << t;
		if (endgame == 0) {
			cout << ": incomplete\n";
		}
		else {
			cout << ": complete\n";
		}
		for (int i = 0; i < R; i++) {
			cout << MAP[i] << "\n";
		}
		t++;
	}
	return 0;
}
