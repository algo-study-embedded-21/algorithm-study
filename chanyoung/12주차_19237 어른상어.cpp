#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <cmath>
#include <string.h>
using namespace std;

struct gps { int y, x; };
struct smell { int snum, last; }; // ������ ���ι�ȣ , �����ð�

int n, m, k;
int map[20][20];
smell smellmap[20][20]; //�� ��ġ�� ���� ���� ǥ��
gps shark[400]; // ������ ���� ��ġ
int nowdir[400]; // ������ �����ִ� ����
int outshark[400]; // ����� ��� ǥ��
vector<int> sdir[400][4]; // ������ ���� �켱����

int yy[4] = { -1,1,0,0 };
int xx[4] = { 0,0,-1,1 };

void move()
{
    int tmp[20][20] = { 0 };
    for (int i = 1; i <= m; i++) // 1�� ������ �̵�
    {
        if (outshark[i])continue; // ����� ��� ����
        gps now = shark[i];
        int d = nowdir[i];
        gps check = { 30,30 }; // �̵��� ��ġ �ʱⰪ(�ʹ�)
        int checkd; // �̵��� �� �ٶ󺸴� ����
        for (int j = 0; j < 4; j++)
        {
            int dd = sdir[i][d][j]; // �켱������ ���� ����
            gps next = { now.y + yy[dd], now.x + xx[dd] };
            if (next.y<0 || next.y>n - 1 || next.x<0 || next.x>n - 1)continue;
            if (check.y == 30 && smellmap[next.y][next.x].snum==i) 
            { // �ڱ⳿���� ����ĭ�� �켱���� ���⿡ ���� ���� ù��° ĭ
                check = next;
                checkd = dd;
            }
            else if (smellmap[next.y][next.x].snum==0)
            { // ������ ���� ĭ ����� �̵�ĭ���� Ȯ��!
                check = next;
                checkd = dd;
                break;
            }
        }
        if (check.y == 30)continue; // �̵��Ҽ� �ִ� ĭ�� ���°��
        if (tmp[check.y][check.x] == 0 || tmp[check.y][check.x]>i)
        { // �� ĭ������ �̵��� ���� ó���̰ų� ������ ū��ȣ�� �� �ִ°�� �ڸ�����
            outshark[tmp[check.y][check.x]] = 1;
            tmp[check.y][check.x] = i;
            map[check.y][check.x] = i;
            shark[i] = check;
            nowdir[i] = checkd;
        }
        else if(tmp[check.y][check.x] < i) outshark[i] = 1; // ������ ���� ��ȣ�� �� �ִ°�� ���� ����
    }
}

void makesmell() // ���� ����
{
    for (int i = 0; i < 20; i++)
    {
        for (int j = 0; j < 20; j++) // ��� �ʿ� ����
        {
            if (smellmap[i][j].last > 0)
            {
                smellmap[i][j].last -= 1; // ���� ���̰�
                if (smellmap[i][j].last == 0) smellmap[i][j].snum = 0; // ������ �� ������ �ʱ�ȭ
            }
        }
    }
    for (int i = 1; i <= m; i++) // ���� ������ġ�� ���� �����
    {
        if (outshark[i])continue;
        gps now = shark[i];
        smellmap[now.y][now.x].snum = i;
        smellmap[now.y][now.x].last = k;
    }
}

int check() // ��������
{
    for (int i = 2; i <= m; i++) if (outshark[i] == 0)return 0;
    return 1;
}


int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie();
    cout.tie();

    cin >> n >> m >> k;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            cin >> map[i][j];
            if (map[i][j] > 0)shark[map[i][j]] = { i,j };
        }
    }
    for (int i = 1; i <= m; i++)
    {
        int d;
        cin >> d;
        nowdir[i] = d - 1;
    }
    for (int i = 1; i <= m; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            for (int a = 0; a < 4; a++)
            {
                int d;
                cin >> d;
                sdir[i][j].push_back(d - 1);
            }
        }
    }
    makesmell(); // ���ʿ� ���� ����� ����
    for (int i = 1; i <= 1000; i++)
    {
        move();
        makesmell();
        if (check())
        {
            cout << i;
            return 0;
        }
    }
    cout << "-1";
    return 0;
}