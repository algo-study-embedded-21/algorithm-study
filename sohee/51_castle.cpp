#include <iostream>
#include <vector>
using namespace std;

// ���ϵ���
int map[50][50][4];
int visited[50][50];
int visited2[50][50];
int n, m;
int ans1, ans2, ans3;
int dx[] = { 0, -1, 0, 1 };
int dy[] = { -1, 0, 1, 0 };
int best;
// �� ���� ���� ���� ����
vector<pair<int, int>> v;

void visit_clear() {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			visited2[i][j] = 0;
		}
	}
}

int dfs(int r, int c, int idx) {
	int cnt = 1;
	visited[r][c] = idx;
	for (int i = 0; i < 4; i++) {
		if (map[r][c][i]) continue;
		int nx = r + dx[i];
		int ny = c + dy[i];
		if (nx < 0 || nx >= n || ny < 0 || ny >= m) continue;
		if (visited[nx][ny]) continue;
		cnt += dfs(nx, ny, idx);
	}
	return cnt;
}

int dfs2(int r, int c, int flag, int idx) {
	// ó�� �� ���� ũ�� ���
	int cnt = 1;
	visited2[r][c] = 1;
	for (int i = 0; i < 4; i++) {
		int nx = r + dx[i];
		int ny = c + dy[i];
		if (nx < 0 || nx >= n || ny < 0 || ny >= m) continue;
		if (visited2[nx][ny]) continue;
		if (map[r][c][i]) {
			if (flag) continue;
			// �� �� ���� ���� ���̸� X -> �ѹ��� ������ dfs �� �� �� ��ħ
			if (visited[nx][ny] == idx) continue;
			int cnt2 = dfs2(nx, ny, 1, idx);
			// �� ���� �� �� �� ���� ū ũ�� ���
			best = best < cnt2 ? cnt2 : best;
		}
		else {
			cnt += dfs2(nx, ny, flag, idx);
		}
	}
	return cnt;
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie();
	cout.tie();

	cin >> m >> n;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			int x;
			cin >> x;
			// ���ϵ��� ������ ���� ������ 1, �ƴϸ� 0
			for (int k = 0; k < 4; k++) {
				map[i][j][k] = x % 2;
				x /= 2;
			}
		}
	}

	// �� �濡 ��ȣ �ű��
	int idx = 1;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			if (visited[i][j]) continue;
			int cnt = dfs(i, j, idx);
			ans2 = ans2 < cnt ? cnt : ans2;
			ans1++;
			v.push_back({ i, j });
			idx++;
		}
	}

	int len = v.size();
	for (int i = 0; i < len; i++) {
		best = 0;
		visit_clear();
		int cnt = dfs2(v[i].first, v[i].second, 0, visited[v[i].first][v[i].second]);
		ans3 = ans3 < cnt + best ? cnt + best : ans3;
	}

	cout << ans1 << "\n" << ans2 << "\n" << ans3;

	return 0;
}