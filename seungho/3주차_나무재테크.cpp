#include <iostream>
#include <algorithm>
#include <deque>
using namespace std;

struct node {
	int y;
	int x;
	int age;
};

int N, M, K;
int A[11][11] = { 0 };	// 추가되는 양분
int soil[11][11] = { 0 };	// 양분
deque<node> dq;
deque<node> temp;
deque<node> dead;

bool cmp(node a, node b) {
	if (a.age < b.age) return true;
	if (a.age > b.age) return false;
	if (a.y < b.y) return true;
	if (a.y > b.y) return false;
	if (a.x < b.x) return true;
	if (a.x > b.x) return false;
	return false;
}

int dy[] = { -1,-1,-1,0,0,1,1,1 };
int dx[] = { -1,0,1,-1,1,-1,0,1 };




int main() {

	cin >> N >> M >> K;

	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			cin >> A[i][j];
			soil[i][j] = 5;		 // 처음 양분 5
		}
	}
	for (int i = 0; i < M; i++) {
		int y, x, age;
		cin >> y >> x >> age;
		dq.push_back({ y,x,age });
	}

	sort(dq.begin(), dq.end(), cmp);

	for (int i = 0; i < K; i++) {
		// 봄 
		// 나이만큼 양분을 먹고, 나이 1 증가
		// 어린 나무부터
		// 양분 부족 -> 즉사
		while (!dq.empty()) {
			node now = dq.front();
			dq.pop_front();
			if (soil[now.y][now.x] < now.age) {
				dead.push_back({ now.y,now.x, now.age });
				continue;
			}
			else {
				soil[now.y][now.x] -= now.age;
				temp.push_back({ now.y,now.x,now.age + 1 });
			}
		}
		// 여름
			// 죽은 나무 -> 양분 = 나이/2
		while (!dead.empty()) {
			node now = dead.front();
			dead.pop_front();
			soil[now.y][now.x] += now.age / 2;
		}
		// 가을
			// 번식 -> 나이가 5의 배수인 나무
			// 인접한 8개 칸에 나이 1인 나무 추가
		while (!temp.empty()) {
			node now = temp.front();
			temp.pop_front();
			if (now.age % 5 == 0) {
				for (int t = 0; t < 8; t++) {
					int ny = now.y + dy[t];
					int nx = now.x + dx[t];
					if (ny <= 0 || nx <= 0 || ny > N || nx > N) continue;
					dq.push_front({ ny,nx,1 });
				}
			}
			dq.push_back({ now.y,now.x, now.age });
		}
		// 겨울
			// 양분 추가
		for (int i = 1; i <= N; i++) {
			for (int j = 1; j <= N; j++) {
				soil[i][j] += A[i][j];
			}
		}
	}
	cout << dq.size();
	return 0;
}
