#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <cmath>
#include <string.h>
#include <unordered_map>
using namespace std;

struct gps { int y, x; };

int test,n;
char cube[6][3][3]; // 0:��,1:�Ʒ�,2:��,3:��,4:��,5:��

/*  <�� �� ����>    <����,�Ʒ���>  
    ����              �޸�
*   0,0,0           0,0,0
*   0,0,0           0,0,0
*   0,0,0           0,0,0
*   �Ʒ���            �ո�
*/

int turnindex[6][4] = { // �ش���� �� �������� ������ �������� �ð���� �ε���
    {3,5,2,4},
    {3,4,2,5},
    {0,5,1,4},
    {0,4,1,5},
    {0,2,1,3},
    {0,3,1,2}
};

int rowcol[6][6] = { // rowcol[�ش��][���ư��¸�index] ���ư��� �鿡���� �ش�鿡�� ���ư��� ��,���� ���� ����index
    {-1,-1,0,1,3,2},
    {-1,-1,0,1,2,3},
    {1,0,-1,-1,3,2},
    {1,0,-1,-1,2,3},
    {1,0,2,3,-1,-1},
    {1,0,3,2,-1,-1}
};

gps st[6][6] = { // st[�ش��][���¸�] �� �������� �ð�������� ���� ���ư��� ��,���� ���� ��ǥ
    {{-1,-1},{-1,-1},{2,0},{0,2},{0,0},{2,2}},
    {{-1,-1},{-1,-1},{2,0},{0,2},{2,2},{0,0}},
    {{0,2},{2,0},{-1,-1},{-1,-1},{0,0},{2,2}},
    {{0,2},{2,0},{-1,-1},{-1,-1},{2,2},{0,0}},
    {{0,2},{2,0},{2,2},{0,0},{-1,-1},{-1,-1}},
    {{0,2},{2,0},{0,0},{2,2},{-1,-1},{-1,-1}}
};

char color[6] = { 'w','y', 'r', 'o', 'g', 'b' };
unordered_map<char, int> sideindex = { {'U',0},{'D',1}, {'F',2}, {'B',3}, {'L',4}, {'R',5} };
unordered_map<char, int> turndir = { {'+',1},{'-',0} };

int yy[4] = { 0,0,-1,1 };
int xx[4] = { 1,-1,0,0 };

void cubeset() // ť���ʱ�ȭ
{
    for (int i = 0; i < 6; i++)
    {
        memset(cube[i], color[i], sizeof(cube[i]));
    }
}

void turn(char side, char dir) // ���ư��� �� ������
{
    int s = sideindex[side];
    int d = turndir[dir];
    int tmp[3][3] = { 0 };
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (d) tmp[j][2 - i] = cube[s][i][j]; // �ð����
            else tmp[i][j] = cube[s][j][2 - i]; // �ݽð����
        }
    }
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            cube[s][i][j] = tmp[i][j];
        }
    }
}

void turnside(char side, char dir) // ���ư��� �� ���� ������
{
    int s = sideindex[side];
    int d = turndir[dir];
    int now = turnindex[s][0]; // ���ư��� �� ���� �������� ����
    int tmp[3][3] = { 0 };
    for (int i = 0; i < 3; i++) // ���� tmp�� ���
    {
        for (int j = 0; j < 3; j++)
        {
            tmp[i][j] = cube[now][i][j];
        }
    }
    for (int i = 0; i < 3; i++) // ��>>��>>��>>�� or ��>>��>>��>>��
    {
        int next;
        if (d) next = turnindex[s][3 - i]; // �ð����
        else next = turnindex[s][i + 1]; // �ݽð����
        gps nowst = st[now][s];
        gps nextst = st[next][s];
        int nowd = rowcol[now][s];
        int nextd = rowcol[next][s];
        for (int j = 0; j < 3; j++)
        {
            cube[now][nowst.y + yy[nowd] * j][nowst.x + xx[nowd] * j] = cube[next][nextst.y + yy[nextd] * j][nextst.x + xx[nextd] * j];
        }
        now = next;
    }
    // �� >> �� or ��
    int next = turnindex[s][0];
    gps nowst = st[now][s];
    gps nextst = st[next][s];
    int nowd = rowcol[now][s];
    int nextd = rowcol[next][s];
    for (int j = 0; j < 3; j++)
    {
        cube[now][nowst.y + yy[nowd] * j][nowst.x + xx[nowd] * j] = tmp[nextst.y + yy[nextd] * j][nextst.x + xx[nextd] * j];
    }
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie();
    cout.tie();
    
    cin >> test;
    for (int t = 0; t < test; t++)
    {
        cubeset();
        cin >> n;
        for (int i = 0; i < n; i++)
        {
            string command;
            cin >> command;
            turn(command[0], command[1]);
            turnside(command[0], command[1]);
        }
        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                cout << cube[0][i][j];
            }
            cout << "\n";
        }
    }

    return 0;
}