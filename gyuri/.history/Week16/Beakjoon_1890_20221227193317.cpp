#include <iostream>
#define endl '\n'
using namespace std;

int N;
int arr[101][101];

void Output() {}

void FillDp() {}

void Input() {

    cin >> N;

    for ( int i = 0; i < N; i++ ) {
        for (int j = 0; j < N; j++ ) {
            cin >> arr[i][j];
        }
    }
}

int main(){

    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    Input();

    return 0;
}
