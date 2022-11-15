#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <cmath>
#include <string.h>
using namespace std;

struct gps { int y,x; };
int n, m;
vector<int> dir; // �̵� ����
vector<int> dis; // �̵� �Ÿ�
vector<gps> cloud; // ������ (�̵���) ����
vector<gps> rain; // �̵��� ���� (�� ������)

int map[51][51];

int yy[8] = { 0,-1,-1,-1,0,1,1,1 };
int xx[8] = { -1,-1,0,1,1,1,0,-1 };

int side[4] = { 1,3,5,7 }; // �밢���� �ε���

void move(int t) // ���� �̵�
{
    rain.clear();
    int dd = dir[t] - 1;
    int ss = dis[t] % n; // �� �������� �̵��ϵ���
    for (int i = 0; i < cloud.size(); i++)
    {
        gps now = cloud[i];
        gps next = { now.y + yy[dd]*ss, now.x + xx[dd]*ss };
        if (next.y > n) next.y = next.y - n;
        if (next.y < 1)next.y = n + next.y;
        if (next.x > n)next.x = next.x - n;
        if (next.x < 1)next.x = n + next.x;
        rain.push_back(next);
    }
    cloud.clear();
}

void rainy()
{
    for (int i = 0; i < rain.size(); i++)
    {
        gps now = rain[i];
        map[now.y][now.x] += 1; // �񳻸���
    }
    int rmap[51][51] = { 0 };
    for (int i = 0; i < rain.size(); i++)
    {
        gps now = rain[i];
        int cnt = 1; // �밢�� ���ִ� �ٱ��� ���� (�񳻸� �ڸ� �Ǻ����� 1�� ����)
        for (int d = 0; d < 4; d++)
        {
            int dd = side[d];
            gps next = { now.y + yy[dd], now.x + xx[dd] };
            if (next.y > n || next.y<1 || next.x>n || next.x < 1)continue;
            if (map[next.y][next.x] == 0)continue;
            cnt++;
        }
        rmap[now.y][now.x] = cnt;
    }
    for (int i = 0; i < rain.size(); i++)
    {
        gps now = rain[i];
        map[now.y][now.x] += rmap[now.y][now.x]-1; // ���õ� 1���� �����ֱ�
    }
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n; j++) // ���ο� ���� ����
        {
            if (rmap[i][j] > 0)continue; // ������ ����� �ڸ� �Ǻ�
            if (map[i][j] < 2)continue; 
            map[i][j] -= 2;
            cloud.push_back({ i,j });
        }
    }
}

int go()
{
    for (int i = 0; i < m; i++) // m���̵�
    {
        move(i);
        rainy();
    }
    int cnt = 0;
    for (int i = 1; i <= n; i++) // ���� ���Ǿ� ī��Ʈ
    {
        for (int j = 1; j <= n; j++)
        {
            cnt += map[i][j];
        }
    }
    return cnt;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie();
    cout.tie();

    cin >> n >> m;
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            cin >> map[i][j];
        }
    }
    for (int i = 0; i < m; i++)
    {
        int d, s;
        cin >> d >> s;
        dir.push_back(d);
        dis.push_back(s);
    } 
    // ���� ���� ����
    cloud.push_back({ n,1 });
    cloud.push_back({ n,2 });
    cloud.push_back({ n-1,1 });
    cloud.push_back({ n-1,2 });
    cout << go();

    return 0;
}