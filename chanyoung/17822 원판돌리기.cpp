#include<iostream>
#include<string>
#include<vector>
#include<queue>
#include<cstring>
#include<algorithm>
#include<unordered_map>
#include<cmath>

// 1:25 ���� �� ����
// 1:52 �����˻�
// 2:58 �Ϸ�

using namespace std;

struct two
{
	int circle;
	int num;
};

int n, m, t;
int circle[51][50];

void turn(int num,int di,int k) //���� ȸ��
{
	int temp;
	if (di == 1) // �ݽð����
	{
		for (int i = 0; i < k; i++)
		{
			temp = circle[num][0];
			for (int j = 0; j < m - 1; j++)
			{
				circle[num][j] = circle[num][j + 1];
			}
			circle[num][m-1] = temp;
		}
	}
	else // �ð����
	{
		for (int i = 0; i < k; i++)
		{
			temp = circle[num][m-1];
			for (int j = m-1; j >0;j--)
			{
				circle[num][j] = circle[num][j - 1];
			}
			circle[num][0] = temp;
		}
	}
}

void find() // ������ ã�� �����
{
	int flag = 0; // �������� �־����� ����
	vector<two> v; // ���� ������ ��ġ
	long long avg = 0; // ��ü ��հ�
	int cnt = 0; // ���ڰ� �����ִ� ����
	for (int i = 1; i <= n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			flag = 0;
			int now = circle[i][j];
			if (now != -1001) // ������ �� ����
			{
				if (now == circle[i][(j + 1) % m]) // �ٷ� ������ �������
				{
					flag = 1;
					v.push_back({ i,(j + 1) % m });
				}
				if (i!=n && now == circle[i + 1][j]) // ���� ������ ���� �ڸ��� �������(���������� ���� X)
				{
					flag = 1;
					v.push_back({ i + 1,j });
				}
				if (flag == 1)
				{
					v.push_back({ i,j });
				}
				avg += now;
				cnt++;
			}
		}
	}
	if (v.size() != 0) // �������� ���� �ִ°��
	{
		for (int i = 0; i < v.size(); i++)
		{
			circle[v[i].circle][v[i].num] = -1001; // -1�ε� �����ߴ� ***** 0�� �Ұ����ϴ� ******
		}
	}
	else if(cnt !=0 )
	{
		int last = avg % cnt; // ��հ��� �Ҽ����ڸ� ���翩��
		avg = avg / cnt; // ��հ�
		for (int i = 1; i <= n; i++)
		{
			for (int j = 0; j < m; j++)
			{
				if (circle[i][j] > avg) // ��պ��� ū��
				{
					circle[i][j] -= 1;
				}
				else if (circle[i][j] < avg && circle[i][j] != -1001) // ������ ���� �ƴϸ鼭 ��պ��� ������
				{
					circle[i][j] += 1;
				}
				else // ��հ� ��� ���ٸ�
				{
					if (last > 0 && circle[i][j] != -1001)
					{ // ������ ���� �ƴϸ鼭 ��հ��� ���� ������ ��հ��� ����� �Ҽ����� �ִ°�� ��պ��� �۴ٰ� �Ǵ�
						circle[i][j] += 1;
					}
					else if (last < 0 && circle[i][j] != -1001)
					{ // ������ �Ҽ����� �ִ°�� ��պ��� ũ�ٰ� �Ǵ�  >>> ��������� ��� �����ߴ�
						circle[i][j] -= 1;
					}
				}
			}
		}
	}
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie();
	cout.tie();
	
	cin >> n >> m >> t;
	for (int i = 1; i <= n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			int a;
			cin >> a;
			circle[i][j] = a;
		}
	}
	for (int i = 0; i < t; i++) // ���� ���� ���� ������ ���ÿ� ����
	{
		int x, d, k;
		cin >> x >> d >> k;
		int xx = x;
		while (xx <= n) // ���� ������
		{
			turn(xx, d, k); // ������
			xx += x; //��� ���� >>>>>>>>  **** xx += xx �� �ۼ��Ѱ��� ���� Ʋ���κ� ****
		}
		find();
	}
	int ans = 0;
	for (int i = 1; i <= n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			if (circle[i][j] != -1001)
			{
				ans += circle[i][j];
			}
		}
	}
	cout << ans;

	return 0;
}