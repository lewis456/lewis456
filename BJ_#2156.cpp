#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

int n, g[10001], dp[10001];
//dp: i���� �� ������ �ִ� ������ ��

int main() {
	cin >> n;
	for (int i = 1; i <= n; i++) cin >> g[i];
	dp[1] = g[1];
	dp[2] = g[1] + g[2];

	//i��° �� ���ô� ���� �ȸ��ô� ����� �ִ�
	for (int i = 3; i <= n; i++) {
		dp[i] = max(dp[i - 1], max(g[i] + g[i - 1] + dp[i - 3], g[i] + dp[i - 2]));
	}
	cout << dp[n] << endl;
	return 0;
}