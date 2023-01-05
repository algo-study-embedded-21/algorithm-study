#include <iostream>
#include <cstring>
using namespace std;

int N;
int population[11];
int MAP[11][11];
int Group[11];
int possible = 0;
int ans = 2134567890;

// Union Find
int parent[11];
int groupCnt[11];

int Find(int node) {
	if (node == parent[node]) return node;
	return parent[node] = Find(parent[node]);
}

void Union(int a, int b) {
	int pa = Find(a);
	int pb = Find(b);
	if (pa == pb) return;
	parent[pb] = pa;
	groupCnt[pa] += groupCnt[pb];
	groupCnt[pb] = 0;
}

void dfs(int level) {
	if (level > N) {
		// 가능한 방법인지 확인
		for (int i = 1; i <= N; i++) {
			parent[i] = i;
		}
		memset(groupCnt, 1, sizeof(groupCnt));
		int grpPop[3] = { 0 };
		for (int i = 1; i <= N; i++) {
			for (int j = 1; j <= N; j++) {
				if (MAP[i][j] && Group[i] == Group[j]) {
					Union(i, j);
				}
			}
			grpPop[Group[i]] += population[i];
		}
		int cntgroups = 0;
		for (int i = 1; i <= N; i++) {
			if (groupCnt[i] > 0) cntgroups++;
		}

		if (cntgroups == 2) {
			possible = 1;
			ans = min(ans, abs(grpPop[1] - grpPop[2]));
		}
		return;
	}
	for (int i = 1; i < 3; i++) {
		Group[level] = i;
		dfs(level + 1);
	}
}

int main()
{
	// dfs로 1/2 그룹으로 구분
	// 두 그룹이 각각 모두 연결되어 있는지 확인

	cin >> N;
	for (int i = 1; i <= N; i++) {
		cin >> population[i];
	}

	for (int i = 1; i <= N; i++) {
		int num;
		cin >> num;

		for (int j = 0; j < num; j++) {
			int area;
			cin >> area;
			MAP[i][area] = 1;
		}
	}
	if (N == 2) {
		cout << abs(population[1] - population[2]);
		return 0;
	}

	dfs(1);
	if (possible) cout << ans;
	else cout << -1;
	return 0;
}
