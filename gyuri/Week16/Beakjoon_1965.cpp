#include <iostream>
#define endl '\n'
using namespace std;

int N;
int boxes[1001];
int dp[1001]; // 최대 상자 갯수 저장
int maxSize;

void Output() {
    cout << maxSize;
}

void FillDp() {
    for (int i = 1; i < N; i++) {
        for (int j = 0; j < i; j++) {
            if (boxes[i] > boxes[j]) {
                if (dp[i] < dp[j] + 1) dp[i] = dp[j] + 1;
            }
        }
        maxSize = max(maxSize, dp[i]);
    }
    
}

void Input() {
    cin >> N;
    for (int i = 0; i < N; i++) {
        cin >> boxes[i];
        dp[i] = 1;
    }
}


int main() {

    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    
    Input();
    FillDp();
    Output();
}