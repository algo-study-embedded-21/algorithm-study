#include <iostream>
#include <vector>
#include <queue>
using namespace std;

int n, m, x, y;
vector<int> map[100];

int bfs() {
	queue<int> q;
	int visited[100] = {0};

	q.push(x);

	while (!q.empty()) {
		int now = q.front();
		q.pop();
		for (int i = 0; i < map[now].size();i++) {
			if (visited[map[now][i]]) continue;
			q.push(map[now][i]);
			visited[map[now][i]] = visited[now] + 1;
			if (map[now][i] == y) {
				return visited[map[now][i]];
			}
		}
	}
	return -1;
}

int main()
{
	cin >> n;
	cin >> x >> y;
	cin >> m;

	for (int i = 0; i < m; i++) {
		int parent, child;
		cin >> parent >> child;
		map[parent].push_back(child);
		map[child].push_back(parent);
	}
	int a = 0;
	cout << bfs();

	return 0;
}
