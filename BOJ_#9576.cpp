#include <iostream>
#include <algorithm>
#include <vector>
#include <cstring>
using namespace std;
bool visited[1001];

bool cmp(pair<int, int> a, pair<int, int> b)
{
	//먼저 뒤의 숫자 기준 오름차순
	if (!(a.second == b.second))
		return a.second < b.second;
	//같다면 앞의 숫자 기준 오름차순
	return a.first < b.first;
}

int main(void){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	int T;
	cin >> T;

	for (int t = 0; t < T; t++){
		memset(visited, false, sizeof(visited));
		int N, M;
		cin >> N >> M;

		vector<pair<int, int>> v;
		for (int i = 0; i < M; i++){
			int a, b;
			cin >> a >> b;
			v.push_back({ a, b });
		}
		//b번을 기준으로 오름차순 정렬
		sort(v.begin(), v.end(), cmp);
		int ans = 0;
		for (int i = 0; i < M; i++) {
			for (int j = v[i].first; j <= v[i].second; j++) {
				if (!visited[j])
				{
					visited[j] = true;
					ans++;
					break;
				}
			}
		}
		cout << ans << endl;
	}

	return 0;

}