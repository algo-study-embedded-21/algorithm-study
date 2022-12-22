#include<iostream>
#include<vector>
#include<algorithm>
#include<cstring>

using namespace std;

struct gps { int y, x; };

int n;
int map[100][100]; // �����̰� �پ��ִ��� ����
int row[100][100]; // ���� ���ӵ� ���� ǥ��
int col[100][100]; // ���� ���ӵ� ���� ǥ��

int ans = -1;

void post(gps st)
{
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			map[st.y + i][st.x + j] = 1;
		}
	}
}

void square()
{
	for (int i = 0; i < 100; i++)
	{
		int rowcnt = 1;
		int colcnt = 1;
		int rownum = row[0][i];
		int colnum = col[i][0];
		ans = max(ans,max(rowcnt * rownum, colcnt * colnum));
		int j = 1;
		while (j < 100)
		{
			if (rownum == row[j][i])
			{
				rowcnt++;
				ans = max(ans, rowcnt * rownum);
			}
			else
			{
				rownum = row[j][i];
				rowcnt = 1;
				ans = max(ans, rowcnt * rownum);
			}
			if (colnum == col[i][j])
			{
				colcnt++;
				ans = max(ans, colcnt * colnum);
			}
			else
			{
				colnum = col[i][j];
				colcnt = 1;
				ans = max(ans, colcnt * colnum);
			}
			j++;
		}
	}
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie();
	cout.tie();

	cin >> n;
	for (int i = 0; i < n; i++)
	{
		int x, y;
		cin >> x >> y;
		post({ y,x }); // ������ ���̱�
	}
	for (int i = 0; i < 100; i++)
	{
		for (int j = 0; j < 100; j++)
		{
			if (map[i][j] == 1)
			{
				if (i == 0) col[i][j] = 1;
				else col[i][j] = col[i - 1][j] + 1;
				if (j == 0)row[i][j] = 1;
				else row[i][j] = row[i][j - 1] + 1;
			}
		}
	}
	square();
	cout << ans;
	
	return 0;
}