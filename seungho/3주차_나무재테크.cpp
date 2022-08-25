#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
using namespace std;

struct node {
	int y;
	int x;
	int z;
};

int N, M, K;
int A[11][11] = { 0 };	// 추가되는 양분
int soil[11][11]={0};	// 양분
//vector<node> tree;
priority_queue<node> pq1;
priority_queue<node> pq2;

//bool cmp (node a, node b) {
//	if (a.y < b.y) return true;
//	if (a.y > b.y) return false;
//	if (a.x < b.x) return true;
//	if (a.x > b.x) return false;
//	if (a.z < b.z) return true;
//	if (a.z > b.z) return false;
//	return false;
//}

bool operator<(node a, node b) {
	if (a.y < b.y) return false;
	if (a.y > b.y) return true;
	if (a.x < b.x) return false;
	if (a.x > b.x) return true;
	if (a.z < b.z) return false;
	if (a.z > b.z) return true;
	return false;
}

int dy[] = { -1,-1,-1,0,0,1,1,1 };
int dx[] = { -1,0,1,-1,1,-1,0,1 };

int main() {
	
	cin >> N >> M >> K;
	int cntTree = 0;

	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			cin >> A[i][j];
			soil[i][j] = 5;		 // 처음 양분 5
		}
	}
	for (int i = 0; i < M; i++) {
		int x, y, z;
		cin >> x >> y >> z;
		//tree.push_back({ y,x,z, 1 });
		pq1.push({ x,y,z });
	}	
	queue<node> q;

	for (int year = 0; year < K; year++) {
		// 봄 
		// 나이만큼 양분을 먹고, 나이 1 증가
		// 어린 나무부터
		// 양분 부족 -> 즉사
		while (!pq1.empty()) {
			node now = pq1.top();
			pq1.pop();
			// 현재 땅의 양분이 나이보다 적으면 즉사
			if (soil[now.y][now.x] < now.z) {
				q.push({ now.y,now.x,now.z});
				continue;
			}
			soil[now.y][now.x] -= now.z;
			//cout << now.z + 1<<" ";
			pq2.push({ now.y,now.x,now.z + 1 });
		}

		// 여름
		// 죽은 나무 -> 양분 = 나이/2
		while (!q.empty()) {
			node now = q.front();
			q.pop();
			soil[now.y][now.x] += now.z / 2;
		}

		// 가을
		// 번식 -> 나이가 5의 배수인 나무
		// 인접한 8개 칸에 나이 1인 나무 추가
		while (!pq2.empty()) {
			node now = pq2.top();
			pq2.pop();
			if (now.z % 5 == 0) {
				for (int t = 0; t < 8; t++) {
					int ny = now.y + dy[t];
					int nx = now.x + dx[t];
					if (ny <= 0 || nx <= 0 || ny > N || nx > N) continue;
					pq1.push({ ny,nx,1 });
				}
			}
			pq1.push(now);
		}

		// 겨울
		// 양분 추가
		for (int i = 1; i <= N; i++) {
			for (int j = 1; j <= N; j++) {
				soil[i][j] += A[i][j];
			}
		}
	}

	cout << pq1.size();

	return 0;
}
