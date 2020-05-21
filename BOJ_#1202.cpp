#include <iostream>
#include <memory.h>
#include <vector>
#include <queue>
#include <algorithm>
#include <utility>
using namespace std;

int n, k;
long long rst = 0;
vector<pair<int, int>> jam;
vector<int> bag;
priority_queue<int> pq;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);

	cin >> n >> k;
	for (int i = 0; i < n; i++) {
		int a, b;
		cin >> a >> b;
		jam.push_back(make_pair(a, b));
	}
	for (int i = 0; i < k; i++) {
		int w;
		cin >> w;
		bag.push_back(w);
	}

	sort(jam.begin(), jam.end());			//���� ���Լ� �������� ����
	sort(bag.begin(), bag.end());			//���� ���Լ� �������� ����
											//���� ���濡 ���� ��� ���� �ֱ�

	//i��° ���濡 �� �� �ִ� ������ i+n��° ���濡�� �� �� ����
	//i��° ���濡 ������ ������ �켱����ť�� �ְ� �����Ѱ� pop
	//���� ���濡���� �׺��� ���ſ� ������ ����ϸ� ť�� ������ ��

	for (int i = 0, j = 0; i < k; i++) {
		while (bag[i] >= jam[j].first && j < n)
			pq.push(jam[j++].second);

		if (!pq.empty()) {
			rst += pq.top();
			pq.pop();
		}
	}
	cout << rst << endl;
	return 0;
}