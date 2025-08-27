#include <bits/stdc++.h>
#define endl '\n'

using namespace std;
using ll = long long;
#define mod 1000000007
#define Mid (l + ((r - l) >> 1))
static const long long M = 1e9 + 9;

static const long long B = 9973;
#include <bits/stdc++.h>
using namespace std;
struct no{
    ll valor=0;
    ll tamanho=0;
    ll pos=0;
};
no Seg[8*200005];
ll Vet[8*200005];
ll n;
vector<unsigned ll>ppow={1};
no Modify(no a, no b){
    no h;
    h.valor=((a.valor*ppow[b.tamanho])%M+b.valor)%M;
    h.tamanho=a.tamanho+b.tamanho;
    h.pos=a.pos;
    return h;
}
 
no build(ll l = 0, ll r = n - 1, ll id = 1){
    if (l == r){
        return Seg[id]={Vet[l],1,l};
    }
    return Seg[id]= Modify(build(l, Mid, 2 * id), build(Mid + 1, r, 2 * id + 1));
}
 
no query(ll i, ll j, ll l = 0, ll r = n - 1, ll id = 1){
    if (i > r || j < l) return {0,0,0};
    if (i <= l && j >= r) return Seg[id];
    return Modify(query(i, j, l, Mid, 2 * id),query(i, j, Mid + 1, r, 2 * id + 1));
}
 
void upd(ll i, ll x, ll l = 0, ll r = n - 1, ll id = 1){
    if (l > r) return;
    if (l == r){ Seg[id].valor = {x}; return; }
    if (i <= Mid) upd(i, x, l, Mid, 2 * id);
    else upd(i, x, Mid + 1, r, 2 * id + 1);
    Seg[id] = Modify(Seg[2 * id], Seg[2 * id + 1]);
}

int main(){
	//freopen("1.txt","r",stdin);
	//freopen("12.txt","w",stdout);
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
    int z,w;
    cin>>z>>w;
    string a;
    cin>>a;
    n=2*a.size();
    for (int i = 0; i < a.size()*2; i++) {
        ppow.push_back((ppow.back() * B) % M);
    }
    for(int i=0;i<a.size();i++){
        Vet[i]=(ll)a[i];
    }
    reverse(a.begin(),a.end());
    for(int i=0;i<a.size();i++){
        Vet[i+a.size()]=(ll)a[i];
    }
    build();
    for(int i=0;i<w;i++){
        int d;
        cin>>d;
        if(d==1){
            int b;
            char c;
            cin>>b>>c;
            b--;//cout<<b<<"!";
            upd(b,(ll)c);
            b=a.size()-1-b+a.size();
            //cout<<b<<endl;
            upd(b,(ll)c);
        }
        else{
            int b,c;
            cin>>b>>c;
            b--;
            c--;
            //cout<<b<<" "<<c<<endl;
            ll v1=query(b,c).valor;
            b=a.size()-1-b+a.size();
            c=a.size()-1-c+a.size();
            if(b>c){
                swap(b,c);
            }
            ll v2=query(b,c).valor;
            //cout<<b<<" "<<c<<endl;
            //cout<<v1<<" "<<v2<<endl;
            if(v1==v2){
                cout<<"YES"<<endl;
            }
            else{
                cout<<"NO"<<endl;
            }
        }
    }
}
