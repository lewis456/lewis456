#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

int n, g[10001], dp[10001];
//dp: i개의 잔 까지의 최대 포도주 양

int main() {
	cin >> n;
	for (int i = 1; i <= n; i++) cin >> g[i];
	dp[1] = g[1];
	dp[2] = g[1] + g[2];

	//i번째 잔 마시는 경우와 안마시는 경우의 최댓값
	for (int i = 3; i <= n; i++) {
		dp[i] = max(dp[i - 1], max(g[i] + g[i - 1] + dp[i - 3], g[i] + dp[i - 2]));
	}
	cout << dp[n] << endl;
	return 0;
}