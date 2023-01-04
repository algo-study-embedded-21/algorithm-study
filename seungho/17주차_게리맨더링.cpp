#include <iostream>
using namespace std;

int N;
int population[11];
int MAP[11][11];
int Group[11];
int possible = 0;
int ans = 2134567890;

// Union Find
int parent[11];

int Find(int node) {
	if (node == parent[node]) return node;
	return parent[node] = Find(parent[node]);
}

void Union(int a, int b) {
	int pa = Find(a);
	int pb = Find(b);
	if (pa == pb) return;
	parent[pb] = pa;
}

void dfs(int level) {
	if (level > N) {
		for (int i = 1; i <= N; i++) {

		}
		return;
	}

	for (int i = 1; i < 3; i++) {
		Group[level] = i;
		dfs(level + 1);
	}
}

void dfs(int level) {
	if (level > N) {
		int cntGroup[3] = {0};
		int GrpPop[3] = { 0 };

		// 가능한 방법인지 확인
		for (int i = 1; i <= N; i++) {
			GrpPop[Group[i]] += population[i];
			for (int j = 1; j <= N; j++) {
				if (!MAP[i][j]) continue;	// 두 선거구가 연결되어 있지 않으면 continue
				if (j == i) continue;		// 같은 번호이면 continue
				
				// 두 선거구가 연결되어 있고 같은 구역으로 나눠진 경우
				if (Group[i] == Group[j]) {	
					cntGroup[Group[i]]++;
					break;
				}
			}
		}
		if (cntGroup[1] + cntGroup[2] >= N - 1) {
			possible = 1;
			ans = min(ans, abs(GrpPop[1] - GrpPop[2]));
		}
		return;
	}

	for (int i = 1; i <= 2; i++) {
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

	if (N == 2) return abs(population[1] - population[2]);

	for (int i = 1; i <= N; i++) {
		int num;
		cin >> num;

		for (int j = 0; j < num; j++) {
			int area;
			cin >> area;
			MAP[i][area] = 1;
		}
	}
	
	dfs(1);

	return 0;
}
