#include <iostream>
#include <vector>
#include <queue>
using namespace std;

int N, M, D;
int MAP[15][15];
int enemies = 0;
vector <int> archer;
int ans = 0;

int c = 0;

struct Node {
	int y; int x;
};

int diry[4] = { 0,-1,1,0 };
int dirx[4] = { -1,0,0,1 };

void play() {
	int score = 0;
	int COPY[15][15] = { 0 };

	// 맵 복사
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			COPY[i][j] = MAP[i][j];
		}
	}

	while (true) {
		vector<Node> attack_list;

		// 모든 궁수 동시에 공격		
		for (int a = 0; a < archer.size(); a++) {
			queue<Node> q;
			int visited[15][15] = { 0 };
			q.push({ N - 1, archer[a] });
			if(COPY[N-1][archer[a]]) {
				attack_list.push_back({ N-1,archer[a]});
				continue;
			}
			visited[N - 1][archer[a]] = 1;
			bool attack = false;

			while (!q.empty() && !attack) {
				Node now = q.front();
				q.pop();

				// 공격 사거리보다 멀면 break
				if (visited[now.y][now.x] == D) break;
				for (int d = 0; d < 4; d++) {
					int ny = now.y + diry[d];
					int nx = now.x + dirx[d];
					if (ny < 0 || nx < 0 || ny >= N || nx >= M) continue;
					if (visited[ny][nx] > 0) continue;

					// 사거리 안에 적 찾으면 제거리스트에 넣고 break
					if (COPY[ny][nx]) {
						attack_list.push_back({ ny,nx });
						attack = true;
						break;
					}
					q.push({ ny,nx });
					visited[ny][nx] = visited[now.y][now.x] + 1;
				}
			}
		}

		// 공격당할 리스트에 있는 적 제거
		for (int l = 0; l < attack_list.size(); l++) {
			Node now = attack_list[l];
			if (COPY[now.y][now.x] == 0) continue;
			COPY[now.y][now.x] = 0;
			score++;
		}

		// 적 한 칸 씩 이동
		// 남는 적 없으면 break
		int cnt = 0;
		for (int i = N - 1; i >= 0; i--) {
			for (int j = 0; j < M; j++) {
				if (COPY[i][j]) {
					COPY[i][j] = 0;
					if (i + 1 == N) continue;
					COPY[i + 1][j] = 1;
					cnt++;
				}
			}
		}
		if (cnt == 0) break;
	}

	// 제거할 수 있는 적 최대 수 갱신
	ans = max(ans, score);
}

void dfs(int level, int p) {
	if (level == 3) {
		c++;
		play();
		return;
	}

	for (int i = p + 1; i < M; i++) {
		archer.push_back(i);
		dfs(level + 1, i);
		archer.pop_back();
	}
}


int main()
{
	cin >> N >> M >> D;
	
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			cin >> MAP[i][j];
			if (MAP[i][j]) enemies++;
		}
	}

	dfs(0, -1);

	cout << ans;

	return 0;
}
