#include <bits/stdc++.h>
#define endl '\n'
 
using namespace std;
using ll = int;
#define mod 1000000007
 
class HashedString {
  private:
	// change M and B if you want
	static const long long M = 1e9+ 9;
	static const long long B = 9973;
 
	// pow[i] contains B^i % M
	static vector<long long> pow;
 
	// p_hash[i] is the hash of the first i characters of the given string
	vector<long long> p_hash;
 
  public:
	HashedString(const string &s) : p_hash(s.size() + 1) {
		while (pow.size() <= s.size()) { pow.push_back((pow.back() * B) % M); }
 
		p_hash[0] = 0;
		for (int i = 0; i < s.size(); i++) {
			p_hash[i + 1] = ((p_hash[i] * B) % M + s[i]) % M;
		}
	}
 
	long long get_hash(int start, int end) {
		long long raw_val = (p_hash[end + 1] - (p_hash[start] * pow[end - start + 1]));
		return (raw_val % M + M) % M;
	}
};
vector<long long> HashedString::pow = {1};
 
int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	string g;
	cin>>g;
	int k=1;
	int l=1;
	int m=1;
	HashedString h(g);
	reverse(g.begin(),g.end());
	HashedString h1(g);
	//cout<<h.get_hash(0,0)<<endl;
	pair<int,int>p={0,0};
	int tamanho=g.size();
	reverse(g.begin(),g.end());	
	for(int i=0;i<g.size();i++){
		//cout<<i<<endl;
		int iv=tamanho-1-i;
		if(i-k>=0 and iv-k>=0 and iv-1>=0 and i-1>=0){
			bool x=true;
			while(i-k>=0 and iv+k<tamanho and iv-1>=0 and i-1>=0 and iv-k>=0 and x){
				ll a=h.get_hash(i-k,i-1),b=h1.get_hash(iv-k,iv-1);
				
				if(a==b){
					if(2*k>p.second-p.first){
						p.first=i-k;
						p.second=i+k;
					}
					k++;
				}
				else{
					x=false;
				}
			}
		}
		if(i-l>=0 and iv-l-1>=0 and iv-1>=0 and i+l+1<tamanho){
			bool x=true;
			while(i-l>=0 and iv-l-1>=0 and iv-1>=0 and i+l+1<tamanho and x){
				ll a=h.get_hash(i-l,i),b=h1.get_hash(iv-l-1,iv-1);
				//cout<<a<<" "<<b<<endl;
				if(a==b){
					if(2*l+1>p.second-p.first){
						p.first=i-l;
						p.second=i+l+1;
					}
					l++;
				}
				else{
					x=false;
				}
			}
		}
		if(i+1<tamanho and p.second-p.first<1 and g[i]==g[i+1]){
			p.first=i;
			p.second=i+1;
		}
		if(p.second-p.first<1 and g[i-1]==g[i]){
			p.first=i-1;
			p.second=i;
		}
	}
	//cout<<p.first<<" "<<p.second<<endl;
	for(int i=p.first;i<=p.second;i++){
		cout<<g[i];
	}
	cout<<endl;
}
