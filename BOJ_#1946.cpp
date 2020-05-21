#include <iostream>
#include <memory.h>
#include <vector>
#include <queue>
#include <algorithm>
#include <utility>
using namespace std;

int t, n;

int main() {
	cin >> t;
	while(t--) {
		vector<pair<int, int>> v;
		cin >> n;
		for (int i = 0; i < n; i++) {
			int a, b;
			cin >> a >> b;
			v.push_back(make_pair(a, b));
		}
		sort(v.begin(), v.end());		//ù��° ���� ���� ��������
										//�ι�° ������ ���ϸ� ��
		int cur = v[0].second;
		int ans = 1;
		for (int i = 1; i < n; i++) {
			if (v[i].second < cur) {	//�� ���� ������ ���� �ִ�� �ø� �� ����
				ans++;
				cur = v[i].second;
			}
		}
		cout << ans << endl;
	}
	
	return 0;
}