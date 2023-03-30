#include <iostream>
#include <string>
#include <math.h>
using namespace std;

int n, k;
int idx = 1; // �ڸ� ��
int num = 9; // �ڸ� �� �� ����
int last_num;
int quotient, remain;
string answer;

void input() { cin >> n >> k; }

void calc() {

    // �����ϴ� �ڸ� �� ���� ����
    while (k > idx * num) {
        int cnt = idx * num;
        k -= cnt;
        last_num += num;
        idx++;
        num *= 10;
    }

    last_num += 1;
    quotient = (k - 1) / idx;
    remain = (k - 1) % idx;
    last_num += quotient;

}

void output() {
    if (last_num > n) cout << -1;
    else {
        answer = to_string(last_num);
        cout << answer[remain];
    }
}

int main() {

    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    input();
    calc();
    output();
}