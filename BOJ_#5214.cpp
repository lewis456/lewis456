#include <iostream>
#include <memory.h>
#include <vector>
#include <queue>
#include <algorithm>
#include <utility>
using namespace std;

#define MAX 100001

int n, k, m;
int ans = 1;
vector<int> v[MAX+MAX];
queue<int> q;
bool visited[MAX+MAX];

int main() {
	cin >> n >> k >> m;
	//n:��ü �� ����  k:������Ʃ�갡 �����ϴ� �� ��  m:������Ʃ�� ��
	for (int i = 1; i <= m; i++) {
		for (int j = 0; j < k; j++) {
			int temp;
			cin >> temp;
			//i��° ������Ʃ�꿡 k���� ���� ����
			v[i + n].push_back(temp);
			//���� ������Ʃ�꿡 ����
			v[temp].push_back(i + n);
		}
	}
	q.push(1);
	visited[1] = true;
	while (!q.empty()) {
		int size = q.size();
		while (size--) {
			int cur = q.front();	//���� ���캼 ��
			q.pop();
			if (cur == n) {
				cout << ans/2+1 << endl;
				return 0;
			}
			for (auto &i : v[cur]) {	//i:���� ���� ����� ��
					if (visited[i]) continue;
					q.push(i);
					visited[i] = true;
			}
		}
		ans++;
	}
	cout << -1 << endl;
	return 0;
}