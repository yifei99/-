#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int maxn = 10010;

int n, mid, ans = 0;
int x[maxn], y[maxn];
//����y�ᣬ�ܲ���Ϊ��|y[i]-mid|������x�ᣬ�ܲ���Ϊ��|x[i]-(mid+i)|=��|(x[i]-i)-mid|

int main()
{
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) scanf("%d%d", &x[i], &y[i]);
	sort(x + 1, x + n + 1);
	for (int i = 1; i <= n; i++) x[i] -= i;//Ԥ����x[i]-i
	sort(x + 1, x + n + 1);
	mid = x[(1 + n) / 2];
	for (int i = 1; i <= n; i++) ans += abs(mid - x[i]);

	sort(y + 1, y + n + 1);
	mid = y[(1 + n) / 2];
	for (int i = 1; i <= n; i++) ans += abs(mid - y[i]);

	printf("%d\n", ans);
	return 0;
}