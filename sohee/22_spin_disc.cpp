#include <iostream>
#include <vector>
using namespace std;

int n, m, t;
int map[51][51];

// ������ �� ã��
int  findNum() {
    int flag = 1;
    int cnt = 0;
    int all = 0;

    // ���� ��ǥ ����
    vector<pair<int, int>> v;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            // �̹� ������ ���� �ǳʶٱ�
            if (map[i][j] == 0) continue;

            // �¿� �˻�
            if (map[i][j] == map[i][(j + 1) % m] || map[i][j] == map[i][(j - 1 + m) % m]) {
                v.push_back({ i, j });
                flag = 0;
                continue;
            }

            // �յ� �� �˻�
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

            // ������ ���ڰ� �ƴ϶�� ���� �� �հ� ����
            cnt++;
            all += map[i][j];
        }
    }

    if (flag) {
        if (cnt == 0) return 0;

        // int�� �ߴ� �Ҽ� ó���� ������
        // �������� ���� ���� ��� ���ϱ�
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
        // �����ϸ鼭 ���� �� �����
        for (auto p : v) {
            map[p.first][p.second] = 0;
        }
    }

    return all;
}

// ȸ�� ��Ű�� + �� ���ϱ�
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

    // �Է�
    cin >> n >> m >> t;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> map[i][j];
        }
    }

    // t�� ȸ��
    for (int i = 0; i < t; i++) {
        int x, d, k;
        cin >> x >> d >> k;
        // �ݽð� ���� ȸ�� = �ð�������� m - k��ŭ �� ��
        k %= m;
        if (d) {
            k = m - k;
        }

        answer = rolling(x, k);
    }

    cout << answer;

    return 0;
}