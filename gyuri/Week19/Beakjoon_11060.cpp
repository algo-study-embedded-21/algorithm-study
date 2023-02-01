#include <iostream>
#define endl '\n'
#define MAX 1001
using namespace std;

int N;
int arr[1001];
int dp[1001];
int result;

// dp[A] = V
// V : A��° ĭ���� �� �� �ִ� �ּ� ����� ��

void Input() {

    cin >> N;

    for (int i = 0; i < N; i++) {
        cin >> arr[i];
    }

}

void FillDp() {

    for (int i = 1; i < N; i++) {
        dp[i] = MAX;
    }

    for (int i = 0; i < N; i++) { // �迭 ��ü Ž��
        for (int j = 1; j <= arr[i]; j++) { // �̵��� �� �ִ� Ƚ��
            dp[i + j] = min(dp[i + j], dp[i] + 1);
        }
    }
}

void Output() {

    result = (dp[N - 1] == MAX) ? -1 : dp[N - 1];

    cout << result;
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