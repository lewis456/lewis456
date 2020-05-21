#include <iostream>
#include <memory.h>
#include <vector>
#include <queue>
#include <algorithm>
#include <utility>
using namespace std;

#define MAX 100001

int T, n, cnt;
int s[MAX];		//i��° �л��� ������ �л� �ε��� ����
bool visited[MAX], cycle[MAX];

void dfs(int i) {
	visited[i] = true;
	int next = s[i];		//next�� i��° �л��� ������ �л�

	if (!visited[next]) {	//���� �� �� ���� ���
		dfs(next);
	}

	else if (!cycle[next]) {
		cnt++;
		for (int j = next; j != i; j = s[j]) {
			cycle[j] = true;
			cnt++;
		}
	}
	cycle[i] = true;
}

int main() {
	cin >> T;
	for (int test = 0; test < T; test++) {
		cnt = 0;
		memset(cycle, false, sizeof(cycle));
		memset(visited, false, sizeof(visited));

		cin >> n;
		for (int i = 1; i <= n; i++) cin >> s[i];

		for (int i = 1; i <= n; i++) {
			if (!visited[i]) dfs(i);
		}
		cout << n - cnt << endl;
	}
}
