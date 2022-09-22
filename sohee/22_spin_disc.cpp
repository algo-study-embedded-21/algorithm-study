#include <iostream>
#include <vector>
using namespace std;

int n, m, t;
int map[51][51];

// 인접한 수 찾기
int  findNum() {
    int flag = 1;
    int cnt = 0;
    int all = 0;

    // 지울 좌표 저장
    vector<pair<int, int>> v;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            // 이미 지워진 수면 건너뛰기
            if (map[i][j] == 0) continue;

            // 좌우 검사
            if (map[i][j] == map[i][(j + 1) % m] || map[i][j] == map[i][(j - 1 + m) % m]) {
                v.push_back({ i, j });
                flag = 0;
                continue;
            }

            // 앞뒤 판 검사
            if (i + 1 < n) {
                if (map[i][j] == map[i + 1][j]) {
                    v.push_back({ i, j });
                    flag = 0;
                    continue;
                }
            }
            if (i > 0) {
                if (map[i][j] == map[i - 1][j]) {
                    v.push_back({ i, j });
                    flag = 0;
                    continue;
                }
            }

            // 지워질 숫자가 아니라면 개수 및 합계 저장
            cnt++;
            all += map[i][j];
        }
    }

    if (flag) {
        if (cnt == 0) return 0;

        // int로 했다 소수 처리를 못했음
        // 지워지지 않은 숫자 평균 구하기
        double avg = (double)all / cnt;

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (map[i][j] == 0) continue;
                if (map[i][j] > avg) map[i][j] -= 1;
                else if (map[i][j] < avg) map[i][j] += 1;
            }
        }
    }
    else {
        // 인접하면서 같은 수 지우기
        for (auto p : v) {
            map[p.first][p.second] = 0;
        }
    }

    return all;
}

// 회전 시키기 + 합 구하기
int rolling(int x, int k) {
    for (int j = x - 1; j < n; j+= x) {
        int line[51] = { 0 };
        for (int i = 0; i < m; i++) {
            line[(i + k) % m] = map[j][i];
        }
        for (int i = 0; i < m; i++) {
            map[j][i] = line[i];
        }
    }

    return findNum();
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie();
    cout.tie();

    int answer = 0;

    // 입력
    cin >> n >> m >> t;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> map[i][j];
        }
    }

    // t번 회전
    for (int i = 0; i < t; i++) {
        int x, d, k;
        cin >> x >> d >> k;
        // 반시계 방향 회전 = 시계방향으로 m - k만큼 돈 것
        k %= m;
        if (d) {
            k = m - k;
        }

        answer = rolling(x, k);
    }

    cout << answer;

    return 0;
}