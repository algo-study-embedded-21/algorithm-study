#include <iostream>
#include <vector>
#include <queue>
using namespace std;

int N, M,fuel;
int MAP[20][20];

int ty, tx;		// 택시 좌표

int diry[4] = { 0,0,1,-1 };
int dirx[4] = { 1,-1,0,0 };

struct Node {
	int y; int x;
};

vector<Node> v;

void dfs() {
	int visited[20][20] = { 0 };

	queue<Node> q;
	q.push({ ty, tx });

	while (!q.empty()) {
		Node now = q.front();
		q.pop();
		for (int d = 0; d < 4; d++) {
			int ny = now.y + diry[d];
			int nx = now.x + dirx[d];
			if (ny < 0 || nx < 0 || ny >= N || nx >= N) continue;
			if(MAP[ny][nx] )
		}
	}

}


int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie();
	cout.tie();

	cin >> N >> M >> fuel;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cin >> MAP[i][j];
		}
	}

	cin >> ty >> tx;

	for (int m = 0; m < M; m++) {
		int sy, sx, ey, ex;
		cin >> sy >> sx >> ey >> ex;
		// 손님 번호 2번 ~ M+1번
		MAP[sy][sx] = m+2;
		v.push_back({ ey,ex });
	}
	
	for (int m = 0; m < M; m++) {
		dfs();

	}



	return 0;
}
