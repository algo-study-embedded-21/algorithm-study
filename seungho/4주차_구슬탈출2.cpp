#include <iostream>
#include <queue>
using namespace std;

int N, M;
string MAP[11];
int by, bx, ry, rx;

struct Node {
	int by;
	int bx;
	int ry;
	int rx;
};

int diry[4] = { 0,0,1,-1 };
int dirx[4] = { 1,-1,0,0 };

int mintry=2134567890;

int visitedr[11][11] = { 0 };
int visitedb[11][11] = { 0 };

void dfs(int level, int by, int bx, int ry, int rx) {
	
	if (level == 10 || (level>mintry)) {
		cout << "level:" << level << "by:" << by << "bx:" << bx << "ry:" << ry << "rx:" << rx << "\n";
		return;
	}

	for (int i = 0; i < 4; i++) {
		int nry = ry;
		int nrx = rx;
		int nby = by;
		int nbx = bx;

		// 빨간구슬이 더 먼저 움직이는 경우
		if(((by==ry) && ((i==0 && rx>bx) || (i == 1 && rx < bx))) || ((bx == rx) && ((i == 2 && ry > by) || (i == 3 && ry < by)))) {
			while (true) {
				nry += diry[i];
				nrx += dirx[i];
				if (visitedr[nry][nrx] > 0) break;
				// 빨간 구슬이 빠지면 최소 횟수 갱신
				if (MAP[nry][nrx] == 'O') {
					cout << "level:" << level << "by:" << by << "bx:" << bx << "ry:" << ry << "rx:" << rx << "\n";
					mintry = min(mintry, level + 1);
					return;
				}
				// 더 움직일 수 없으면 제자리
				else if (MAP[nry][nrx] != '.') {
					nry -= diry[i];
					nrx -= dirx[i];
					break;
				}
				visitedr[nry][nrx] = 1;
			}
			while (true) {
				nby = nby + diry[i];
				nbx = nbx + dirx[i];
				
				if (visitedb[nby][nbx] > 0) continue;
				visitedb[nby][nbx] = 1;

				// 파란 구슬이 빠지면 
				if (MAP[nby][nbx] == 'O') {
					return;
				}
				// 더 움직일 수 없으면 제자리
				if (MAP[nby][nbx] != '.') {
					nby -= diry[i];
					nbx -= dirx[i];
					break;
				}
			}
		}
		// 파란구슬이 더 먼저 움직이는 경우
		/*if (((by == ry) && ((i == 0 && rx < bx) || (i == 1 && rx > bx))) || ((bx == rx) && ((i == 2 && ry < by) || (i == 3 && ry > by))))*/ 
		
		// 나머지 경우
		else{
			while (true) {
				nby = nby + diry[i];
				nbx = nbx + dirx[i];
				if (visitedb[nby][nbx] > 0) continue;
				visitedb[nby][nbx] = 1;

				// 파란 구슬이 빠지면 
				if (MAP[nby][nbx] == 'O') {
					return;
				}
				// 더 움직일 수 없으면 제자리
				if (MAP[nby][nbx] != '.') {
					nby -= diry[i];
					nbx -= dirx[i];
					break;
				}
			}
			while (true) {
				nry = nry + diry[i];
				nrx = nrx + dirx[i];
				if (visitedr[nry][nrx] > 0) break;
				visitedr[nry][nrx] = 1;
				// 빨간 구슬이 빠지면 최소 횟수 갱신
				if (MAP[nry][nrx] == 'O') {
					cout << "level:" << level << "by:" << by << "bx:" << bx << "ry:" << ry << "rx:" << rx << "\n";
					mintry = min(mintry, level + 1);
					return;
				}
				// 더 움직일 수 없으면 제자리
				if (MAP[nry][nrx] != '.') {
					nry -= diry[i];
					nrx -= dirx[i];
					break;
				}
			}	
		}
		
		dfs(level + 1, nby, nbx, nry, nrx);
	}
	
}


int main() {
	ios_base::sync_with_stdio(false);
	cin.tie();
	cout.tie();

	cin >> N >> M;
	for (int i = 0; i < N; i++) {
		cin >> MAP[i];
		for (int j = 0; j < M; j++) {
			if (MAP[i][j] == 'B') {
				by = i;
				bx = j;
				MAP[i][j] = '.';
			}
			else if (MAP[i][j] == 'R') {
				ry = i;
				rx = j;
				MAP[i][j] = '.';
			}
		}
	}
	dfs(0, by, bx, ry, rx);
	if (mintry == 2134567890) cout << -1;
	else {
		cout << mintry;
	}

	
	return 0;
}
