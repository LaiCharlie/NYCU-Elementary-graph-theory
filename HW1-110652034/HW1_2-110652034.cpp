#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <cstring>
#include <queue>
using namespace std;

bool bfs(int init, int n, queue<int> mp[]){
    queue<int> q;
    q.push(init);

    int c[n];
    memset(c,0,sizeof(c));

    while(!q.empty()){
        int temp = q.front();
        q.pop();

        if(c[temp]==0)
            c[temp] = 1;

        while(!mp[temp].empty()){
            int node = mp[temp].front();
            mp[temp].pop();

            if(c[node]==0){
                c[node] = ((c[temp]==1) ? 2 : 1);
                q.push(node);
            }
            else if(c[node]==c[temp])
                return false;
        }
    }
    return true;
}

void solve(){
    int n,m;
    cin>>n>>m;
    queue<int> mp[n];
    int init = n;
    for(int i=0;i<m;i++){
        int l,r;
        cin>>l>>r;
        mp[l-1].push(r-1);
        mp[r-1].push(l-1);
        init = min(l-1,init);
        init = min(r-1,init);
    }

    bool ans = bfs(init, n, mp);
    if(ans)
        cout << "Yes\n";
    else
        cout << "No\n";

}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);

    solve();

    return 0;
}