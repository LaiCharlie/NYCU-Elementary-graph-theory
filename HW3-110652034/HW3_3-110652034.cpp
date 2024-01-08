#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <iomanip>
#include <cstring>
#include <queue>
#include <map>
#include <sstream>
using namespace std;

#define F first
#define S second

typedef long long ll;
typedef pair<int,int> pii;

int  p[100005];
int  h[100005];
vector<int> edge[100005];

int dfs(int node){
    bool test = true;

    for(int i : edge[node]){
        if(p[i] == 0){
            // cout << node << " : " << i << '\n';
            test = false;
            p[i] = node;
            h[node] = max(dfs(i) + 1, h[node]);
        }
    }

    if(test){
        h[node] = 0;
        p[node] = edge[node][0];
        return 0;
    }
    return h[node];
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);

    // freopen("in.txt","r",stdin);
    // freopen("out.txt","w",stdout);

    memset(p, 0, sizeof(p));
    memset(h, 0, sizeof(h));
    // memset(v, false, sizeof(v));

    int n;
    cin >> n;
    p[1] = -1;
    // edge[1].push_back(-1);
    for(int i=1;i<n;i++){
        int u,v;
        cin >> u >> v;
        edge[u].push_back(v);
        edge[v].push_back(u);
    }
    dfs(1);

    for(int i=1;i<=n;i++){
        cout << h[i] << ' ' << p[i] << '\n';
    }

    return 0;
}

// 8
// 1 2
// 2 3
// 3 4
// 1 5
// 5 6
// 5 7
// 1 8

// 10
// 1 2
// 2 10
// 1 6
// 3 10
// 2 8
// 6 7
// 8 9
// 4 6
// 5 10
