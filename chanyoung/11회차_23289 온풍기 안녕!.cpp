#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <cmath>
#include <string.h>
using namespace std;

struct gps { int y, x; };

int r, c, k;
int w;
int map[20][20];
vector<gps> heater; // ��ǳ����� ��ġ
vector<gps> check;  // �µ� üũ�� �ؾ��ϴ� ������ ��ġ
int rwall[19][20]; // ���κ� ǥ��
int cwall[20][19]; // ���κ� ǥ��
int temp[20][20]; // �µ�ǥ
int plustemp[20][20]; // �µ� ��ȭ ǥ
int choco; // ���ݸ� ����

int yy[4] = { 0,0,-1,1 };
int xx[4] = { 1,-1,0,0 };

int pos(gps now, gps next) // now���� next�� ���� ���������� 1��ȯ
{
    if (next.y > now.y && rwall[now.y][now.x] == 0)return 0;
    else if (next.y < now.y && rwall[next.y][next.x] == 0)return 0;
    else if (next.x > now.x && cwall[now.y][now.x] == 0)return 0;
    else if (next.x < now.x && cwall[now.y][next.x] == 0)return 0;
    else return 1;
}

int outmap(gps next) // next�� �� ������ ������ 1 ��ȯ
{
    if (next.y<0 || next.y>r - 1 || next.x<0 || next.x>c - 1)return 1;
    else return 0;
}

void tempplus() // �µ� ��ȭ �ջ�
{
    for (int i = 0; i < r; i++){
        for (int j = 0; j < c; j++){
            temp[i][j] += plustemp[i][j];
        }
    }
}

void wind(gps st) // �ٶ� �ұ�
{
    queue<gps> q;
    int d = map[st.y][st.x] - 1;
    st = { st.y + yy[d],st.x + xx[d] };
    q.push(st);
    int visit[20][20] = { 0 };
    visit[st.y][st.x] = 5;
    int zero = 5;
    while (!q.empty() && zero>0) // ���̻� �ٶ��Ұ��� ���ų� �߰��Ǵ� �µ��� ������ ����
    {
        gps now = q.front();
        q.pop();
        for (int i = 0; i < 3; i++)
        {
            gps next;
            if (i == 0) // ���ư��� ����
            {
                next = { now.y + yy[d],now.x + xx[d] };
                if (outmap(next))continue;
                if (pos(now, next)) continue;
            }
            else if (i == 1) // ù��° �밢 ����
            {
                if (d < 2) // �¿� ������ ��� 
                {
                    next = { now.y + yy[2],now.x + xx[2] }; // �ϴ� ���Ϸ� �̵� �������� 
                    if (outmap(next))continue;
                    if (pos(now, next)) continue;
                    gps mid = next;
                    next = { mid.y + yy[d],mid.x + xx[d] }; // ���� �¿�� �̵���������
                    if (outmap(next))continue;
                    if (pos(mid, next))continue;
                }
                else // ���� ������ ���
                {
                    next = { now.y + yy[0],now.x + xx[0] }; // �¿�� �̵� ��������
                    if (outmap(next))continue;
                    if (pos(now, next)) continue;
                    gps mid = next;
                    next = { mid.y + yy[d],mid.x + xx[d] }; // ���Ϸ� �̵� ��������
                    if (outmap(next))continue;
                    if (pos(mid, next))continue;
                }
            }
            else // �ι�° �밢 ����
            {
                if (d < 2)
                {
                    next = { now.y + yy[3],now.x + xx[3] };
                    if (outmap(next))continue;
                    if (pos(now, next)) continue;
                    gps mid = next;
                    next = { mid.y + yy[d],mid.x + xx[d] };
                    if (outmap(next))continue;
                    if (pos(mid, next))continue;
                }
                else
                {
                    next = { now.y + yy[1],now.x + xx[1] };
                    if (outmap(next))continue;
                    if (pos(now, next)) continue;
                    gps mid = next;
                    next = { mid.y + yy[d],mid.x + xx[d] };
                    if (outmap(next))continue;
                    if (pos(mid, next))continue;
                }
            }
            visit[next.y][next.x] = visit[now.y][now.x] - 1;
            zero = visit[next.y][next.x]; // �߰��Ǵ� �µ� ����
            q.push(next);
        }
    }
    for (int i = 0; i < r; i++){
        for (int j = 0; j < c; j++){
            plustemp[i][j] += visit[i][j];
        }
    }
}

int checking() // �������� Ž��
{
    for (int i = 0; i < check.size(); i++)
    {
        gps ch = check[i];
        if (temp[ch.y][ch.x] < k) return 0;
    }
    return 1;
}

void avg() // �µ� ����
{
    for (int i = 0; i < r; i++)
    {
        for (int j = 0; j < c; j++)
        {
            gps now = { i,j };
            int nowtemp = temp[now.y][now.x]; // ���� ��ġ�� �µ�
            for (int d = 1; d < 3; d++) // �ߺ��� ���ϱ����� ��,�� �������θ� ����
            {
                gps next = { now.y + yy[d],now.x + xx[d] };
                if (outmap(next))continue;
                if (pos(now, next))continue;
                int nexttemp = temp[next.y][next.x]; // �α� ��ġ�� �µ�
                if (nowtemp > nexttemp) // ������ġ�� �� ���� �µ�
                {
                    int m = (nowtemp - nexttemp) / 4;
                    plustemp[now.y][now.x] -= m;
                    plustemp[next.y][next.x] += m;
                }
                else if (nexttemp > nowtemp) // �α� ��ġ�� �� ���� �µ�
                {
                    int m = (nexttemp - nowtemp) / 4;
                    plustemp[next.y][next.x] -= m;
                    plustemp[now.y][now.x] += m;
                }
            }
        }
    }
}

void heating() // ��� ���μ���
{
    while (choco <= 100)
    {
        for (int n = 0; n < heater.size(); n++)
        {
            gps h = heater[n];
            memset(plustemp, 0, sizeof(plustemp));
            wind(h);
            tempplus();
        }
        memset(plustemp, 0, sizeof(plustemp));
        avg();
        tempplus();
        for (int i = 0; i < r; i++){ // �ܰ� �µ� 1�� ����
            for (int j = 0; j < c; j++){
                if ((i == 0 || i == r - 1 || j == 0 || j == c - 1) && temp[i][j] > 0) temp[i][j] -= 1;
            }
        }
        choco++;
        if (checking())return; // ��������
    }
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie();
    cout.tie();

    cin >> r >> c >> k;
    for (int i = 0; i < r; i++)
    {
        for (int j = 0; j < c; j++)
        {
            cin >> map[i][j];
            if (map[i][j] == 5)check.push_back({ i,j });
            else if (map[i][j] > 0) heater.push_back({ i,j });
        }
    }
    cin >> w;
    for (int i = 0; i < w; i++)
    {
        int x, y, t;
        cin >> x >> y >> t;
        if (t == 0) rwall[x - 2][y - 1] = 1;
        else cwall[x - 1][y - 1] = 1;
    }
    heating();
    cout << choco;
    return 0;
}