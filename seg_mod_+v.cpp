#include <bits/stdc++.h>
#define endl '\n'
using namespace std;
using ll = long long;
#define mod 1000000007
#define Mid (l + ((r - l) >> 1))
struct no{
    ll sum;
    ll prefixo;
    ll sufixo;
    ll melhor;
};
no Seg[4*200005];
ll Vet[4*200005];
ll n;
 
no Modify(no a, no b){
    no res;
    res.sum=a.sum+b.sum;
    res.prefixo=max(a.prefixo,a.sum+b.prefixo);
    res.sufixo=max(b.sufixo,a.sufixo+b.sum);
    res.melhor=max({a.melhor,b.melhor,a.sufixo+b.prefixo});
    return res;
}
 
no build(ll l = 0, ll r = n - 1, ll id = 1){
    if (l == r){
        return Seg[id]={Vet[l],max(0LL, Vet[l]), max(0LL, Vet[l]), max(0LL, Vet[l])};
    }
    return Seg[id]= Modify(build(l, Mid, 2 * id), build(Mid + 1, r, 2 * id + 1));
}
 
no query(ll i, ll j, ll l = 0, ll r = n - 1, ll id = 1){
    if (i > r || j < l) return {0, 0, 0, 0};;
    if (i <= l && j >= r) return Seg[id];
    return Modify(query(i, j, l, Mid, 2 * id),query(i, j, Mid + 1, r, 2 * id + 1));
}
 
void upd(ll i, ll x, ll l = 0, ll r = n - 1, ll id = 1){
    if (l > r) return;
    if (l == r){ Seg[id] = {x, max(0LL, x), max(0LL, x), max(0LL, x)};; return; }
    if (i <= Mid) upd(i, x, l, Mid, 2 * id);
    else upd(i, x, Mid + 1, r, 2 * id + 1);
    Seg[id] = Modify(Seg[2 * id], Seg[2 * id + 1]);
}
 
int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    ll z,w;
    cin>>z>>w;
    n=z;
    for(int i=0;i<z;i++){
        cin>>Vet[i];
    }
    build();
    for(int i=0;i<w;i++){
        ll a,b;
        cin>>a>>b;
        Vet[a-1]=b;
        upd(a-1,b);
        cout<<query(0,z-1).melhor<<endl;
    }
}
