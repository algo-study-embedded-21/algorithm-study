#include <iostream>
using namespace std;

// 0 : green
// 1 : blue
int block[2][6][4];
int n;
// 각 열에 블록이 차있는 정도를 저장
int buffer[2][4];
int score;

int getCnt() {
    int val = 0;
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 6; j++) {
            for (int k = 0; k < 4; k++) {
                if (block[i][j][k] == 1) val++;
            }
        }
    }
    return val;
}

// 행 없애기
void deleteBlock(int color, int index) {
    for (int i = index; i < 5; i++) {
        for (int j = 0; j < 4; j++) {
            block[color][i][j] = block[color][i + 1][j];
        }
    }
    for (int i = 0; i < 4; i++) {
        block[color][5][i] = 0;
        if (buffer[color][i] != 0) buffer[color][i] -= 1;
    }
}

// 특별한 칸 체크
void checkSpecial(int color) {
    int top = 0;
    for (int i = 0; i < 4; i++) {
        top = max(top, buffer[color][i]);
    }
    if (top == 5) {
        deleteBlock(color, 0);
    }
    else if (top == 6) {
        deleteBlock(color, 0);
        deleteBlock(color, 0);
    }
}

// 타일 수 체크
// 행의 수 만큼만 땡김
void checkFull(int color, int top) {
    int index = 0;
    while (index < 6) {
        int flag = 1;
        for (int j = 0; j < 4; j++) {
            if (block[color][index][j] == 0) {
                flag = 0;
                break;
            }
        }

        if (flag) {
            deleteBlock(color, index);
            score++;
        }
        else {
            index++;
        }
    }
}

// 블록 이동
// 열 정보 & 쌓이는 블록 개수 정보
void move(int color, pair<int, int> row, int col) {
    int top = buffer[color][row.first];
    if (row.second != -1) {
        top = max(top, buffer[color][row.second]);
        block[color][top][row.second] = 1;
        buffer[color][row.second] = top + col;
    }
    for (int i = 0; i < col; i++) {
        block[color][top + i][row.first] = 1;
    }
    buffer[color][row.first] = top + col;

    checkFull(color, top);
    checkSpecial(color);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie();
    cout.tie();

    cin >> n;
    for (int i = 0; i < n; i++) {
        int t, x, y;
        cin >> t >> x >> y;
        if (t == 1) {
            move(0, { y, -1 }, 1);
            move(1, { x, -1 }, 1);
        }
        else if (t == 2) {
            move(0, { y, y + 1 }, 1);
            move(1, { x, -1 }, 2);
        }
        else if (t == 3) {
            move(0, { y, -1 }, 2);
            move(1, { x, x + 1 }, 1);
        }
    }

    cout << score << '\n';
    cout << getCnt();

    return 0;
}