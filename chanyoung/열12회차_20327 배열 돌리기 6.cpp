#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <cmath>
#include <string.h>
using namespace std;

struct gps { int y, x; };

int N, R;
vector<int> Cmap[128];
vector<int> Rmap[128];
int endM;

void copymap(int d)  // d=0�϶� Cmap�� Rmap�� ī�� 
{
    for (int i = 0; i < endM; i++)
    {
        for (int j = 0; j < endM; j++)
        {
            if (d) Rmap[i][j] = Cmap[j][i];
            else Cmap[i][j] = Rmap[j][i];
        }
    }
}

void movemap() // Cmap�� tmp�� �̿��Ѱ�� �� �ű��
{
    for (int i = 0; i < endM; i++)
    {
        Rmap[i] = Cmap[i];
    }
}

void cal(int k, int l)
{
    int sep = pow(2, l);
    int block = 1;
    if (k > 4) // 5~8�� ������ 1~4�� ���꿡 ��Ī
    {
        k = k % 4;
        block = sep; // 1����� ������ �κй迭ũ��� ����
        sep = endM; // �κй迭�� ũ�⸦ �迭 ��ü ũ��� ����
    }
    int st = 0;
    if (k == 1) // ���Ϲ���
    {
        for (int i = st; i <= endM - sep; i += sep)
        {
            for (int j = i; j < i + sep / 2; j += block)
            {
                for (int k = 0; k < block; k++)
                {
                    vector<int> tmp = Rmap[j + k];
                    Rmap[j + k] = Rmap[i + sep - block - j + i + k];
                    Rmap[i + sep - block - j + i + k] = tmp;
                }
            }
        }
        copymap(0);
    }
    else if (k == 2) // �¿����
    {
        for (int i = st; i <= endM - sep; i += sep)
        {
            for (int j = i; j < i + sep / 2; j += block)
            {
                for (int k = 0; k < block; k++)
                {
                    vector<int> tmp = Cmap[j + k];
                    Cmap[j + k] = Cmap[i + sep - block - j + i + k];
                    Cmap[i + sep - block - j + i + k] = tmp;
                }
            }
        }
        copymap(1);
    }
    else if (k == 3) // ������ 90�� ȸ��
    {
        for (int ist = st; ist <= endM - sep; ist += sep)
        {
            for (int jst = st; jst <= endM - sep; jst += sep)
            {
                for (int i = ist; i < ist + sep; i += block)
                {
                    for (int j = jst; j < jst + sep; j += block)
                    {
                        for (int a = 0; a < block; a++)
                        {
                            for (int b = 0; b < block; b++)
                            {
                                Cmap[ist - jst + (j + a)][jst + ist + sep - block - (i - b)] = Rmap[i + a][j + b];
                            }
                        }
                    }
                }
            }
        }
        movemap();
        copymap(0);
    }
    else { // ���� 90�� ȸ��
        for (int ist = st; ist <= endM - sep; ist += sep)
        {
            for (int jst = st; jst <= endM - sep; jst += sep)
            {
                for (int i = ist; i < ist + sep; i += block)
                {
                    for (int j = jst; j < jst + sep; j += block)
                    {
                        for (int a = 0; a < block; a++)
                        {
                            for (int b = 0; b < block; b++)
                            {
                                Cmap[ist + sep - block - (j - a) + jst][jst + (i + b) - ist] = Rmap[i + a][j + b];
                            }
                        }
                    }
                }
            }
        }
        movemap();
        copymap(0);

    }
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie();
    cout.tie();

    cin >> N >> R;
    endM = pow(2, N);
    for (int i = 0; i < endM; i++)
    {
        for (int j = 0; j < endM; j++)
        {
            int num;
            cin >> num;
            Rmap[i].push_back(num);
            Cmap[i].push_back(0);
        }
    }
    copymap(0);
    for (int i = 0; i < R; i++)
    {
        int k, l;
        cin >> k >> l;
        cal(k, l);
    }
    for (int i = 0; i < endM; i++)
    {
        for (int j = 0; j < endM; j++)
        {
            cout << Rmap[i][j] << " ";
        }
        cout << "\n";
    }
    return 0;
}