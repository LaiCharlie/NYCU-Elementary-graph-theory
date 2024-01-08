#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <iomanip>
#include <cstring>
#include <set>
#include <sstream>
using namespace std;

#define F first
#define S second

typedef long long ll;
typedef pair<int,int> pii;

vector<int> nei[100005];
bool vis[100005];
int  fid[100005];
int  rot[100005];

set<int> ans;

void solve(int v, int& seq, int par){
    seq++;
	vis[v] = true;
    fid[v] = seq;
    rot[v] = seq;

	int chd = 0;
	for(auto i : nei[v]){
		if(!vis[i]){
			chd++;
			solve(i, seq, v);

			rot[v] = min(rot[v], rot[i]);
			if (par && rot[i] >= fid[v])
				ans.insert(v);
		}
		else if(i != par)
			rot[v] = min(rot[v], fid[i]);
	}

	if(!par && chd > 1)
		ans.insert(v);
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    memset(vis, false, sizeof(vis));
    memset(fid, 0, sizeof(fid));
    memset(rot, 0, sizeof(rot));

	int n, m;
    cin >> n >> m;
    for(int i = 0; i < m; i++){
        int p, q;
        cin >> p >> q;
        nei[p].push_back(q);
        nei[q].push_back(p);
    }

    int seq = 0, root = 0;

    for(int i = 1; i <= n; i++){
        if(!vis[i])
            solve(i, seq, root);
    }

    cout << ans.size() << '\n';
    for(auto i : ans)
        cout << i << ' ';
    cout << '\n';

	return 0;
}

// 8 8
// 1 2
// 1 5
// 2 3
// 2 4
// 3 6
// 4 5
// 5 7
// 5 8
