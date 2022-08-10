/*

backtracking + dat로 풀 수 있을 것 같다.
1. 치킨집 조합을 구한 뒤
2. 최소 치킨 거리를 구할 때 dat 사용

*/

#include <iostream>
#include <vector>
using namespace std;

struct Node {
	int x;
	int y;
};

vector<Node> home;
vector<Node> chicken;
vector<int> arr;

int n, m;
int chArr[14];
int minDist = 2134567890;

void getChickenDistance() {
	// 각 집의 치킨 거리 초기화
	int dist[100];
	for (int i = 0; i < 100; i++) dist[i] = 2134567890;

	// 각 집마다 가장 짧은 치킨 거리 저장
	int len = home.size();
	for (int i = 0; i < len; i++) {
		Node now = home[i];
		for (int a : arr) {
			Node c = chicken[a];

			int d = abs(now.x - c.x) + abs(now.y - c.y);

			if (d < dist[i]) dist[i] = d;
		}
	}

	// 치킨 거리의 합
	int cnt = 0;
	for (int i = 0; i < len; i++) {
		cnt += dist[i];
	}

	// 최소 치킨 거리 저장
	minDist = min(minDist, cnt);
}

void dfs(int start, int depth){
	if (depth == m) {
		getChickenDistance();
		return;
	}

	int len = chicken.size();
	// 치킨 집을 고르는 순서는 상관 없고
	// 중복되지 않게 골라야 함
	for (int i = start; i < len; i++) {
		if (chArr[i]) continue;
		chArr[i] = 1;
		arr.push_back(i);
		dfs(i + 1, depth + 1);
		arr.pop_back();
		chArr[i] = 0;
	}
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie();
	cout.tie();

	// 입력
	cin >> n >> m;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			int a;
			cin >> a;
			if (a == 1) home.push_back({ i, j });
			if (a == 2) chicken.push_back({ i, j });
		}
	}
	
	// 치킨 집 조합 및 치킨 거리 구하기
	dfs(0, 0);
	cout << minDist;

	return 0;
}