#include <iostream>
#include <memory.h>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

vector<int> com[101];
bool visited[101] = { false, };
int n, m, rst = -1;		//1�� ��ǻ�ʹ� �������� ����

void dfs(int);

int main() {
	cin >> n >> m;
	for (int i = 0; i < m; i++) {
		int a, b;
		cin >> a >> b;

		//���� ���� �Ǿ�����
		com[a].push_back(b);
		com[b].push_back(a);
	}
	dfs(1);
	cout << rst << endl;
}

void dfs(int n) {
	for (int i = 0; i < com[n].size(); i++) {		//n�� ��ǻ�Ϳ� ����Ǿ� �ִ� ��ǻ�͵� Ž��
		int next = com[n][i];
		if (visited[next] == false) {
			visited[next] = true;
			rst++;
			dfs(next);
		}
	}
}