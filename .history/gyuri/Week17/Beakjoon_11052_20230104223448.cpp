#include <iostream>
#include <vector>
#define endl '\n'
using namespace std;

int N;
int cards[1002];

void Input() {

    cin >> N;

    for ( int i = 0; i < N; i++ ) {
        cin >> cards[i];
    }
}

void Output() {}

int main() {

    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    return 0;
}
