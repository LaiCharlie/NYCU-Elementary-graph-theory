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

bool sstr(string a, string b){
    if(a == b)
        return false;
    if(a.length() < b.length())
        return false;
    
    for(int i=0; i <= a.length()-b.length(); i++){
        if(a.substr(i,b.length()) == b)
            return true;
    }
    return false;
}

string cstr(string a, string b){
    int com = min(a.length(), b.length());
    for(int i=com; i>=0; i--){
        if(a.substr(a.length()-i) == b.substr(0,i))
            return a.substr(0,a.length()-i) + b;
    }
    return a+b;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);

    // freopen("in.txt","r",stdin);
    // freopen("out.txt","w",stdout);

    int n;
    cin >> n;
    vector<string> ele;
    string temp;
    for(int i=0;i<n;i++){    
        cin >> temp;
        ele.push_back(temp);
    }
    sort(ele.begin(),ele.end());
    set<string> less;
    for(int i=0;i<n;i++){
        bool exist = false;
        for(int j=0;j<n;j++){
            if(i==j) continue;
            if(sstr(ele[j],ele[i]))
                exist = true;
        }
        if(!exist)
            less.insert(ele[i]);
    }
    n = less.size();
    ele.clear();
    for(auto i:less)
        ele.push_back(i);

    string ans(50,'z');
    do{
        temp = ele[0];
        for(int i=1;i<n;i++)
            temp = cstr(temp,ele[i]);
        
        if(ans.length() > temp.length())
            ans = temp;
        if(ans.length() == temp.length() && ans > temp)
            ans = temp;
    }while(next_permutation(ele.begin(),ele.end()));

    cout << ans << '\n';

    return 0;
}

// 4
// i
// love
// saito
// asuka

// 11
// genshin
// impact
// start
// hee
// hee
// hee
// i
// am
// a
// klee
// player