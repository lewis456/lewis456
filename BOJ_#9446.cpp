#include <iostream>
#include <memory.h>
#include <vector>
#include <queue>
#include <algorithm>
#include <utility>
using namespace std;

#define MAX 100001

int T, n, cnt;
int s[MAX];		//i번째 학생이 지목한 학생 인덱스 저장
bool visited[MAX], cycle[MAX];

void dfs(int i) {
	visited[i] = true;
	int next = s[i];		//next는 i번째 학생이 지목한 학생

	if (!visited[next]) {	//아직 간 적 없는 노드
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
