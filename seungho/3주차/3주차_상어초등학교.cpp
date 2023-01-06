#include <iostream>
#include <vector>
using namespace std;

int main() {
	int n;
	cin >> n;
	vector<int> v[441];
	int MAP[21][21]={0};
	int diry[4] = { 0,0,1,-1 };
	int dirx[4] = { 1,-1,0,0 };

	struct Node {
		int y;
		int x;
		int cntl;
		int cntv;
	};

	for (int i = 0; i < n*n; i++) {
		int s;
		cin >> s;
		for (int j = 0; j < 4; j++) {
			int t;
			cin >> t;
			v[s].push_back(t);
		}
		int maxlike = -1;
		Node maximum;
		for (int y = 1; y <= n; y++) {
			for (int x = 1; x <= n; x++) {

				// 이미 학생이 앉아있다면 패스
				if (MAP[y][x] > 0) continue;
				int cntlike = 0;	// 인접한 좋아하는 학생 수
				int cntvacant = 0;	// 인접한 빈자리수
				for (int p = 0; p < 4; p++) {	// 상하좌우
					int ny = y + diry[p];
					int nx = x + dirx[p];
					if (ny <= 0 || nx <= 0 || ny > n || nx > n) continue;
					for (int q = 0; q < 4; q++) {	// 좋아하는 학생 4명 중 인접한 자리에 있으면 
						if (MAP[ny][nx] == v[s][q]) cntlike++;
					}
					if (MAP[ny][nx] == 0) cntvacant++;
				}

				// 가장 많은 좋아하는 학생과 인접하는 경우

				// 기존 최대값보다 큰 경우 -> 최대값 갱신
				if (maxlike < cntlike) {
					maxlike = cntlike;
					maximum = { y,x,cntlike,cntvacant };
				}
				// 기존 최대값과 같은 경우 -> 인접한 빈자리 많은 자리 선택
				if (maxlike == cntlike) {

					// 3번째 조건에 맞게 왼쪽 위부터 순서대로 탐색하므로 빈 자리가 더 많을 경우에만 갱신
					if (maximum.cntv < cntvacant) {		
						maximum = { y,x,cntlike,cntvacant };
					}
				}
			}
		}
		MAP[maximum.y][maximum.x] = s;		// 학생배치
	}
	
	int score = 0;
	int scorel[5] = { 0,1,10,100,1000 };
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			int cnt = 0;
			for (int p = 0; p < 4; p++) {	// 상하좌우
				int ny = i + diry[p];
				int nx = j + dirx[p];
				if (ny <= 0 || nx <= 0 || ny > n || nx > n) continue;
				for (int q = 0; q < 4; q++) {	// 좋아하는 학생 4명 중 인접한 자리에 있으면 
					if (MAP[ny][nx] == v[MAP[i][j]][q]) cnt++;  
				}
			}
			score += scorel[cnt];
		}
	}
	cout << score;

	return 0;
}
