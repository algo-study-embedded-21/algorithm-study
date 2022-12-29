#include <iostream>
#define endl '\n'
using namespace std;

int N;
int arr[101][101];
long dp[101][101];

int dy[2] = {0, 1};
int dx[2] = {1, 0};

void Output() {

    // for ( int i = 0; i < N; i++ ) {
    //     for (int j = 0; j < N; j++ ) {
    //         cout << dp[i][j] << "  ";
    //     }
    //     cout << endl;
    // }
    cout << dp[N-1][N-1];
}

void FillDp() {

    dp[0][0] = 1;

    for ( int i = 0; i < N; i++ ) {
        for ( int j = 0; j < N; j++ ) {
            for ( int k = 0; k < 2; k++) {

                int ny = i + dy[k] * arr[i][j];
                int nx = j + dx[k] * arr[i][j];

                if ( nx < 0 || ny < 0 || nx >= N || ny >= N ) continue;
                if ( i == N-1 && j == N-1 ) break;

                dp[ny][nx] += dp[i][j];
            }
        }
    }

}

void Input() {

    cin >> N;

    for ( int i = 0; i < N; i++ ) {
        for (int j = 0; j < N; j++ ) {
            cin >> arr[i][j];
        }
    }
}

int main() {

    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    Input();
    FillDp();
    Output();

    return 0;
}
