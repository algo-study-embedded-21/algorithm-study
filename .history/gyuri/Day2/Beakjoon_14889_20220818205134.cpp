// 아이디어 구상
// 모든 사람들의 조합을 구해 구성된 팀의 능력치 차이를 최소로 해야하기 때문에
// dfs + back tracking 을 이용하면 될 것 같다.

#include <iostream>
#include <algorithm>
#include <vector>
#define endl '\n'
using namespace std;

// level : 각 팅당 사람 수 (N/2)
// branch : 사람들(N)

int N;
int arr[25][25];

int used[25];
vector<int> path; 
int minval = 2134567890;


void dfs(int level) {

    // 기저 조건
    if (level == N / 2) {
        int start = 0;
        int link = 0;
        for (int i = 1; i <= N; i++) {
            for (int j = 1; j <= N; j++) {
                if (used[i] == 1 && used[j] == 1) start += arr[i][j];
                else if (used[i] == 0 && used[j] == 0) link += arr[i][j];
            }
        }

        int sub = abs(start - link);
        if (minval > sub) {
            minval = sub;
        }
        return;
    }

    // 재귀 구성
    for (int branch = 1; branch <= N; branch++) {
        if (used[branch] == 1) continue;
        if (level > 0) {
            if (path[level - 1] > branch) continue;
        }

        used[branch] = 1;
        path.push_back(branch);
        dfs(level+1);
        used[branch] = 0;
        path.pop_back();
    }
}

int main() {

    ios_base::sync_with_stdio(false);
    cin.tie();
    cout.tie();

    cin >> N;

    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= N; j++) {
            cin >> arr[i][j];
        }
    }

    dfs(0);
    cout << minval;

    return 0;
}