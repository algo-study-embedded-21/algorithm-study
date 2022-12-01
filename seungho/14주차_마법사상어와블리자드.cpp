#include <iostream>
#include <queue>
using namespace std;

int N, M;
int MAP[51][51];

int diry[4] = { 0,1,0,-1 };
int dirx[4] = { -1,0,1,0 };

int dindex[4] = { 3,1,0,2 };

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie();
	cout.tie();

	cin >> N >> M;
	int sy = (N + 1) / 2;
	int sx = sy;
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			cin >> MAP[i][j];
		}
	}

	int cnt[4] = { 0,0,0,0 };

	for (int m = 0; m < M; m++) {
		int d, s;
		cin >> d >> s;
		d = dindex[d - 1];
		// 1. 얼음 파편 던져 구슬 파괴
		for (int i = 1; i <= s; i++) {
			int ny = sy + i * diry[d];
			int nx = sx + i * dirx[d];
			if (ny <= 0 || nx <= 0 || ny > N || nx > N) break;
			MAP[ny][nx] = 0;
		}

		// 2. 빈 칸으로 구슬 이동
		// 3. 4개이상 연속하는 구슬 폭발
		// 4. 구슬 이동
		// 5. 반복

		while (true) {
			int bflag = 0;
			int dd = 0;		// 처음 이동 방향
			int dist = 1;	// 처음 이동 거리
			int dflag = 0;	// 2번마다 거리 1 증가
			int flag = 0;
			int ny = sy;
			int nx = sx;
			queue<int> q;
			queue<int> qCheck;

			while (true) {
				for (int i = 0; i < dist; i++) {
					ny += diry[dd];
					nx += dirx[dd];
					if (ny <= 0 || nx <= 0 || ny > N || nx > N) {
						flag = 1;
						break;
					}
					if (MAP[ny][nx] == 0) continue;
					if (!qCheck.empty()) {
						if (qCheck.front() != MAP[ny][nx]) {
							// 같은 번호 4개 이상 쌓였으면 폭발
							if (qCheck.size() >= 4) {
								bflag = 1;
								// 1,2,3번 구슬 폭발 개수 카운트
								if (qCheck.front() <= 3) {
									cnt[qCheck.front()] += qCheck.size();
								}
								while (!qCheck.empty()) qCheck.pop();
							}
							else {
								while (!qCheck.empty()) {
									q.push(qCheck.front());
									qCheck.pop();
								}
							}
						}
					}
					qCheck.push(MAP[ny][nx]);
					MAP[ny][nx] = 0;
				}
				if (flag) break;
				dd++;
				dd %= 4;
				dflag++;
				if (dflag > 1) {
					dflag = 0;
					dist++;
				}
			}
			// qCheck에 남은 구슬 check
			if (!qCheck.empty()) {
				if (qCheck.size() >= 4) {
					// 1,2,3번 구슬 폭발 개수 카운트
					if (qCheck.front() <= 3) {
						cnt[qCheck.front()] += qCheck.size();
					}
					while (!qCheck.empty()) qCheck.pop();
				}
				else {
					while (!qCheck.empty()) {
						q.push(qCheck.front());
						qCheck.pop();
					}
				}
			}

			// MAP에 구슬 배치
			dd = 0;		// 처음 이동 방향
			dist = 1;	// 처음 이동 거리
			dflag = 0;	// 2번마다 거리 1 증가
			ny = sy;
			nx = sx;
			flag = 0;
			while (true) {
				for (int i = 0; i < dist; i++) {
					ny += diry[dd];
					nx += dirx[dd];
					if (ny <= 0 || nx <= 0 || ny > N || nx > N) {
						flag = 1;
						break;
					}
					if (q.empty()) {
						flag = 1;
						break;
					}
					MAP[ny][nx] = q.front();
					q.pop();
				}

				if (flag) break;

				dd++;
				dd %= 4;
				dflag++;
				if (dflag > 1) {
					dflag = 0;
					dist++;
				}
			}
			if (bflag == 0) break;
		}

		// 6. 구슬 변화
		int bflag = 0;
		int dd = 0;		// 처음 이동 방향
		int dist = 1;	// 처음 이동 거리
		int dflag = 0;	// 2번마다 거리 1 증가
		int flag = 0;
		int ny = sy;
		int nx = sx;
		queue<int> q;
		queue<int> qCheck;

		while (true) {
			for (int i = 0; i < dist; i++) {
				ny += diry[dd];
				nx += dirx[dd];
				if (ny <= 0 || nx <= 0 || ny > N || nx > N) {
					flag = 1;
					break;
				}
				if (MAP[ny][nx] == 0) continue;
				if (!qCheck.empty()) {
					if (qCheck.front() != MAP[ny][nx]) {
						q.push(qCheck.size());
						q.push(qCheck.front());
						while (!qCheck.empty()) qCheck.pop();
					}
				}
				qCheck.push(MAP[ny][nx]);
				MAP[ny][nx] = 0;
			}

			if (flag) break;
			dd++;
			dd %= 4;
			dflag++;
			if (dflag > 1) {
				dflag = 0;
				dist++;
			}
		}
		if (!qCheck.empty()) {
			q.push(qCheck.size());
			q.push(qCheck.front());
		}
		while (!qCheck.empty()) qCheck.pop();

		// 변화한 구슬 넣기
		bflag = 0;
		dd = 0;		// 처음 이동 방향
		dist = 1;	// 처음 이동 거리
		dflag = 0;	// 2번마다 거리 1 증가
		flag = 0;
		ny = sy;
		nx = sx;
		while (true) {
			int asdf = 1;
			for (int i = 0; i < dist; i++) {
				ny += diry[dd];
				nx += dirx[dd];
				if (ny <= 0 || nx <= 0 || ny > N || nx > N) {
					flag = 1;
					break;
				}
				if (q.empty()) {
					flag = 1;
					break;
				}
				MAP[ny][nx] = q.front();
				q.pop();
			}

			if (flag) break;
			dd++;
			dd %= 4;
			dflag++;
			if (dflag > 1) {
				dflag = 0;
				dist++;
			}
		}
	}

	cout << cnt[1] + 2 * cnt[2] + 3 * cnt[3];

	return 0;
}
