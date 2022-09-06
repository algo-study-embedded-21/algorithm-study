#include <iostream>
#include <vector>
using namespace std;

int dx[] = { 0, -1, 1, 0, 0 };
int dy[] = { 0, 0, 0, 1, -1 };
int r, c, m;

// 상어의 위치, 크기, 속력, 방향
struct shark {
	int x;
	int y;
	int size;
	int vel;
	int dx;
	int dy;
};

// 상어의 위치
int map[111][111];
// 이동한 상어의 위치
int new_map[111][111];
vector<shark> v;

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie();
	cout.tie();

	cin >> r >> c >> m;
	for (int i = 0; i < m; i++) {
		int x, y, s, d, z;
		cin >> x >> y >> s >> d >> z;
		v.push_back({ x - 1, y - 1, z, s, dx[d], dy[d] });
		// vector의 index를 저장
		map[x - 1][y - 1] = i + 1;
	}

	// 잡은 상어의 크기 합
	int cnt = 0;

	// 사람은 열의 크기만큼 이동을 반복함
	for (int j = 0; j < c; j++) {
		// 땅과 가장 가까운 상어 잡기
		for (int i = 0; i < r; i++) {
			if (map[i][j] == 0) continue;
			cnt += v[map[i][j] - 1].size;
			// 잡은 상어의 size를 0으로 변환
			v[map[i][j] - 1].size = 0;
			// 지도에서도 삭제
			map[i][j] = 0;
			break;
		}
		
		// 상어 이동
		for (int i = 0; i < m; i++) {
			// 잡힌 상어는 제외
			if (v[i].size == 0) continue;
			shark now = v[i];
			// 이동할 좌표 구하기
			int nx = -1;
			int ny = -1;
			int vel = now.vel;
			
			// 위, 아래로 이동하는 경우
			if (now.dx) {
				// (r - 1) * 2 만큼 움직이면 제자리로 돌아옴
				vel %= (r - 1) * 2;
				// 이동한 거리가 범위 내라면 그냥 계산
				if (now.x + now.dx * vel >= 0 && now.x + now.dx * vel < r) {
					nx = now.x + now.dx * vel;
				}
				// 범위를 초과할 경우
				else {
					// + 방향으로 이동한다면
					if (now.dx > 0) {
						// r - 1 행에서 부터 계산
						vel -= (r - 1 - now.x);
						// 한 번만 꺾는 경우 방향 전환
						if (vel / r == 0) {
							v[i].dx *= -1;
							nx = (r - 1) - vel;
						}
						// 두 번 꺾는 경우 방향 유지
						else {
							vel -= (r - 1);
							nx = vel;
						}
					}
					// - 방향으로 이동한다면
					else {
						// 0행에서 부터 계산
						vel -= now.x;
						if (vel / r == 0) {
							v[i].dx *= -1;
							nx = vel;
						}
						else {
							vel -= (r - 1);
							nx = (r - 1) - vel;
						}
					}
				}

				ny = now.y;
			}
			// 좌, 우로 이동하는 경우
			else {
				vel %= (c - 1) * 2;
				if (now.y + now.dy * vel >= 0 && now.y + now.dy * vel < c) {
					ny = now.y + now.dy * vel;
				}
				else {
					if (now.dy > 0) {
						vel -= (c - 1 - now.y);
						if (vel / c == 0) {
							v[i].dy *= -1;
							ny = (c - 1) - vel;
						}
						else {
							vel -= (c - 1);
							ny = vel;
						}
					}
					else {
						vel -= now.y;
						if (vel / c == 0) {
							v[i].dy *= -1;
							ny = vel;
						}
						else {
							vel -= (c - 1);
							ny = (c - 1) - vel;
						}
					}
				}

				nx = now.x;
			}

			map[now.x][now.y] = 0;
			// 이동한 곳에 이미 이동해 온 상어가 있다면
			if (new_map[nx][ny] != 0) {
				// 큰 놈만 기록
				if (v[new_map[nx][ny] - 1].size > now.size) {
					v[i].size = 0;
				}
				else {
					v[new_map[nx][ny] - 1].size = 0;
					v[i].x = nx;
					v[i].y = ny;
					new_map[nx][ny] = i + 1;
				}
			}else{
				v[i].x = nx;
				v[i].y = ny;
				new_map[nx][ny] = i + 1;
			}
		}
		// 낚시를 위해 map에 기록
		for (int i = 0; i < m; i++) {
			if (v[i].size == 0) continue;
			map[v[i].x][v[i].y] = i + 1;
			new_map[v[i].x][v[i].y] = 0;
		}
	}

	cout << cnt;

	return 0;
}