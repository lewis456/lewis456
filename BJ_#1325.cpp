#include <memory.h>
#include<iostream>
#include <queue>
#include <algorithm>
#include <string>
#include <vector>
using namespace std;

#define MAX 10001

int n, m;					//n:��ǻ�� ��, m:�ŷڰ��� ��
vector<int> com[MAX];		//i��° ��ǻ�͸� ��ŷ�ϸ� ���� ��ŷ�� �� �ִ� ��ǻ��
bool visited[MAX];
int cur_max = 1;
int tmp_ans = 1;
vector<int> ans;

void dfs(int);

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);


	cin >> n >> m;
	for (int i = 1; i <= m; i++) {
		int a, b;
		cin >> a >> b;
		com[b].push_back(a);
	}

	for (int i = 1; i <= n; i++) {
		memset(visited, false, sizeof(visited));
		tmp_ans = 1;
		dfs(i);

		if (cur_max == tmp_ans) 
			ans.push_back(i);
		else if (cur_max < tmp_ans) {
			ans.clear();
			ans.push_back(i);
			cur_max = tmp_ans;
		}
	}

	sort(ans.begin(), ans.end());
	for (int i = 0; i < ans.size(); i++)
		cout << ans[i] << " ";

	return 0;
}

void dfs(int n) {
	visited[n] = true;
	for (int i = 0; i < com[n].size(); i++) {			//�ŷڰ��� ��ǻ�� Ȯ��
		int next = com[n][i];
		if (visited[next] == false) {					//�ߺ� ����
			tmp_ans++;
			dfs(next);
		}
	}
}