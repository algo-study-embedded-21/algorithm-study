#include<iostream>
#include<string>
#include<vector>
#include<queue>
#include<cstring>
#include<algorithm>
#include<unordered_map>
#include<cmath>
using namespace std;

// 1:18  ���� ����
// 1:32  ����!

struct gps {
    int y;
    int x;
};

int n,ans;
vector<int> map[20];
vector<int> path;

int yy[4] = { -1,1,0,0 }; // �� �Ʒ� ���� ������ ����
int xx[4] = { 0,0,-1,1 };
vector<int> en; // 0 �Ǵ� n-1
int plusminus[2] = { 1,-1 }; //���� ���� ǥ��

void slide(int d) // ���ʹ������� ����
{
    int dd = d % 2; // �� �Ǵ� ���ʹ����϶� 0  �Ʒ� �Ǵ� ������ �����϶� 1
    int ddd = (d + 1) % 2; // dd�� �ݴ�
    int i = en[dd]; // �������϶� 0 �Ʒ������϶� n-1
    while (i != en[ddd] - plusminus[ddd]) // �������϶� n-1-(-1) = n �Ʒ������϶� 0-1 = -1
    {
        int j = en[dd];
        while(j != en[ddd] - plusminus[ddd])
        {
            int yd = i, xd = j;
            while (yd + yy[d] >= 0 && yd + yy[d] <= n - 1 && xd + xx[d] <= n - 1 && xd + xx[d] >= 0 && map[yd + yy[d]][xd + xx[d]] == 0)
            {
                yd += yy[d];
                xd += xx[d];
            }
            int temp = map[i][j];
            map[i][j] = 0;
            map[yd][xd] = temp;
            j += plusminus[dd];
        }
        i += plusminus[dd]; // �������϶� ���� �Ʒ������϶� ����
    }
}

void make(int d) // ���� ���� ��ġ��
{
    int dd = d % 2;
    int ddd = (d + 1) % 2;
    int i = en[dd];
    while (i != en[ddd] - plusminus[ddd])
    {
        int j = en[dd];
        while (j != en[ddd] - plusminus[ddd])
        {
            if (i + yy[d] >= 0 && i + yy[d] <= n - 1 && j + xx[d] <= n - 1 && j + xx[d] >= 0 && map[i][j] == map[i + yy[d]][j + xx[d]])
            {
                map[i][j] = 0;
                map[i + yy[d]][j + xx[d]] *= 2; // �������� ������ ���X2
            }
            j += plusminus[dd];
        }
        i += plusminus[dd];
    }
}

int maxscore() // ����ū ���� ���ϱ�
{
    int mmax = 1;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            mmax = max(mmax, map[i][j]);
        }
    }
    return mmax;
}

void dfs(int level) // 5�� �����̴� ��� ��� dfs
{
    if (level == 5) // 5�� �����ε� ����ū ���� ����
    {
        ans = max(ans, maxscore());
        return;
    }
    for (int i = 0; i < 4; i++)
    {
        vector<int> mapcopy[20]; // �� �����صα�
        for (int i = 0; i < n; i++)
        {
            mapcopy[i] = map[i];
        }
        slide(i); // �����̰�
        make(i); // ��ġ��
        slide(i); // �����̰�
        path.push_back(i);
        dfs(level + 1);
        path.pop_back();
        for (int i = 0; i < n; i++) // �� ����
        {
            map[i] = mapcopy[i];
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie();
    cout.tie();
    
    cin >> n;
    en.push_back(0);
    en.push_back(n-1); // en�� 0 �Ǵ� n-1�� ����
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            int a;
            cin >> a;
            map[i].push_back(a);
        }
    }
    dfs(0);
    cout << ans;
    return 0;
}