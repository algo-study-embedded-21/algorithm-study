#include <iostream>
#include <queue>
using namespace std;

struct Node {
	int m;
	int s;
	int d;
};

queue<Node> MAP[51][51];
queue<Node> MAP2[51][51];
int dirMap[51][51] = { 0 };

int diry[8] = { -1,-1,0,1,1,1,0,-1 };
int dirx[8] = { 0,1,1,1,0,-1,-1,-1 };

int d1[4] = { 0, 2, 4, 6 };
int d2[4] = { 1,3,5,7 };

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie();
	cout.tie();

	// 입력
	int N, M, K;
	cin >> N >> M >> K;
	for (int i = 0; i < M; i++) {
		int r, c, m, s, d;
		cin >> r >> c >> m >> s >> d;
		MAP[r][c].push({ m,s,d });
	}

	// K번 반복
	for (int k = 0; k < K; k++) {
		// 모든 파이어볼 이동
		for (int i = 1; i <= N; i++) {
			for (int j = 1; j <= N; j++) {
				while (!MAP[i][j].empty()) {
					Node now = MAP[i][j].front();
					MAP[i][j].pop();
					int ni = i;
					int nj = j;
					for (int l = 0; l < now.s; l++) {
						ni += diry[now.d];
						nj += dirx[now.d];
						if (ni < 1) ni = N;
						else if (ni > N) ni = 1;
						if (nj < 1) nj = N;
						else if (nj > N) nj = 1;
					}

					// MAP2의 새로운 위치의 큐에 푸시
					MAP2[ni][nj].push({ now.m,now.s,now.d });
				}
			}
		}

		for (int i = 1; i <= N; i++) {
			for (int j = 1; j <= N; j++) {
				if (MAP2[i][j].empty()) continue;
				// 현재 칸에 파이어볼이 하나만 있다면 그대로 MAP에 넣는다
				if (MAP2[i][j].size() == 1) {
					Node now = MAP2[i][j].front();
					MAP2[i][j].pop();
					MAP[i][j].push({ now.m,now.s, now.d });
				}
				else {
					int nm = 0;
					int ns = 0;
					int nd = -1;
					int cntball = MAP2[i][j].size();
					while (!MAP2[i][j].empty()) {
						Node now = MAP2[i][j].front();
						MAP2[i][j].pop();
						nm += now.m;
						ns += now.s;
						if (nd == -1) nd = now.d % 2;
						else if (nd == 2) continue;
						else if (nd == now.d % 2) continue;
						else nd = 2;
					}
					for (int f = 0; f < 4; f++) {
						// 질량 계산 결과가 0이면 파이어볼 소멸
						if (nm / 5 == 0) continue;

						// 파이어볼들의 방향이 모두 홀수이거나 짝수가 아닌 경우
						if (nd == 2) {
							MAP[i][j].push({ nm / 5, ns / cntball, d2[f] });
						}
						// 파이어볼들의 방향이 모두 홀수이거나 모두 짝수인 경우
						else {
							MAP[i][j].push({ nm / 5, ns / cntball, d1[f] });
						}
					}
				}
			}
		}
	}
	int ans = 0;

	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			while (!MAP[i][j].empty()) {
				Node now = MAP[i][j].front();
				MAP[i][j].pop();
				ans += now.m;
			}
		}
	}

	cout << ans;

	return 0;
}
