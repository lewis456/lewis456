#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

int n, a[1000], dp[1000], rst=0;

int main() {
	cin >> n;
	for (int i = 0; i < n; i++) {
		dp[i] = 1;
		cin >> a[i];
		for (int j = 0; j < i; j++) {
			if (a[i] > a[j]) dp[i] = max(dp[i], dp[j] + 1);
		}
		rst = max(rst, dp[i]);
	}
	cout << rst << endl;
	return 0;
}