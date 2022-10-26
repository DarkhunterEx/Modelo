#include <bits/stdc++.h>

using namespace std;

int kmp(string a,string b,vector<int>&match){
    int ss=0,s=0;
    int r=0;
    while(s<(int)a.size()){
        if(b[ss]==a[s]){
            s++;
            ss++;
        }
        if(ss==(int)b.size()){
            r++;
            s=s-(int)b.size()+1;
            ss=0;
        }
        else if(s<(int)a.size() and b[ss]!=a[s]){
            if(ss!=0)
                ss=match[ss-1];
            else{
                s++;
            }
        }
    }
    return r;
}

void prefix(string padrao, vector<int> & aux)
{
	aux[0] = 0;
	int j = 0, i = 1;

	while((unsigned)i < padrao.size())
	{
		if(padrao[i] == padrao[j])
		{
			j++;
			aux[i] = j;
			i++;
		}
		else
		{
			if(j)
				j = aux[j - 1];
			else
			{
				aux[i] = 0;
				i++;
			}
		}
	}
}

int main(){
    int z;
    cin>>z;
    while(z){
        vector<pair<int,string>>a;
        for(int i=0;i<z;i++){
            string k;
            cin>>k;
            a.push_back(make_pair(0,k));
        }
        string b;
        cin>>b;
        pair<int,int>ma;
        ma=make_pair(0,0);
        for(int i=0;i<z;i++){
            vector<int>r((int)(a[i].second).size());
            prefix(a[i].second,r);
            a[i].first=kmp(b,a[i].second,r);
            //cout<<a[i].first<<" "<<a[i].second<<endl;
            if(ma.first<a[i].first){
                ma.first=a[i].first;
                ma.second=1;
            }
            else if(ma.first==a[i].first){
                ma.second++;
            }
        }
        cout<<ma.first<<endl;
        for(int i=0;i<(int)a.size();i++){
            if(a[i].first==ma.first)
            cout<<a[i].second<<endl;
        }
        cin>>z;
    }
}
