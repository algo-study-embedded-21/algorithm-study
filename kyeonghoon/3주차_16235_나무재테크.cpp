#include<iostream>
#include<vector>
#include<queue>
using namespace std;

int dx[] = { -1,-1,-1,0,1,1,1,0 };
int dy[] = { -1,0,1,1,1,0,-1,-1 };
//나무의 위치
priority_queue<int, vector<int>, greater<int>> tree[10][10];

//five_tree : 5살나무, n_tree : 임시나무, dead : 죽은나무
vector<int> five_tree[10][10], n_tree[10][10], dead[10][10];

int n, m, k;
int a[10][10];
int map[10][10];

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cin >> n >> m >> k;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cin >> a[i][j];
			map[i][j] = 5;
		}
	}
	for (int i = 0; i < m; i++) {
		int x, y, age;
		cin >> x >> y >> age;
		x -= 1, y -= 1;
		tree[x][y].push(age);
	}
	for (int time = 1; time <= k; time++) {
		//봄
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				//빈곳이면 패스
				if (tree[i][j].size() == 0)continue;
				//빌때까지 n_tree, dead, five_tree 에 넣는다.
				while (!tree[i][j].empty()) {
					if (map[i][j] - tree[i][j].top() >= 0) {
						//한살 증가한채로 새로운 위치저장
						n_tree[i][j].push_back(tree[i][j].top() + 1);
						//나이만큼 양분감소
						map[i][j] -= tree[i][j].top();
						//만약 한살 증가한 것이 5의배수나이라면 따로 저장
						if ((tree[i][j].top() + 1) % 5 == 0) {
							five_tree[i][j].push_back(tree[i][j].top() + 1);
						}
					}
					//양분이 부족하다면 다 죽는다
					else {
						dead[i][j].push_back(tree[i][j].top());
					}
					tree[i][j].pop();
				}
			}
		}
		//여름
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				if (dead[i][j].size() == 0)continue;
				for (auto x : dead[i][j]) {
					map[i][j] += x / 2;
				}
				dead[i][j].clear();
			}
		}
		//가을
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				if (five_tree[i][j].size() == 0)continue;
				for (auto x : five_tree[i][j]) {
					for (int k = 0; k < 8; k++) {
						int nx = i + dx[k];
						int ny = j + dy[k];
						if (nx < 0 || nx >= n || ny < 0 || ny >= n)continue;
						n_tree[nx][ny].push_back(1);
					}
				}
				five_tree[i][j].clear();
			}
		}
		//겨울
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				map[i][j] += a[i][j];
			}
		}
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				for (auto x : n_tree[i][j]) {
					tree[i][j].push(x);
				}
				n_tree[i][j].clear();
			}
		}
	}
	int cnt = 0;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cnt += tree[i][j].size();
		}
	}
	cout << cnt;
}
