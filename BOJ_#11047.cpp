#include <iostream>
#include <memory.h>
#include <vector>
#include <queue>
#include <algorithm>
#include <utility>
using namespace std;

int n, k;
int coin[11];
int ans = 0;

int main() {
	cin >> n >> k;
	for (int i = 0; i < n; i++) {
		cin >> coin[i];
	}
	for (int i = n - 1; i >= 0; i--) {
		int cnt = (k / coin[i]);
		if (cnt !=0) {
			ans += cnt;
			k %=coin[i];
		}
	}
	cout << ans << endl;
	return 0;
}