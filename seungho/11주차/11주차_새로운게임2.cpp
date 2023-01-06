#include <iostream>
#include <vector>
#include <deque>
using namespace std;

int N, K;

struct Node {
	int n; int d;
};

vector<Node> v;

int MAP[12][12];
vector<Node> vMAP[12][12];

int diry[4] = { 0,0,-1,1 };
int dirx[4] = { 1,-1,0,0 };

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie();
	cout.tie();

	cin >> N >> K;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cin >> MAP[i][j];
		}
	}

	for (int k = 1; k <= K; k++) {
		int y, x, d;
		cin >> y >> x >> d;
		vMAP[y - 1][x - 1].push_back({ k, d - 1 });
	}

	int turn = 1;

	while (1) {
		if (turn > 1000) {
			cout << -1;
			return 0;
		}

		// 말 벡터에서 0번부터 돌면서 이동
		// 현재 말이 이동할 칸 확인
		// 움직일 말이 있는 칸에서 말 위의 모든 말을 vMAP에서 꺼낸다
		// 이동할 칸이 흰색이면 queue, 빨간색이면 stack, 파란색이면 방향 바꿔서 queue

		// 1번말부터 순서대로 이동
		for (int num = 1; num <= K; num++) {
			// 맵을 돌며 num번 말 찾기
			int flag = 0;
			int y, x, z;
			for (int i = 0; i < N; i++) {
				for (int j = 0; j < N; j++) {
					if (vMAP[i][j].empty()) continue;
					for (int k = 0; k < vMAP[i][j].size(); k++) {
						if (vMAP[i][j][k].n == num) {
							y = i;
							x = j;
							z = k;
							flag = 1;
							break;
						}
					}
					if (flag == 1)	break;
				}
				if (flag == 1) break;
			}
			int ny = y + diry[vMAP[y][x][z].d];
			int nx = x + dirx[vMAP[y][x][z].d];

			deque<Node> dq;

			while (1) {
				Node temp = vMAP[y][x].back();
				dq.push_back({ temp.n, temp.d });
				vMAP[y][x].pop_back();
				if (temp.n == num) break;
			}

			// 범위 벗어나거나 파란칸인 경우
			// 방향 반대로 바꾸기
			if (ny < 0 || nx < 0 || ny >= N || nx >= N || MAP[ny][nx] == 2) {
				switch (dq.back().d) {
				case 0:
					dq.back().d = 1;
					break;
				case 1:
					dq.back().d = 0;
					break;
				case 2:
					dq.back().d = 3;
					break;
				case 3:
					dq.back().d = 2;
					break;
				}

				ny = y + diry[dq.back().d];
				nx = x + dirx[dq.back().d];

				// 바뀐 방향으로 이동한 칸이 범위 벗어나거나 파란칸인 경우
				if (ny < 0 || nx < 0 || ny >= N || nx >= N || MAP[ny][nx] == 2) {
					while (!dq.empty()) {
						vMAP[y][x].push_back(dq.back());
						dq.pop_back();
					}
				}
				// 바뀐 방향으로 이동한 칸이 흰 칸인 경우
				else if (MAP[ny][nx] == 0) {
					while (!dq.empty()) {
						vMAP[ny][nx].push_back(dq.back());
						dq.pop_back();
					}
				}
				// 바뀐 방향으로 이동한 칸이 빨간 칸인 경우
				else if (MAP[ny][nx] == 1) {
					while (!dq.empty()) {
						vMAP[ny][nx].push_back(dq.front());
						dq.pop_front();
					}
				}
			}

			// 흰 칸인 경우
			else if (MAP[ny][nx] == 0) {
				while (!dq.empty()) {
					vMAP[ny][nx].push_back(dq.back());
					dq.pop_back();
				}
			}
			// 빨간 칸인 경우
			else if (MAP[ny][nx] == 1) {
				while (!dq.empty()) {
					vMAP[ny][nx].push_back(dq.front());
					dq.pop_front();
				}
			}

			// 한 칸에 말 4개면 리턴
			for (int i = 0; i < N; i++) {
				for (int j = 0; j < N; j++) {
					if (vMAP[i][j].size() >= 4) {
						cout << turn;
						return 0;
					}
				}
			}
		}
		turn++;
	}

	cout << turn;

	return 0;
}
