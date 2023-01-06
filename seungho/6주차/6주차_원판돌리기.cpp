#include <iostream>
#include <queue>
using namespace std;

int MAP[51][51];

int N, M, T;

struct Node {
	int y;
	int x;
};

// 해당 원판 회전
void turn(int x, int d, int k) {
	for (int a = 1; a <= (N / x); a++) {
		int i = a * x;

		// MAP2에 기존 배열을 담는다
		int MAP2[51] = { 0 };
		for (int j = 0; j < M; j++) {
			MAP2[j] = MAP[i][j];
		}
		// 새로운 순서로 MAP에 담는다
		for (int j = 0; j < M; j++) {
			//         (1-d) => 시계방향,         d => 반시계방향
			int nj = (1 - d) * ((j + k) % M) + d * ((M + ((j - k) % M)) % M) ;

			MAP[i][nj] = MAP2[j];
		}
	}
}

int diry[4] = { 0,0,1,-1 };
int dirx[4] = { 1,-1,0,0 };

int flag = 0; // 인접한 같은 수가 있다면 1

// 원판 회전 후 인접한 수끼리 같은 것 지우기
void bfs(int i, int j) {
	int number = MAP[i][j];
	queue<Node> q;
	q.push({ i,j });
	int visited[51][51] = { 0 };
	visited[i][j] = 1;

	while (!q.empty()) {
		Node now = q.front();
		q.pop();
		for (int d = 0; d < 4; d++) {
			int ny = now.y + diry[d];
			int nx = now.x + dirx[d];
			if (ny<1 || ny>N) continue;
			if (nx < 0) nx += M;
			if (nx >= M) nx -= M;
			if (MAP[ny][nx] != number) continue;
			if (visited[ny][nx] == 1) continue;


			MAP[i][j] = 0;
			flag = 1;
			MAP[ny][nx] = 0;
			visited[ny][nx] = 1;
			q.push({ ny,nx });
		}
	}

}


int main() {
	ios_base::sync_with_stdio(false);
	cin.tie();
	cout.tie();

	//입력

	cin >> N >> M >> T;
	for (int i = 1; i <= N; i++) {
		for (int j = 0; j < M; j++) {
			cin >> MAP[i][j];
		}
	}

	// 회전 T번 반복
	for (int t = 0; t < T; t++) {
		int x, d, k;
		cin >> x >> d >> k;

		turn(x, d, k);
		flag = 0;
		int sum = 0;	// 남은 숫자 총합
		int cnt = 0;	// 남은 숫자 개수
		for (int i = 1; i <= N; i++) {
			for (int j = 0; j < M; j++) {
				if (MAP[i][j] == 0) continue;
				sum += MAP[i][j];
				cnt++;
				bfs(i, j);
			}
		}

		// 원판에 인접한 같은 수가 없는 경우
		if (flag == 0) {
			int mean = sum / cnt;  // 평균
			for (int i = 1; i <= N; i++) {
				for (int j = 0; j < M; j++) {
					if (MAP[i][j] == 0) continue;
					if (MAP[i][j] * cnt > sum) MAP[i][j]--;
					else if (MAP[i][j] * cnt < sum) MAP[i][j]++;
				}
			}
		}
	}

	// T번 회전 후 원판에 적힌 수 합 출력
	int ans = 0;
	for (int i = 1; i <= N; i++) {
		for (int j = 0; j < M; j++) {
			if (MAP[i][j] == 0) continue;
			ans += MAP[i][j];
		}
	}
	cout << ans;
	return 0;
}
