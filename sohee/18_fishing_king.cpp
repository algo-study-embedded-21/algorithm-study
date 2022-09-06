#include <iostream>
#include <vector>
using namespace std;

int dx[] = { 0, -1, 1, 0, 0 };
int dy[] = { 0, 0, 0, 1, -1 };
int r, c, m;

// ����� ��ġ, ũ��, �ӷ�, ����
struct shark {
	int x;
	int y;
	int size;
	int vel;
	int dx;
	int dy;
};

// ����� ��ġ
int map[111][111];
// �̵��� ����� ��ġ
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
		// vector�� index�� ����
		map[x - 1][y - 1] = i + 1;
	}

	// ���� ����� ũ�� ��
	int cnt = 0;

	// ����� ���� ũ�⸸ŭ �̵��� �ݺ���
	for (int j = 0; j < c; j++) {
		// ���� ���� ����� ��� ���
		for (int i = 0; i < r; i++) {
			if (map[i][j] == 0) continue;
			cnt += v[map[i][j] - 1].size;
			// ���� ����� size�� 0���� ��ȯ
			v[map[i][j] - 1].size = 0;
			// ���������� ����
			map[i][j] = 0;
			break;
		}
		
		// ��� �̵�
		for (int i = 0; i < m; i++) {
			// ���� ���� ����
			if (v[i].size == 0) continue;
			shark now = v[i];
			// �̵��� ��ǥ ���ϱ�
			int nx = -1;
			int ny = -1;
			int vel = now.vel;
			
			// ��, �Ʒ��� �̵��ϴ� ���
			if (now.dx) {
				// (r - 1) * 2 ��ŭ �����̸� ���ڸ��� ���ƿ�
				vel %= (r - 1) * 2;
				// �̵��� �Ÿ��� ���� ����� �׳� ���
				if (now.x + now.dx * vel >= 0 && now.x + now.dx * vel < r) {
					nx = now.x + now.dx * vel;
				}
				// ������ �ʰ��� ���
				else {
					// + �������� �̵��Ѵٸ�
					if (now.dx > 0) {
						// r - 1 �࿡�� ���� ���
						vel -= (r - 1 - now.x);
						// �� ���� ���� ��� ���� ��ȯ
						if (vel / r == 0) {
							v[i].dx *= -1;
							nx = (r - 1) - vel;
						}
						// �� �� ���� ��� ���� ����
						else {
							vel -= (r - 1);
							nx = vel;
						}
					}
					// - �������� �̵��Ѵٸ�
					else {
						// 0�࿡�� ���� ���
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
			// ��, ��� �̵��ϴ� ���
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
			// �̵��� ���� �̹� �̵��� �� �� �ִٸ�
			if (new_map[nx][ny] != 0) {
				// ū �� ���
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
		// ���ø� ���� map�� ���
		for (int i = 0; i < m; i++) {
			if (v[i].size == 0) continue;
			map[v[i].x][v[i].y] = i + 1;
			new_map[v[i].x][v[i].y] = 0;
		}
	}

	cout << cnt;

	return 0;
}