#include <iostream>
#include <queue>
#include <string.h>
#include <typeinfo>
using namespace std;

int N, M;

struct Node {
	int y;
	int x;
};

int MAP[21][21];
int visited[21][21];
int rainbow[500] = { 0 };

vector<Node> v[500];

int ans = 0;

int diry[4] = { 0,0,1,-1 };
int dirx[4] = { 1,-1,0,0 };

int maxgroupsize;	// 블록 그룹 최대 크기
int maxgroupindex;

void bfs(int index, int sy, int sx) {
	queue<Node> q;
	q.push({ sy,sx });
	visited[sy][sx] = 1;
	v[index].push_back({ sy,sx });

	maxgroupsize = 1;
	maxgroupindex = 0;

	while (!q.empty()) {
		Node now = q.front();
		q.pop();
		for (int i = 0; i < 4; i++) {
			int ny = now.y + diry[i];
			int nx = now.x + dirx[i];
			if (ny<1 || nx<1 || ny>N || nx>M) continue;
			if (visited[ny][nx] > 0) continue;
			if (MAP[ny][nx] == MAP[sy][sx]) {	// 같은 색 일반블록인 경우
				visited[ny][nx] = 1;
				q.push({ ny,nx });
				v[index].push_back({ ny, nx });	
			}

			// 무지개색 블록인 경우
			if (MAP[ny][nx] == 0) {
				visited[ny][nx] = 1;
				q.push({ ny,nx });
				v[index].push_back({ ny, nx });
				rainbow[index]++;
			}
		}
	}
	// 그룹 찾을 때 마다 그룹 크기 최대값, 그 그룹의 무지개블록 수 갱신
	int size = v[index].size();
	// 그룹 크기가 현재 최대값보다 큰 경우
	cout << v[index].size()<<"\n";
	cout << maxgroupsize<< "\n";
	if (v[index].size() > maxgroupsize) {
		maxgroupsize = v[index].size();
		maxgroupindex = index;
	}

	// 그룹 크기가 현재 최대값과 같은 경우
	if (v[index].size() == maxgroupsize) {
		// 무지개블록수 같은 경우 더 나중에 확인한 그룹(행,열 큰 그룹)으로 갱신
		if (rainbow[index] >= rainbow[maxgroupindex]) {	
			maxgroupsize = v[index].size();
			maxgroupindex = index;
		}
	}
}

void gravity() {
	for (int i = 1; i <= N; i++) {
		int low = N;
		for (int j = N; j > 0; j--) {
			if (MAP[j][i] == -1) {
				if (j == 1) continue;
				low = j - 1;
			}
			if (MAP[j][i] >= 0) {
				int temp = MAP[low][i];
				MAP[low][i] = MAP[j][i];
				MAP[j][i] = temp;
				low--;
			}
		}
	}
}


int autoplay() {
	// rainbow 초기화
	memset(rainbow, 0, sizeof(rainbow));

	// visited 초기화
	memset(visited, 0, sizeof(visited));

	// 벡터 초기화
	for (int i = 0; i < 500; i++) {
		v[i].clear();
	}

	// 블록 그룹 찾기
	// 0번 노드(1,1)부터 돌며 일반 블럭을 찾는다
	int index = 0;
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			if (visited[i][j] != 0) continue;

			// 일반블록이면 bfs로 해당 블록 기준의 유니온 찾는다
			if (MAP[i][j] > 0) {
				bfs(index, i, j);
				index++;
			}
		}
	}
	// 크기가 2 이상인 블록 그룹이 없다면 0 리턴
	if (maxgroupsize < 2) return 0;

	// 찾은 그룹 중 크기가 가장 큰 블록 그룹의 블록 제거(-2로)
	for (int i = 0; i < v[maxgroupindex].size(); i++) {
		Node now = v[maxgroupindex][i];
		MAP[now.y][now.x] = -2;
	}

	// 점수 획득
	ans += maxgroupsize * maxgroupsize;

	// 중력 작용
	gravity();

	// 반시계 90도 회전
	int MAP2[21][21] = { 0 };
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			MAP2[N + 1 - j][i] = MAP[i][j];
		}
	}
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			MAP[i][j] = MAP2[i][j];
		}
	}
	// 중력 작용
	gravity();

	return 1;
}

int main() {
	// 입력
	cin >> N >> M;
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			cin >> MAP[i][j];
		}
	}

	// 블록 그룹이 없을때까지 반복
	while (true) {
		int result = autoplay();
		if (result == 0) break;
	}
	cout << ans;
	return 0;
}
