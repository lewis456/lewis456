#include <iostream>
#include <algorithm>
#include <vector>
#include <cstring>
using namespace std;
#define MAX 100001
int n, m, a[MAX];

int main() {
	cin >> n;
	for (int i = 0; i < n; i++)
		cin >> a[i];
	sort(a, a + n);			//오름차순 정렬
	cin >> m;
	vector<int> v;
	for (int i = 0; i < m; i++) {
		int tmp;
		cin >> tmp;
		v.push_back(tmp);
	}
	for (int i = 0; i < v.size(); i++) {
		int high = n-1;
		int low = 0;
		bool check = false;
		while (low <= high) {
			int mid = (low + high) / 2;
			if (a[mid] == v[i]) {
				check = true;
				break;
			}
			else if (a[mid] > v[i])
				high = mid - 1;
			else 
				low = mid + 1;
		}
		if (check) cout << "1 ";
		else cout << "0 ";
	}
}