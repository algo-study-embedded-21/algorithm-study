#include <iostream>
#include <vector>
#define endl '\n'
using namespace std;

int n;
int arr[100001];
int dp[100001]; // index: 수열 인덱스, value: 가장 큰 합

void Input() {

    cin >> n;

    for ( int i = 0; i < n; i++ ) {
        cin >> arr[i];
    }
}

void FillDp() {
    
}

void Output() {}

int main() {

    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    Input();
    Output();
    return 0;
}
