	#include <bits/stdc++.h>
	#define endl '\n'
	
	using namespace std;
	using ll = int;
	#define mod 1000000007
	#define Mid (l + ((r - l) >> 1))
	struct no{
		ll inicio;
		ll fim;
		ll i;
	};
	no Seg[4*200005];
	vector<no> Vet;
	ll n;
	ll nxt[200005][20];
	
	no Modify(no a, no b){
		no res=a;
		if(b.fim<a.fim){
			return b;
		}
		if(b.fim==a.fim and b.inicio<a.inicio){
			return b;
		}
		return res;
	}
	
	no build(ll l = 0, ll r = n - 1, ll id = 1){
		if (l == r){
			return Seg[id]={Vet[l].inicio,Vet[l].fim, Vet[l].i};
		}
		return Seg[id]= Modify(build(l, Mid, 2 * id), build(Mid + 1, r, 2 * id + 1));
	}
	
	no query(ll i, ll j, ll l = 0, ll r = n - 1, ll id = 1){
		if (i > r || j < l) return {INT_MAX, INT_MAX, INT_MAX};;
		if (i <= l && j >= r) return Seg[id];
		return Modify(query(i, j, l, Mid, 2 * id),query(i, j, Mid + 1, r, 2 * id + 1));
	}

	bool so(no a,no b){
		if(a.inicio!=b.inicio){
			return a.inicio<b.inicio;
		}
		return a.fim<b.fim;
	}


	int main(){
		ios_base::sync_with_stdio(false);
		cin.tie(NULL);
		int z,w;
		cin>>z>>w;
		for(int i=0;i<z;i++){
			ll a,b;
			cin>>a>>b;
			no aba={a,b,0};
			Vet.push_back(aba);
		}
		n=z;
		sort(Vet.begin(),Vet.end(),so);
		for(int i=0;i<z;i++){
			Vet[i].i=i;
		}
		build();
		for(int i=0;i<z;i++){
			for(int j=0;j<20;j++){
				nxt[i][j]=INT_MAX;
			}
		}
		vector<pair<int,int>>p;
		int in=0;
		for(int i=0;i<z;i++){
			if(Vet[i].inicio!=Vet[in].inicio){
				p.push_back({in,i-1});
				in=i;
			}
		}
		p.push_back({in,z-1});
		for(int i=0;i<z;i++){
			auto it=lower_bound(Vet.begin(),Vet.end(),
			no{Vet[i].fim,INT_MIN,INT_MIN},
			[](const no&x,const no&y){
				return x.inicio<y.inicio;
			})-Vet.begin();
			int t=query(it,z-1).i;
			if(t!=INT_MAX and Vet[t].inicio>=Vet[i].fim){
				nxt[i][0]=t;
				//cout<<Vet[i].inicio<<" "<<Vet[i].fim<<" "<<Vet[it].inicio<<" "<<Vet[it].fim<<endl;
			}
		}
		for(int i=0;i<z;i++){
			for(int j=1;j<20;j++){
				if(nxt[i][j-1]!=INT_MAX){
					nxt[i][j]=nxt[nxt[i][j-1]][j-1];
				}
			}
		}
		for(int i=0;i<w;i++){
			int a,b;
			cin>>a>>b;
			int sum=0;
			auto it=lower_bound(Vet.begin(),Vet.end(),
			no{a,INT_MIN,INT_MIN},
			[](const no&x,const no&y){
				return x.inicio<y.inicio;
			})-Vet.begin();
			int t=query(it,z-1).i;
			if(Vet[t].inicio>=a and Vet[t].fim<=b){
				it=t;
			}
			else{
				it=z;
			}
			if(it<z and Vet[it].fim<=b){
				sum++;
			}
				for(int j=18;j>=0;j--){
					if(it!=INT_MAX and nxt[it][j]!=INT_MAX and Vet[nxt[it][j]].inicio>=a and Vet[nxt[it][j]].fim<=b){
						sum=sum+(1<<j);
						it=nxt[it][j];
						j++;
					}
				}
			
			cout<<sum<<endl;
		}
	}
