#include <iostream>
#include <memory.h>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

vector<int> com[101];
bool visited[101] = { false, };
int n, m, rst = -1;		//1번 컴퓨터는 포함하지 않음

void dfs(int);

int main() {
	cin >> n >> m;
	for (int i = 0; i < m; i++) {
		int a, b;
		cin >> a >> b;

		//서로 연결 되어있음
		com[a].push_back(b);
		com[b].push_back(a);
	}
	dfs(1);
	cout << rst << endl;
}

void dfs(int n) {
	for (int i = 0; i < com[n].size(); i++) {		//n번 컴퓨터와 연결되어 있는 컴퓨터들 탐색
		int next = com[n][i];
		if (visited[next] == false) {
			visited[next] = true;
			rst++;
			dfs(next);
		}
	}
}