/*

1. Union-Find �̿��� ���� ���ϱ�
2. ������ �ϳ� �̻� �����Ѵٸ� �α� ������� ���� �� days++;
3. ������ ���̻� �������� �ʴ´ٸ� break;

*/

#include <iostream>
#include <vector>
using namespace std;

int parents[2555];
int map[2555];
int n, l, r;
int days = 0;

// �α� ���� ���ϴµ� ������ �߿����� ������
// ������, �Ʒ��ʸ� ��
int dx[] = { 1, 0};
int dy[] = { 0, 1};

struct Node {
	int x;
	int y;
	int cnt;
};

vector<Node> v[2555];

int Find(int now) {
	if (parents[now] == now) return now;
	return parents[now] = Find(parents[now]);
}

void Union(int a, int b) {
	int pa = Find(a);
	int pb = Find(b);

	if (pa == pb) return;

	parents[pb] = pa;
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie();
	cout.tie();

	cin >> n >> l >> r;

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cin >> map[i * n + j];
		}
	}

	while (1) {

		for (int i = 0; i < n * n; i++) {
			parents[i] = i;
			v[i].clear();
		}

		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				for (int k = 0; k < 2; k++) {
					int nx = i + dx[k];
					int ny = j + dy[k];

					if (nx < 0 || nx >= n || ny < 0 || ny >= n) continue;
					if (abs(map[i * n + j] - map[nx * n + ny]) < l || abs(map[i * n + j] - map[nx * n + ny]) > r) continue;
					if (Find(i * n + j) == Find(nx * n + ny)) continue;

					Union(i * n + j, nx * n + ny);
				}
			}
		}

		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				v[Find(i * n + j)].push_back({ i, j, map[i * n +j] });
			}
		}

		int flag = 1;
		for (int i = 0; i < n * n; i++) {
			int len = v[i].size();
			
			if (len > 1) flag = 0;
			else continue;

			int val = 0;
			for (int j = 0; j < len; j++) {
				Node now = v[i][j];
				val += map[now.x * n + now.y];
			}

			int mean = val / len;

			for (int j = 0; j < len; j++) {
				Node now = v[i][j];
				map[now.x * n + now.y] = mean;
			}
		}

		if (flag) break;

		days++;
	}

	cout << days;

	return 0;
}