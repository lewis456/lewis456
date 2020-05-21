#include <iostream>
#include <algorithm>
#include <vector>
#include <cstring>
using namespace std;

#define MAX 10001
typedef long long ll;

int k, n;
ll a[MAX];
bool binary(ll a[], ll cut){
	int sum = 0;
	for (int i = 0; i < k; i++) {
		int tmp = a[i] / cut;
		sum += tmp;
		if (sum >= n) return true;
	}
	return false;
}

int main() {
	cin >> k >> n;
	for (int i = 0; i < k; i++) {
		cin >> a[i];
	}

	ll low = 1, high = *max_element(a, a+k), mid;
	while (low <= high) {
		mid = (low + high) / 2;
		if (binary(a, mid))
			low = mid + 1;
		else
			high = mid - 1;
	}
	cout << high << endl;

	return 0;
}