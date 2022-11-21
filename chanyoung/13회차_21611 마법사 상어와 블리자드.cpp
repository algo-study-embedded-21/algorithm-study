#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <cmath>
#include <string.h>
using namespace std;

struct gps { int y, x; };
struct mapnum { int num, cnt; }; // ĭ�� ���� , ĭ�� �ִ� ���� ��ȣ

int n, m;
mapnum map[50][50];
vector<int> magic; // ���ڵ� ���� �Ÿ�
vector<int> magicDir; // ���ڵ� ���� ����
int one, two, three;
vector<int> line; // ������ �迭�� ���ٷ�
vector<int> out; // �ı��� ��ġ ǥ��
gps shark; // ����� ��ġ(���߾�)

int yy[4] = { -1,1,0,0 };
int xx[4] = { 0,0,-1,1 };

int turn[4] = { 2,1,3,0 }; // ������ �迭 �������

void refill() // �ı��� ���� ����
{
    vector<int> tmp;
    vector<int> outtmp;
    for (int i = 0; i < line.size(); i++)
    {
        if (out[i])continue; // �ı��� ���� ����
        tmp.push_back(line[i]);
        outtmp.push_back(0);
    }
    line = tmp;
    out = outtmp;
}

void makeline() // ������ �迭 ���ٷ� �����
{
    gps next = shark;
    int go = 1;
    int dir = 0;
    int num = 0;
    while (go <= n)
    {
        for (int t = 0; t < 2; t++) //���� ���̷� 2�� �ݺ�(���⸸ ����)
        {
            int d = turn[dir];
            for (int i = 0; i < go; i++)
            {
                next = { next.y + yy[d],next.x + xx[d] };
                if (next.y<0 || next.y>n - 1 || next.x<0 || next.x>n - 1)continue;
                int cnt = map[next.y][next.x].cnt;
                map[next.y][next.x].num = num;
                num++;
                if (cnt == 0)continue;; // ������ ������ ��ȣ�� ǥ���ϰ� �߰����� �ʱ�
                line.push_back(cnt);
                out.push_back(0);
            }
            dir += 1;
            dir %= 4;
        }
        go++; // ���� �ø�
    }
}

void breaking(int d, int s) // �������� ���� �ı�
{
    if (line.size() == 0)return;
    gps next = shark;
    for (int i = 0; i < s; i++)
    {
        next = { next.y + yy[d],next.x + xx[d] };
        if (next.y<0 || next.y>n - 1 || next.x<0 || next.x>n - 1)break;
        int num = map[next.y][next.x].num;
        if (num >= line.size())break;
        out[num] = 1; // �ı��� ���� ǥ��
    }
    refill();
}

void fourblock() // 4���̻� ����
{
    int bf = -1;
    int cnt = 0;
    int flag = 1;
    while (flag) // ������ ���������� �ݺ�
    {
        if (line.size() < 4)return;
        flag = 0;
        vector<int> erase; // ������ �׷�
        for (int i = 0; i < line.size(); i++)
        {
            int now = line[i];
            if (now == bf)
            {
                erase.push_back(i); // ���ӵ� ���� �׷쿡 ���
                if (i == line.size() - 1) // ������ ������ �׷쿡 ���Եɰ��
                {
                    if (erase.size() >= 4)
                    {
                        flag = 1;
                        for (int j = 0; j < erase.size(); j++)
                        {
                            out[erase[j]] = 1;
                            if (bf == 1)one++;
                            else if (bf == 2)two++;
                            else if (bf == 3)three++;
                        }
                    }
                }
            }
            else
            {
                if (erase.size() >= 4) // �׷�ũ�Ⱑ 4�̻��̸� ����
                {
                    flag = 1;
                    for (int j = 0; j < erase.size(); j++)
                    {
                        out[erase[j]] = 1;
                        if (bf == 1)one++;
                        else if (bf == 2)two++;
                        else if (bf == 3)three++;
                    }
                }
                erase.clear(); // ������ �׷� �ʱ�ȭ
                erase.push_back(i);
            }
            bf = now;
        }
        if (flag) refill(); // ������ ������ ���ٸ� �������� �ʴ´�
    }
}

void change() // ���� ��ȭ
{
    if (line.size() == 0)return;
    int bf = line[0]; // ���� �׷��� ���� ��ȣ
    int cnt = 1;
    vector<int> tmp; // ��ȭ�� ���� ����
    vector<int> outtmp;
    for (int i = 1; i < line.size(); i++)
    {
        int now = line[i];
        if (bf == now)cnt++;
        else
        {
            tmp.push_back(cnt);
            tmp.push_back(bf);
            outtmp.push_back(0);
            outtmp.push_back(0);
            cnt = 1;
            bf = now;
        }
        if (i == line.size() - 1) // ������������ ��� ���������� ����
        {
            tmp.push_back(cnt);
            tmp.push_back(bf);
            outtmp.push_back(0);
            outtmp.push_back(0);
        }
        if (tmp.size() + 1 >= n * n)break; // ������ ���� ũ�⸦ ������ �ߴ�
    }
    while (tmp.size() + 1 > n * n) // ���� ��� ���� ���� 
    {
        tmp.pop_back();
        outtmp.pop_back();
    }
    line = tmp;
    out = outtmp;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie();
    cout.tie();

    cin >> n >> m;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            cin >> map[i][j].cnt;
        }
    }
    for (int i = 0; i < m; i++)
    {
        int d, s;
        cin >> d >> s;
        magicDir.push_back(d - 1);
        magic.push_back(s);
    }
    shark = { n / 2,n / 2 };
    makeline();
    for (int i = 0; i < m; i++)
    {
        int d = magicDir[i];
        int s = magic[i];
        breaking(d, s);
        fourblock();
        change();
    }
    int ans = 1 * one + 2 * two + 3 * three;
    cout << ans;

    return 0;
}