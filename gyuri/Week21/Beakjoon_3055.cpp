//#include <iostream>
//#include <queue>
//using namespace std;
//
//int r, c;
//char arr[51][51];
//int water[51][51];
//int hedgehog[51][51];
//int sy, sx, ey, ex;
//
//struct COORD {
//	int y, x;
//};
//
//int dy[4] = { 0, 0, -1, 1 };
//int dx[4] = { 1, -1, 0, 0 };
//
//void input() {
//	cin >> r >> c;
//
//	for (int i = 0; i < r; i++) {
//		cin >> arr[i];
//	}
//}
//
//void waterBfs(COORD start) {
//	queue<COORD> q;
//	q.push(start);
//	water[start.y][start.x] = 1;
//
//	while (!q.empty()) {
//
//		COORD now = q.front();
//		q.pop();
//
//		for (int i = 0; i < 4; i++) {
//			int ny = now.y + dy[i];
//			int nx = now.x + dx[i];
//
//			if (ny < 0 || nx < 0 || ny >= r || nx >= c) continue;
//			if (arr[ny][nx] == 'X') continue;
//			if (arr[ny][nx] == 'D') continue;
//			if (water[ny][nx] > 0) continue;
//
//			water[ny][nx] = water[now.y][now.x] + 1;
//			q.push({ ny, nx });
//		}
//	}
//}
//
//void hedgeBfs(COORD start) {
//
//	queue<COORD> q;
//	q.push(start);
//	hedgehog[start.y][start.x] = 1;
//
//	while (!q.empty()) {
//
//		COORD now = q.front();
//		q.pop();
//
//		for (int i = 0; i < 4; i++) {
//			int ny = now.y + dy[i];
//			int nx = now.x + dx[i];
//
//			if (ny < 0 || nx < 0 || ny >= r || nx >= c) continue;
//			if (arr[ny][nx] == 'X') continue;
//			if (arr[ny][nx] == '*') continue;
//			if (hedgehog[ny][nx] > 0) continue;
//			if (water[ny][nx] != 0 && water[ny][nx] <= hedgehog[now.y][now.x]+1) continue;
//
//			hedgehog[ny][nx] = hedgehog[now.y][now.x] + 1;
//			q.push({ ny, nx });
//		}
//	}
//}
//
//void findCoord() {
//	for (int i = 0; i < r; i++) {
//		for (int j = 0; j < c; j++) {
//			if (arr[i][j] == '*') {
//				waterBfs({ i, j });
//			}
//			if (arr[i][j] == 'S') {
//				sy = i, sx = j;
//			}
//			if (arr[i][j] == 'D') {
//				ey = i, ex = j;
//			}
//		}
//	}
//}
//
//
//
//void output() {
//	if (hedgehog[ey][ex] != 0) cout << hedgehog[ey][ex]-1;
//	else cout << "KAKTUS";
//}
//
//int main() {
//	ios_base::sync_with_stdio(false);
//	cin.tie(0);
//	cout.tie(0);
//	
//	input();
//	findCoord();
//	hedgeBfs({ sy, sx });
//	output();
//}