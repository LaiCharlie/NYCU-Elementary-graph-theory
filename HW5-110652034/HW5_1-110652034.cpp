#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <iomanip>
#include <cstring>
#include <map>
#include <sstream>
using namespace std;

#define F first
#define S second

typedef long long ll;
typedef pair<int,int> pii;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);

    // freopen("in.txt","r",stdin);
    // freopen("out.txt","w",stdout);

    int c;
    cin >> c;
    while(c--){
        bool ans = true;
        int n, m, u, v;
        cin >> n >> m;
        vector<pii> edge;
        for(int i = 0; i < m; i++){
            cin >> u >> v;
            edge.push_back(make_pair(u, v));
        }

        for(int t = 0; t < (1<<m); t++){
            int edg[30][30];
            int deg[30];
            memset(edg, 0, sizeof(edg));
            memset(deg, 0, sizeof(deg));
            
            int temp = t;
            for(int i = 0; i < m; i++){
                if(temp & 1){
                    edg[edge[i].first][edge[i].second] = 1;
                    edg[edge[i].second][edge[i].first] = 1;

                    deg[edge[i].first]++;
                    deg[edge[i].second]++;
                }
                temp = temp >> 1;
            }

            while(true){
                bool flg = true;

                for(int i = 1; i < n+1; i++){
                    if(deg[i] == 2){
                        int tu = 0, tv = 0;
                        for(int j = 1; j < n+1; j++){
                            if(edg[i][j]){
                                if(!tu) tu = j;
                                else tv = j;
                            }
                        }
                        if(edg[tu][tv]){
                            deg[tu]--;
                            deg[tu]--;
                        }
                        edg[tu][tv] = 1;
                        edg[tv][tu] = 1;

                        edg[tu][i]  = 0;
                        edg[tv][i]  = 0;
                        edg[i][tu]  = 0;
                        edg[i][tv]  = 0;

                        deg[i] = 0;
                        flg = false;
                        break;
                    }
                }

                if(flg) break;
            }
            // ----------------------------

            vector<int> sg;
            // K3,3
            for(int i = 1; i < n+1; i++)
                if(deg[i] == 3)
                    sg.push_back(i);

            if(sg.size() == 6){
                sort(sg.begin(), sg.end());
                do{
                    bool flg = false;
                    for(int i = 0; i < 3; i++){
                        for(int j = i+1; j < 3; j++){
                            if(edg[sg[i]][sg[j]])
                                flg = true;
                        }
                    }

                    for(int i = 3; i < 6; i++){
                        for(int j = i+1; j < 6; j++){
                            if(edg[sg[i]][sg[j]])
                                flg = true;
                        }
                    }

                    for(int i = 0; i < 3; i++){
                        for(int j = 3; j < 6; j++){
                            if(edg[sg[i]][sg[j]] == 0)
                                flg = true;
                        }
                    }
                    if(!flg) ans = false;
                    if(!ans) break;
                }while(next_permutation(sg.begin(), sg.end()));
            }
            sg.clear();
            // -----------------------------------

            // K5
            for(int i = 1; i < n+1; i++)
                if(deg[i] == 4)
                    sg.push_back(i);
            
            if(sg.size() == 5){
                sort(sg.begin(), sg.end());
                do{
                    bool flg = false;
                    for(int i = 0; i < 5; i++){
                        for(int j = i+1; j < 5; j++){
                            if(edg[sg[i]][sg[j]] == 0)
                                flg = true;
                        }
                        if(deg[sg[i]] != 4) 
                            flg = true;
                    }
                    if(!flg) ans = false;
                    if(!ans) break;
                }while(next_permutation(sg.begin(), sg.end()));
            }
            sg.clear();
            if(!ans) break;
        }

        if(ans)
            cout << "Yes\n";
        else
            cout << "No\n";
    }

    return 0;
}

// 2
// 6 10
// 2 6
// 2 5
// 2 3
// 2 4
// 3 4
// 3 6
// 3 5
// 4 5
// 4 6
// 5 6
// 6 10
// 1 6
// 1 5
// 2 6
// 2 4
// 2 3
// 3 4
// 3 5
// 4 6
// 4 5
// 5 6
