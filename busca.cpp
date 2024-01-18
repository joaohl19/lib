#include <bits/stdc++.h>
using namespace std;
#define br "\n"
typedef long long ll;
#define pb push_back
#define pii pair<int, int>
#define pll pair<long long, long long>
#define forn(i, n) for(int i = 0; i < n; i++)

// Busca Binária
bool check(int k, ll sum, vector<int>v){
    int n = v.size();
    int subarray_size = 0;
    ll cur_sum = 0;
    while(subarray_size < n){
        if(cur_sum + v[subarray_size] <= sum){
            cur_sum += v[subarray_size];
            subarray_size++;
        }
        else{
            k--;
            if(k <= 0)return false;
            cur_sum = 0;
        }
    }
    return true;
}
int k;
vector<int> v;
ll binary_search(){
    ll l = 0;
    ll r = 1e18;
    ll res = 0;
    while(l <= r){
        ll mid = (l + r)/2;
        if(check(k, mid,v)){
            r = mid - 1;
            res = mid;
        }
        else{
            l = mid + 1;
        }
    }
    return res;
}


// Busca Completa
int n = 10;
vector<int> subset;
vector<vector<int>>subsets;
void get(vector<int> sub){
    subsets.pb(sub);
}
// 1. Recursiva
void recursive_search(int i){
    if(i == n)get(subset);
    else{
        recursive_search(i + 1);
        subset.pb(i);
        recursive_search(i + 1);
        subset.pop_back();
    }
}
// 2. Iterativa
void iteractive_search(){
    for(int mask = 0; mask < (1 << n); mask++){
        vector<int> subset;
        for(int j = 0; j < n; j++){
            if((mask >> j) & 1){
                subset.pb(j);
            }
        }
        get(subset);
    }
}


// Backtracking -> Depth First Search otimizado
// -> 1. Verifica se o estado é aceitável
// -> 2. Verifica se o estado não é aceitável(rejeito o ramo caso não seja aceitável)
// -> 3. Faz o que pode ser feito nele, ou seja, explora os estados adjacentes


// Meet in the middle -> Dividir um espaço de busca e fazer busca completa em cada uma das partes


// Dividir e Conquistar
