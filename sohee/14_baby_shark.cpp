/*

��Ƹ��� �� �ִ� ���� ����� ����⸦ bfs�� ã��
���� ����� ����Ⱑ ���� ������ ��� priority_queue�� ���� �� ����
-> ��, ��, ��, �Ʒ� ������ �湮�ص� ���� ����� ������� ������ �������� ����

*/

#include <iostream>
#include <queue>
using namespace std;

int n;
int map[22][22];
int dx[] = { -1, 0, 0, 1 };
int dy[] = { 0, -1, 1, 0 };

struct shark {
	int x;
	int y;
	int size;
	// ������� ��Ƹ��� ��, ��������� ���κ����� �Ÿ�
	int food;
};

bool operator<(shark a, shark b) {
	if (a.x > b.x) return true;
	if (a.x < b.x) return false;
	if (a.y > b.y) return true;
	if (a.y < b.y) return false;
	return false;
}

shark s;

void bfs() {
	int time = 0;

	while (1) {
		int flag = 1;
		queue<shark> q;
		q.push({ s.x, s.y, 0, 0 });
		int visited[22][22] = { 0 };
		visited[s.x][s.y] = 1;
		priority_queue<shark> pq;

		while (!q.empty()) {
			shark now = q.front();
			q.pop();

			// ���� ����� ����⺸�� �Ÿ��� �־����� Ž���� �ʿ� ����
			if (!pq.empty() && now.food == pq.top().food) {
				flag = 0;
				continue;
			}

			for (int i = 0; i < 4; i++) {
				int nx = now.x + dx[i];
				int ny = now.y + dy[i];

				if (nx < 0 || nx >= n || ny < 0 || ny >= n) continue;
				if (visited[nx][ny]) continue;
				if (map[nx][ny] > s.size) continue;
				visited[nx][ny] = 1;
				q.push({ nx, ny, 0, now.food + 1 });
				// ���� �� �ִ� ����⸦ priority_queue�� ����
				if (map[nx][ny] != 0 && map[nx][ny] < s.size) pq.push({ nx, ny, 0, now.food + 1 });
			}
		}
		// ���� �� �ִ� ����Ⱑ ���� ��� Ž�� ����
		if (flag) break;

		// priority_queue�� top�� ���ǿ� ���� ù��°�� ���� �����
		shark now = pq.top();
		map[now.x][now.y] = 0;
		s.food++;
		s.x = now.x;
		s.y = now.y;
		if (s.food == s.size) {
			s.size++;
			s.food = 0;
		}
		time += now.food;
	}

	cout << time;
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie();
	cout.tie();

	cin >> n;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cin >> map[i][j];
			if (map[i][j] == 9) {
				s = { i, j, 2, 0 };
				map[i][j] = 0;
			}
		}
	}

	bfs();

	return 0;
}