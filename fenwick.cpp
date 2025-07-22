#include <bits/stdc++.h>
#define endl '\n'
using namespace std;
using ll = long long;
#define mod 1000000007

struct FenwickTree {
    vector<ll> bit;  // binary indexed tree
    int n;

    FenwickTree(ll n) {
        this->n = n;
        bit.assign(n, 0);
    }

    FenwickTree(vector<ll> const &a) : FenwickTree(a.size()) {
        for (size_t i = 0; i < a.size(); i++)
            add(i, a[i]);
    }

    ll sum(ll r) {
        ll ret = 0;
        for (; r >= 0; r = (r & (r + 1)) - 1)
            ret += bit[r];
        return ret;
    }

    ll sum(ll l, ll r) {
        return sum(r) - sum(l - 1);
    }

    void add(ll idx, ll delta) {
        for (; idx < n; idx = idx | (idx + 1))
            bit[idx] += delta;
    }
};
 
int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    //freopen("1.txt","r",stdin);
    //freopen("13.txt","w",stdout);
    long long z,x;
    cin>>z>>x;
    //cout<<z<<" "<<x<<endl;
    vector<long long>v;
    vector<pair<ll,pair<ll,pair<ll,ll>>>>p;
    vector<pair<ll,ll>>mudar;
    for(long long i=0;i<z;i++){
        long long t;
        cin>>t;
        v.push_back(t);
    }
    FenwickTree t(v);
    unsigned long long resposta[200005];
    for(long long i=0;i<x;i++){
        long long a,b,c;
        cin>>c>>a>>b;
        if(c==2){
            cout<<t.sum(a-1,b-1)<<endl;
        }
        else{
            t.add(a-1,b-v[a-1]);
            //na posição a-1 vc adiciona b-v[a-1] ja que na fenwick nao tem como trocar e sim adicionar
            v[a-1]=b;
            //modifica o elemento atual para obtermos o valor atualizado anterior
        }
    }
}
