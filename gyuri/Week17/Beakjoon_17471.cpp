#include <iostream>
#include <cstring>
#include <vector>
#define endl '\n'

using namespace std;

int N;
int cnt[15], areas[15];
vector<int> graph[15];
int visited[15];
int answer = 1e9;

// 연결되어 있는지 확인
void checkConnect(int now) {
	
	for (auto next : graph[now]) {

		// 이미 방문한 지역일 때 (선거구 배정되었다면)
		if (visited[next] != 0) continue;

		// 인접하지만 다른 선거구일 때
		if (areas[now] != areas[next]) continue;

		// 인접하면서 같은 선거구일 때
		if (areas[now] == areas[next]) {
			visited[next] = areas[now]; // 선거구 번호 저장
			checkConnect(next);
		}
	}
}

void DFS(int level) {

	if (level == N) {
		
		memset(visited, 0, sizeof(visited)); // visited 초기화

		int areasCnt = 0;
		for (int i = 0; i < N; i++) {
			if (visited[i] > 0) continue; // 이미 방문한 지역이면
			checkConnect(i);
			areasCnt++; 
		}

		if (areasCnt == 2) {

			int area1 = 0, area2 = 0;

			for (int i = 0; i < N; i++) {
				if (visited[i] == 1) area1 += cnt[i];
				if (visited[i] == 2) area2 += cnt[i];
			}

			int sub = abs(area1 - area2);
			answer = min(answer, sub);
		}
		else answer = -1;
		return;
	}

	// 재귀 구성
	for (int i = 1; i <= 2; i++) { // 선거구 1, 2
		areas[level] = i;
		DFS(level + 1);
		areas[level] = 0;
	}
	
}

void Input() {

	cin >> N;

	for (int i = 0; i < N; i++) {
		cin >> cnt[i];
	}

	for (int i = 0; i < N; i++) {

		int c;
		cin >> c;

		for (int j = 0; j < c; j++) {
			int area;
			cin >> area;
			graph[i].push_back(area);
		}
	}

}

void Output() {

	cout << answer;

}

int main() {

	ios_base::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);

	Input();
	DFS(0);
	Output();

}