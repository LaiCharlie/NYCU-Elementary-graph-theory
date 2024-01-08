#include <iostream>
#include <map>
#include <cmath>

using namespace std;

int main(){

    int n;
    cin >> n;

    map<int,int> mp;

    for(int i=0;i<n;i++){
        int tmp;
        cin >> tmp;
        mp[tmp]++;
    }


    int ans = 0;
    int amount = 0;
    for(auto i:mp){
        // cout << i.first << ' ' << i.second << '\n';
        if(i.second > amount)
            amount = i.second;
        if(i.second == amount)
            ans = max(ans,i.first);
    }
    cout << ans << ' ' << amount << '\n';

    return 0;
}