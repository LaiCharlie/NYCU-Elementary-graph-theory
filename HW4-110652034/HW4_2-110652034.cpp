#include <iostream>
#include <string>
#include <cstring>
#include <algorithm>
#include <vector>
#include <queue>
#include <unistd.h>

using namespace std;

const int V = 10005;

struct Edge {
    int to, flow, cap, rev;
    Edge(int _to, int _flow, int _cap, int _rev): to(_to), flow(_flow), cap(_cap), rev(_rev) {}
};

vector<Edge> e[V];
int  vist[V];

void add_edge(int from, int to, int cap) {
    e[from].push_back(Edge(to, 0, cap, e[to].size()));
    e[to].push_back(Edge(from, 0, 0, e[from].size() - 1));
}

bool dfs(int u, int v){
    memset(vist, -1, sizeof(vist));
    vist[u] = 0;

    queue<int> q;
    q.push(u);
    while(!q.empty()){
        int node = q.front();
        q.pop();
        for(auto i : e[node]){
            if(vist[i.to] < 0 && i.flow < i.cap){
                vist[i.to] = vist[node] + 1;
                q.push(i.to);
            }
        }
    }

    if(vist[v] > 0) return true;
    else return false;
}

int sflow(int c, int t, int f) {
    if(c == t) return f;

    for(int i = 0; i < e[c].size(); i++){
        Edge &temp = e[c][i];

        if(temp.cap > temp.flow && vist[temp.to] == vist[c] + 1){
            int d = sflow(temp.to, t, min(f, temp.cap - temp.flow));
            if (d > 0) {
                temp.flow += d;
                e[temp.to][temp.rev].flow -= d;
                return d;
            }
        }
    }

    return 0;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);

    int n, m, k;
    cin >> n >> m >> k;

    for(int i = 1; i <= n; i++){
        int p, q;
        cin >> p;
        while(p--){
            cin >> q;
            add_edge(i, (n + q), 1);
        }
        add_edge(0, i, 2);
    }

    add_edge((n+m+1), 0, n+k);
    for(int i = 1; i <= m; i++)
        add_edge((n+i), (n+m+2), 1);

    // hero ->  1  ~  n
    // mons -> n+1 ~ n+m
    // S -> n+m+1
    // T -> n+m+2

    int ans = 0, tf = 0;
    while(dfs(n+m+1, n+m+2)){
        while((tf = sflow(n+m+1, n+m+2, n+k) > 0)){
            ans += tf;
        }
    }
    cout << ans << '\n';

    return 0;
}

// 3 5 2
// 4 1 2 3 5
// 2 2 5
// 2 1 2


// 5 10 2
// 2 3 10
// 5 1 3 4 6 10
// 5 3 4 6 8 9
// 3 1 9 10
// 5 1 3 6 7 10
