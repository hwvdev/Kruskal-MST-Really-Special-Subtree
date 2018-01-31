// red night shortest path
// and printing path

#include<bits/stdc++.h>
using namespace std;
int n;
bool visited[201][201];
int moves[201][201];
typedef pair<string, pair<int, int> > Pair;
typedef pair<int, pair<int, int> > P;
Pair parent[201][201];
stack<string> s;

bool isSafe(int x, int y){
	if(x<0 || y <0 || x>n || y>n )
	return false;
	return true;
}

void path(int x, int y, int l, int m){
	
	for(int i=0;i<n;i++){
		fill(visited[i], visited[i]+n+1, false);
		fill(moves[i], moves[i]+n+1, INT_MAX);
	}
	
	parent[x][y]= make_pair("",make_pair(-1,-1));
	
	int dx[]={-2 , -2 ,  0 , 0 ,  2 , 2};
    int dy[]={-1 ,  1 , 2 , -2 , 1 , -1};
    
    string str[]={"UL","UR","R","L","LR","LL"};
    moves[x][y]=0;
	queue<P> Q;
	Q.push(make_pair(0,make_pair(x,y)));
	stack<string > s;
	
	while(!Q.empty()){
		P p=Q.front();
		x=p.second.first;
		y=p.second.second;
		int w=p.first;
		visited[x][y]=true;
		Q.pop();
			
		for(int i=0;i<6;i++){
			int a=x+dx[i];
			int b=y+dy[i];
			if(isSafe(a,b) && !visited[a][b]){
				if(moves[a][b]> w+1 ){
					moves[a][b]=w+1;
					parent[a][b]=make_pair(str[i],make_pair(x,y));
          Q.push(make_pair(moves[a][b],make_pair(a,b)));
				}
			}
		}
	}
}

int main(){
	cin >> n;
	int x,y,l,m;
	cin >> x >> y >> l >> m;
	path(x,y,l,m);
	
	
	  if(moves[l][m]==INT_MAX)
		cout << "Impossible" << endl;
	  else{
	  cout << moves[l][m] << endl;
	  int a1=l,a2=m;
  	while(1){
		if(l==-1&&m==-1)
		break;
		s.push(parent[l][m].first);
		a1=parent[l][m].second.first;
		a2=parent[l][m].second.second;
		l=a1;
		m=a2;
		}
		s.pop();
  	while(!s.empty()){
		string Z=s.top();
		cout << Z <<" ";
		s.pop();
		}
	}
  parent[x][y]= make_pair("",make_pair(0,0));
  return 0;
}
