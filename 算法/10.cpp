#include<iostream>
#include<cmath>
#include<algorithm>
#define MAX 0x3f3f3f3f
#define N 10001
using namespace std;
int dx[4] = { 0,1,0,-1 };//��������
int dy[4] = { 1,0,-1,0 };//��������
struct Node {
	int x;
	int y;
}a[N];
int x[N], y[N];
int minn, plan;
int main()
{

	int n;
	scanf_s("%d", &n);
	for (int i = 1; i <= n; i++)
	{
		scanf_s("%d%d", &a[i].x, &a[i].y);
		x[i] = a[i].x;
		y[i] = a[i].y;
	}

	sort(x + 1, x + n + 1);//��x����
	sort(y + 1, y + n + 1);//��y����

	if (n % 2)//nΪ����ʱ
	{
		int temp = (n / 2) + 1;
		for (int i = 1; i <= n; i++)
		{
			if (a[i].x == x[temp] && a[i].y == y[temp])//����Ϊ������
			{
				int Min = MAX;
				for (int l = 0; l < 4; l++)//ö���ĸ�����
				{
					int xx = x[temp] + dx[l];
					int yy = y[temp] + dy[l];
					int sum = 0;
					for (i = 1; i <= n; i++)//����С�ľ���
						sum += abs(a[i].x - xx) + abs(a[i].y - yy);
					if (sum < Min)
					{
						Min = sum;
						plan = 1;
					}
					else if (sum == Min)
						plan++;
				}
				printf("%d %d\n", Min, plan);
				return 0;
			}
			else//���㲻Ϊ������
			{
				minn += abs(a[i].x - x[temp]) + abs(a[i].y - y[temp]);//��¼��С����
				plan = 1;//������Ϊ1
			}
		}
		printf("%d %d\n", minn, plan);
	}
	else//nΪż��ʱ
	{
		int temp1 = n / 2, temp2 = n / 2 + 1;
		plan = (x[temp2] - x[temp1] + 1)*(y[temp2] - y[temp1] + 1);//��������ڵ�ĸ���
		for (int i = 1; i <= n; i++)
		{
			minn += abs(a[i].x - x[temp1]) + abs(a[i].y - y[temp1]);//��¼��С����
			int x0 = a[i].x, y0 = a[i].y;
			if (x[temp1] <= x0 && x0 <= x[temp2] && y[temp1] <= y0 && y0 <= y[temp2])//���·�����
				plan--;
		}
		printf("%d %d\n", minn, plan);
	}
	return 0;
}
