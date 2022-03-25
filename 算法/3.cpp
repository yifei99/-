#include<iostream>
using namespace std;

bool map[16][16] = { false };
bool flag = false;
int step;
int a[6] = { -1,1,0,0,0 }, b[6] = { 0,0,-1,1,0 };   //����������

bool judge()      //�ж��Ƿ�ȫ��ͬɫ
{
	for (int i = 1; i <= 4; i++)     //���λ�ã���������ֻҪ�ж��ĸ�
		for (int j = 1; j <= 4; j++)
		{
			if (map[i][j] != map[1][1])
				return false;
		}
	return true;
}
void flip(int row, int col)     //��ת����
{
	for (int i = 0; i <= 4; i++)
		map[row + a[i]][col + b[i]] = !map[row + a[i]][col + b[i]];
	return;
}
void dfs(int row, int col, int deep)
{
	if (deep == step)       //�ж��Ƿ��map[1][1]��ת����ǰλ��
	{
		flag = judge();
		return;
	}
	if (flag || row == 5) return; // dfs�������Ǵ����ң����ϵ��£��ʵ�row==5��ʱ���Ѿ�ʵ��
	flip(row, col);
	if (col < 4)                  //����ת���ȫ������һ�飬���Ƿ����
		dfs(row, col + 1, deep + 1);
	else
		dfs(row + 1, 1, deep + 1);
	flip(row, col);              //��ǰ���ѭ���ڼ�����������������򷭻���
	if (col < 4)
		dfs(row, col + 1, deep);
	else
		dfs(row + 1, 1, deep);
	return;
}
int main()
{
	char fir;
	for (int i = 1; i <= 4; i++)
		for (int j = 1; j <= 4; j++)
		{
			cin >> fir;
			if (fir == 'b') map[i][j] = true;    //������Ϊtrue������Ϊfalse
		}

	for (step = 0; step <= 16; step++)     //�����Ҫ��4*4��16����
	{
		dfs(1, 1, 0);
		if (flag) break;
	}
	if (flag)
		cout << step << endl;
	else
		cout << "Impossible" << endl;
	return 0;
}
