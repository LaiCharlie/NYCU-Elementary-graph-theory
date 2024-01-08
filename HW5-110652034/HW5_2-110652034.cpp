#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <iomanip>
#include <cstring>
#include <map>
#include <queue>
#include <sstream>

using namespace std;

#define F first
#define S second

typedef long long ll;
typedef pair<int,int> pii;

int capa[100][100];
int flow[100][100];
int par[100];
int vis[100];
int n, m;

int bfs(int u, int v){
    memset(par, 0, sizeof(par));
    memset(vis, 0, sizeof(vis));
    vis[u] = 1;

    queue<pii> q;
    q.push(make_pair(u, 1000));

    while(!q.empty()){
        pii node = q.front();
        q.pop();
        vis[node.first] = 1;
        for(int i = 1; i < n+1; i++){
            if(flow[node.first][i] && !vis[i]){
                par[i] = node.first;
                q.push(make_pair(i, min(node.second, flow[node.first][i])));
                if(i == v)
                    return min(node.second, flow[node.first][i]);
            }
        }
    }
    return 0;
}

void cpy(){
    for(int i = 0; i < n + 1; i++)
        for(int j = 0; j < n + 1; j++)
            flow[i][j] = capa[i][j];
}

// K-connect -> find min cut
// max flow = min cut

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);

    // freopen("in.txt","r",stdin);
    // freopen("out.txt","w",stdout);

    memset(capa, 0, sizeof(capa));
    memset(flow, 0, sizeof(flow));

    int u, v;
    cin >> n >> m;
    for(int i = 0; i < m; i++){
        cin >> u >> v;
        flow[u][v] = 1;
        flow[v][u] = 1;
        capa[u][v] = 1;
        capa[v][u] = 1;
    }

    int ans = 1000;
    for(int i = 1; i < n+1; i++){
        for(int j = i+1; j < n+1; j++){
            cpy();
            int f = 0, tmp = 0, node;
            while((tmp = bfs(i, j)) > 0){
                f += tmp;
                node = j;
                while(par[node]){
                    flow[par[node]][node] -= tmp;
                    flow[node][par[node]] += tmp;
                    node = par[node];
                }
            }
            ans = min(ans, f);
        }
    }

    cout << ans << '\n';

    return 0;
}

// 4 4
// 1 2
// 2 3
// 3 4
// 4 1

// 4 6
// 1 2
// 1 3
// 1 4
// 2 4
// 2 3
// 3 4