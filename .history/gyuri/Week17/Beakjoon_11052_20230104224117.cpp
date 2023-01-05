#include <iostream>
#include <vector>
#define endl '\n'
using namespace std;

int N;
int cards[1002];
int dp[10002]; // index: 카드 개수, value: index만큼 카드를 구매하기 위한 최대 금액

void Input() {

    cin >> N;

    for ( int i = 1; i <= N; i++ ) {
        cin >> cards[i];
    }

}

void FillDp() {

}

void Output() {}

int main() {

    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    return 0;
}
