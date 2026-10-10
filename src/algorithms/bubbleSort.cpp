#include <bits/stdc++.h>
#include <cctype>
using namespace std;

#define op ios::sync_with_stdio(false); cin.tie(NULL);
#define int long long
#define endl '\n'

signed main() {
    op

    vector<int> v = {1, 2, 3, 4 , 5};
    int temp, cont = 0;
    
    for(int i = 0; i < v.size(); i++){
        
        bool aux = false;
        for(int j=0; j< (v.size()- i - 1); j++){
            cont++;
            if(v[j] > v[j+1]){
                temp = v[j];
                v[j] = v[j+1];
                v[j+1] = temp;
                aux = true;
            }
        }
        if (!aux) break;
    }

    cout << "contador: " << cont << endl;
    for(int i = 0; i < v.size(); i++){
        cout << v[i] << " " ;
    }
}