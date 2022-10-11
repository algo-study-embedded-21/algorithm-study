#include <iostream>
#include <cmath>
#include <vector>
using namespace std;

int map[100][100];
int visited[100][100];
int N, Q, L;

int dx[] = { 1, 0, -1, 0 };
int dy[] = { 0, 1, 0, -1 };

int answer;
int max_size;

// ���� ���� 90�� ȸ��
void rotate(int x, int y, int n)
{
	vector<vector<int>> v(n, vector<int>(n));
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			v[j][n - i - 1] = map[i + x][j + y];
		}
	}
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			map[i + x][j + y] = v[i][j];
		}
	}
}

void check_ice(int n)
{
	// ���ÿ� �����ؾ� �ϹǷ� 1 ���� ��ǥ ����
	vector<pair<int, int>> v;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (map[i][j] < 1) continue;
			int cnt = 0;
			for (int k = 0; k < 4; k++) {
				if (cnt >= 3) break;
				int nx = i + dx[k];
				int ny = j + dy[k];

				if (nx < 0 || nx >= n || ny < 0 || ny >= n) continue;
				if (map[nx][ny] <= 0) continue;
				cnt++;
			}
			if (cnt < 3) v.push_back({ i, j });
		}
	}
	for (auto p : v) {
		map[p.first][p.second]--;
	}
}

void firestorm()
{
	// 90�� ȸ��
	int len = pow(2, N);
	int step = pow(2, L);
	for (int i = 0; i < len; i += step) {
		for (int j = 0; j < len; j += step) {
			rotate(i, j, step);
		}
	}
	
	// ���� ���̱�
	check_ice(len);	
}

// ���� ĭ�� ��, ������ �� ��ȯ
pair<int, int> dfs(int x, int y, int n)
{
	visited[x][y] = 1;
	int ans = 1;
	int total = map[x][y];

	for (int i = 0; i < 4; i++) {
		int nx = x + dx[i];
		int ny = y + dy[i];

		if (nx < 0 || nx >= n || ny < 0 || ny >= n) continue;
		if (visited[nx][ny]) continue;
		if (map[nx][ny] < 1) continue;
		pair<int, int> next = dfs(nx, ny, n);
		ans += next.first;
		total += next.second;
	}
	return {ans, total};
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie();
	cout.tie();

	// �ʱ�ȭ
	cin >> N >> Q;
	int len = pow(2, N);
	for (int i = 0; i < len; i++) {
		for (int j = 0; j < len; j++) {
			cin >> map[i][j];
		}
	}

	// Q�� ȸ��
	for (int i = 0; i < Q; i++) {
		cin >> L;
		firestorm();
	}

	// ���� ĭ ���ϱ�
	for (int i = 0; i < len; i++) {
		for (int j = 0; j < len; j++) {
			if (map[i][j] < 1) continue;
			if (visited[i][j]) continue;
			pair<int, int> p = dfs(i, j, len);
			answer += p.second;
			max_size = max(max_size, p.first);
		}
	}

	cout << answer << "\n";
	cout << max_size;

	return 0;
}