#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;
typedef long long ll;

int n, map[101][101];
//dp: map[y][x]갈 수 있는 경우의 수
ll dp[101][101];

ll method(int y, int x) {
	if (y<0 || y > n || x<0 || x > n)return 0;
	if (dp[y][x]) return dp[y][x];
	if (y == n && x == n) return 1;
	if (map[y][x] == 0)return 0;

	int nx = x + map[y][x];
	int ny = y + map[y][x];
	if (nx <= n) dp[y][x] += method(y, nx);
	if (ny <= n) dp[y][x] += method(ny, x);
	
	return dp[y][x];
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);

	cin >> n;
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++)
			cin >> map[i][j];
	}
	cout << method(1, 1) << endl;

	return 0;
}