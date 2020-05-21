#include <iostream>
#include <memory.h>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

int n;
vector<pair<int, int>> v;

int main() {
	cin >> n;
	for (int i = 0; i < n; i++) {
		int	start, end;
		cin >> start >> end;
		v.push_back(make_pair(end, start));
	}
	sort(v.begin(), v.end());		//����ð� ���� �������� ����
									//���� ������ ȸ�ǵ��� ����Ͽ� ��� ����

	int current = 0, rst = 0;
	for (int i = 0; i < n; i++) {
		if (current <= v[i].second) {		//������ ������ ȸ���� ���
			current = v[i].first;
			rst++;
		}
	}

	cout << rst << endl;

	return 0;
}