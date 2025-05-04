#include <bits/stdc++.h>

using namespace std;

#include <bits/stdc++.h>
using namespace std;

const int WMAX = 1e6;

int trie[WMAX][26];
int node_count=0;
vector<int>stop(WMAX,0);
int sum=0;

/** Adds a new word into the trie. */
void insert(string word) {
	// Node 0 has 26 children - a through z.
	int node = 0;
	for (char c : word) {
		// If a node with the current char doesn't exist create one.
		if (trie[node][c - 'a'] == 0) { trie[node][c - 'a'] = ++node_count; }
        //cout<<node<<endl;
		// Move down the path in the trie.
        if(trie[node][c - 'a'] ==-1){
            return;
        }
		node = trie[node][c - 'a'];
	}
	// Mark the ending node so we know it's a dictionary word
    //cout<<node<<"**";
    if(trie[node][0]==-1)
    return;
	stop[node]++;
    sum++;
    //cout<<node<<" "<<word.back()-'a'<<"&&&"<<endl;
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    for(int i=0;i<WMAX;i++){
        for(int j=0;j<26;j++){
            trie[i][j]=0;
        }
    }
    //freopen("12.txt","w",stdout);
    int z;
    cin>>z;
    for(int i=0;i<z;i++){
        int k;
        string a;
        cin>>k>>a;
        if(k==1){
            int node=0;
            for(char c:a){
                if (trie[node][c - 'a'] == 0) { trie[node][c - 'a'] = ++node_count; }
                if(trie[node][c - 'a'] !=-1)
                node = trie[node][c - 'a'];
                else{
                    break;
                }
            }
            queue<int>q;
            if(node>-1)
            q.push(node);
            while(!q.empty()){
                node=q.front();
                q.pop();
                //cout<<node<<"***"<<stop[node]<<"***";
                for(int i=0;i<26;i++){
                    if(trie[node][i]>0){
                        q.push(trie[node][i]);
                    }
                    trie[node][i]=-1;
                    if(stop[node]>0){
                        sum=sum-stop[node];
                    }
                    stop[node]=0;
                }
            }
        }
        if(k==2){
            insert(a);
        }
        cout<<sum<<endl;
    }
    //cout<<node_count<<"*"<<endl;
}
