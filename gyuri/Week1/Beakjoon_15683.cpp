#include <iostream>
#include <algorithm>
#include <queue>
#define endl '\n'
using namespace std;

struct CCTV {
    int y, x;
};

int N, M;
char arr[10][10];
int visited[10][10];
int cctvCnt = 0;

int dy[] = { 0, 0, 1, -1 }; // 우 좌 하 상 
int dx[] = { 1, -1, 0, 0 };

vector<vector<vector<int>>> vec = {
    {},
    {{0}, {1}, {2}, {3}}, // 1번 cctv의 방향 인덱스 
    {{0, 2}, {1, 3}}, // 2번 cctv의 방향 인덱스
    {{0, 1}, {2, 3}}, // 3번 cctv의 방향 인덱스
    {{0, 1}, {1, 2}, {2, 3}}, // 4번 cctv의 방향 인덱스
    {{0, 1, 2, 3 }} // 5번 cctv의 방향 인덱스
};

void cctv(int y, int x, int idx) {
    queue<CCTV> q;
    q.push({ y, x });

while (!q.empty()) {
    CCTV now = q.front();
    q.pop();

    for (int i = 0; i < vec[idx].size(); i++) {
        for (int j = 0; j <= vec[idx][i].size(); j++) {
            int ny = now.y + dy[j];
            int nx = now.x + dx[j];

            if (ny < 0 || nx < 0 || ny >= N || nx >= M) break; // 배열 범위를 넘으면 멈추기
            if (arr[ny][nx] == '6') break; // 장애물을 만나면 멈추기
            if (arr[ny][nx] != '0') continue; // cctv 무시
            if (arr[ny][nx] == '#') continue; // 이미 방문한 곳이라면 무시

            arr[ny][nx] = '#';
            q.push({ ny, nx });
        }
    }
}
}

int main()
{
    ios_base::sync_with_stdio;
    cin.tie();
    cout.tie();

cin >> N >> M;

// 배열 셋팅
for (int i = 0; i < N; i++) {
    for (int j = 0; j < M; j++) {
        cin >> arr[i][j];
        if (arr[i][j] != '0') cctvCnt++; // cctv와 장애물 수 구하기
    }
}

for (int i = 0; i < N; i++) {
    for (int j = 0; j < M; j++) {
        if (arr[i][j] == '0') continue;
        if (arr[i][j] == '6') continue;
        int n = arr[i][j] - '0';
        cctv(i, j, n);
    }
}

for (int i = 0; i < N; i++) {
    for (int j = 0; j < M; j++) {
        cout << arr[i][j] << " ";
    }
    cout << endl;
}
}