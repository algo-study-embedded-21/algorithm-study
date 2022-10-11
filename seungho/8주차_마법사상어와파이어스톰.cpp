#include <iostream>
using namespace std;

int N, Q;
int MAP[100][100];
int MAP2[100][100] = { 0 };
int MAPid[100][100];

int msize;

int diry[4] = { 0,0,1,-1 };
int dirx[4] = { 1,-1,0,0 };

void turn(int L) {
	int bsize = 1 << L;


	// 맵 복사
	for (int i = 0; i < msize; i++) {
		for (int j = 0; j < msize; j++) {
			MAP2[i][j] = MAP[i][j];
		}
	}

	// 구역 별 회전
	for (int by = 0; by < msize / bsize; by++) {
		for (int bx = 0; bx < msize / bsize; bx++) {
			for (int i = 0; i < bsize; i++) {
				for (int j = 0; j < bsize; j++) {
					MAP[j + by * bsize][bsize - 1 - i + bx * bsize] = MAP2[i + by * bsize][j + bx * bsize];
				}
			}
		}
	}
}

void melt() {
	// 맵 복사
	for (int i = 0; i < msize; i++) {
		for (int j = 0; j < msize; j++) {
			MAP2[i][j] = MAP[i][j];
		}
	}

	for (int i = 0; i < msize; i++) {
		for (int j = 0; j < msize; j++) {
			// 얼음이 없다면 continue
			if (MAP2[i][j] == 0) continue;

			int cnt = 0;
			for (int d = 0; d < 4; d++) {
				int ny = i + diry[d];
				int nx = j + dirx[d];
				// 맵을 벗어나면 cnt+1
				if (ny < 0 || nx < 0 || ny >= msize || nx >= msize) {
					cnt++;
				}
				// 얼음이 없으면 cnt+1
				else if (MAP2[ny][nx] == 0) cnt++;
			}
			// 인접한 칸 중 얼음이 없는 칸이 두 개 이상이면 얼음 양 -1
			if (cnt > 1) {
				MAP[i][j]--;
			}
		}
	}
}

int parent[10000] = { 0 };
int groupsize[10000] = { 0 };

int Find(int node) {
	if (node == parent[node]) {
		return node;
	}
	return parent[node] = Find(parent[node]);
}

void Union(int a, int b) {
	int pa = Find(a);
	int pb = Find(b);
	if (pa == pb) return;

	parent[pb] = pa;
	groupsize[pa] += groupsize[pb];
	groupsize[pb] = 0;
}

int main() {
	cin >> N >> Q;

	msize = 1 << N;
	cout << msize << "\n";

	for (int i = 0; i < msize; i++) {
		for (int j = 0; j < msize; j++) {
			cin >> MAP[i][j];
		}
	}

	// 파이어스톰 Q번 시전
	for (int i = 0; i < Q; i++) {
		int L;
		cin >> L;

		// 회전
		turn(L);

		// 얼음 양 감소
		melt();
	}
	cout << "\n";
	for (int i = 0; i < msize; i++) {
		for (int j = 0; j < msize; j++) {
			cout << MAP[i][j] << " ";
		}
		cout << "\n";
	}

	// 덩어리 찾기

	// 칸마다 parent 설정
	int n = 0;
	for (int i = 0; i < msize; i++) {
		for (int j = 0; j < msize; j++) {
			parent[n] = n;
			MAPid[i][j] = n;
			groupsize[n] = 1;
			n++;
		}
	}

	int sumice = 0; // 남은 얼음 합

	int maxsize = -1;  // 얼음 덩어리 최대 크기

	// 인접한 얼음 칸 Union
	for (int i = 0; i < msize; i++) {
		for (int j = 0; j < msize; j++) {
			// 얼음 없으면 continue
			if (MAP[i][j] == 0) {
				groupsize[MAPid[i][j] = 0];
				continue;
			}

			// 남은 얼음 합 추가
			sumice += MAP[i][j];

			for (int d = 0; d < 4; d++) {
				int ny = i + diry[d];
				int nx = j + dirx[d];
				if (ny < 0 || nx < 0 || ny >= msize || nx >= msize) continue;

				// 인접한 칸에 얼음이 있다면 Union
				if (MAP[ny][nx] > 0) Union(MAPid[i][j], MAPid[ny][nx]);

				// 얼음 덩어리 최대 크기 갱신
				maxsize = max(maxsize, groupsize[Find(MAPid[i][j])]);
			}
		}
	}
	for (int i = 0; i < msize * msize; i++) {
		cout << groupsize[i] << " ";
	}
	cout << "\n";

	cout << sumice;
	cout << "\n";
	cout << maxsize;

	return 0;
}
