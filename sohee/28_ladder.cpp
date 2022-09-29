#include <iostream>
#include <vector>
using namespace std;

int answer = -1;
// �ִ� 10���� ���� ��, 30���� ���� ��
vector<vector<int>> v(11, vector<int>(31, 0));
int n, m, h;

int check() {
	for (int i = 1; i <= n; i++) {
		int ladder = i;
		int idx = 1;
		while (idx <= h) {
			if (v[ladder][idx] != 0) ladder = v[ladder][idx];
			idx++;
		}
		// ���������� ���������� ���� ��ȣ�� ������ Ȯ��
		if (i != ladder) return 0;
	}
	return 1;
}

void dfs(int level, int start_x, int start_y) {
	if (level > 3) return;

	if (check()) {
		if (answer == -1) answer = level;
		else answer = min(answer, level);
		// ���̰� �� ���� ���� Ȯ���� �ʿ� ����
		return;
	}

	for (int i = start_x; i < n; i++) {
		int j = 1;
		if (i == start_x) j = start_y;
		for (j; j <= h; j++) {
			// ���� ���μ��̳� ������ ���μ��� �̹� ����� ���� ���� �ִٸ� pass
			if (v[i][j] != 0 || v[i+1][j] != 0) continue;
			v[i][j] = i + 1;
			v[i + 1][j] = i;

			int next_y = j == h ? 1 : j + 1;
			int next_x = next_y == 1 ? i + 1 : i;

			dfs(level + 1, next_x, next_y);

			v[i][j] = 0;
			v[i + 1][j] = 0;
		}
	}
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie();
	cout.tie();
	
	cin >> n >> m >> h;
	for (int i = 0; i < m; i++) {
		int a, b;
		cin >> a >> b;
		v[b][a] = b + 1;
		v[b + 1][a] = b;
	}

	dfs(0, 1, 1);

	cout << answer;

	return 0;
}