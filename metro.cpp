#include<bits/stdc++.h>
#include<fstream>
#define ll long long
#define pb push_back
#define fi first
#define se second
#define mp make_pair
using namespace std;

map<string,ll>M;
// city , key(weight)
char color[200][200]={'\0'};
class comparedis
{
	public:
	bool operator()(pair<ll,ll> &p,pair<ll,ll> &q)
		{
			return (p.se > q.se); // For min heap use > sign
		}
};
vector< pair<ll,ll> > v[100010];//Adjacency matrix
ll N;// N is no of vertices
string station[200];
map <string,string> tourm;
void recharge()
{
	fstream f;
	ll amt,ini,cid,fin,x;
	ll c_id,amount;
	f.open("paisa.txt",ios::in|ios::out);
	if(!f)
		cout<<"Not Found\n"<<endl;
	f.seekg(0);
	cout<<endl;
	cout<<"Enter Card Id : ";
	cin>>c_id;
	cout<<"\nEnter Amount : ";
	cin>>amount;
	f.clear();
	while(!f.eof())
	{
		ini=f.tellg();
		f.ignore();
		f>>cid;
		f>>amt;
		fin=f.tellg();
		if(cid==c_id)
		{
			x=amt+amount;
			f.seekg(ini);
			f<<endl<<cid<<endl<<x;
			cout<<"Recharge Details\n";
			cout<<"\nCard Id: "<<cid<<endl;
			cout<<"Initial Balance: "<<amt<<endl;
			cout<<"Recharge Amount: "<<amount<<endl;
			cout<<"Total Balance: "<<x<<endl;
			break;
		}
	}
	f.close();
}
void gettour()
{
	ifstream fin;
	string s1,s2;
	fin.open("tourplace.txt",ios::in);
	if(!fin)
		cout<<"Not Found\n";
	fin.seekg(0);
	fin.clear();
	while(!fin.eof())
	{
		getline(fin,s1);
		getline(fin,s2);
		tourm[s1]=s2;
		//cout<<tourm[s1]<<endl;
	}
	fin.close();
	// map<string,string>:: iterator it;
	// for(it=tourm.begin();it!=tourm.end();it++){
	// 	cout<<it->fi<<"-> "<<it->se<<endl;
	// }
}
//Given below code will print the path
void disp(ll src,ll dest,ll par[])
{
	ll i,x,y,cn=0,ci=0;
	stack<ll> st;
	st.push(dest);
	i=dest;
	while(par[i]!=-1)
	{
		i=par[i];
		st.push(i);				
	}
	char col='\0';
	while(!st.empty())
	{
		x=st.top();
		st.pop();
		if(!st.empty())
			y=st.top();
		cout<<station[x]<<"-> ";
		cn++;
		if(col=='\0')
			col=color[x][y];
		else if(col!='\0'&&col!=color[x][y])
		{
			char c=color[x][y];
			ci++;
			if(c=='b')
				cout<<"\t\tChange to blue line";
			else if(c=='y')
				cout<<"\t\tChange to yellow line";
			else if(c=='o')
				cout<<"\t\tChange to orange line";
			else if(c=='g')
				cout<<"\t\tChange to green line";
			else if(c=='r')
				cout<<"\t\tChange to red line";
			else if(c=='v')
				cout<<"\t\tChange to Violet line";
			col=c;
		}		
		cout<<endl;
	}
	// cout<<endl<<"No of stations ="<<cn<<endl;
	// cout<<"No of interchange stations ="<<ci-1<<endl;
	cout<<endl;
}
int cost(ll src,ll dest,ll par[])
{
	ll i,x,y,cn=0,ci=0;
	stack<ll> st;
	st.push(dest);
	i=dest;
	while(par[i]!=-1)
	{
		i=par[i];
		st.push(i);				
	}
	char col='\0';
	while(!st.empty())
	{
		x=st.top();
		st.pop();
		if(!st.empty())
			y=st.top();
		cn++;
		if(col=='\0')
			col=color[x][y];
		else if(col!='\0'&&col!=color[x][y])
		{
			char c=color[x][y];
			ci++;
			col=c;
		}		
		// cout<<endl;
	}
	int price;
	if(cn>0 && cn<10){
		price=10+6*(cn-1);
	}
	else if(cn>=10 && cn< 20){
		price=10+5*(cn-1);
	}
	else if(cn>=20){
		price=10+4*(cn-1);
	}
	return price;
}
//To find shotest path
void bfs(ll src,ll dest) 
{
	bool vis[100010]={false};
	ll par[100010];
	for(ll i=0;i<N;i++)
		par[i]=-1;
	queue<ll> q;
	q.push(src);
	vis[src]=true;
	while(!q.empty())
	{
		ll x=q.front();
		q.pop();
		ll vsz=v[x].size();
		for(ll i=0;i<vsz;i++)
		{
			ll y=v[x][i].fi;
			if(!vis[y])
			{
				par[y]=x;
				vis[y]=true;
				q.push(y);
			}
		}
		v[x].clear();
	}
	disp(src,dest,par);
}
//To find most economical path
int dijkstra(ll src,ll dest,int d)
{
	bool vis[100010]={false};
	ll dist[100010], par[100010];
	for(ll i=0;i<N;i++)
	{
		dist[i]=LLONG_MAX;
		par[i]=-1;
	}
	priority_queue< pair<ll,ll>,vector< pair<ll,ll> >,comparedis > pq;
	pq.push(mp(src,0));
	dist[src]=0;
	par[src]=-1;
	vis[src]=true;
	while(!pq.empty())
	{
		pair<ll,ll> k=pq.top();
		pq.pop();
		ll x=k.fi;
		//if(x==dest)
		//	break;
		ll vsz=v[x].size();
		for(ll i=0;i<vsz;i++)
		{
			ll y=v[x][i].fi;
			ll w=v[x][i].se;
			if(dist[x]+w < dist[y])
			{
				par[y]=x;
				dist[y]=dist[x]+w;
			}
			if(!vis[y])
			{
				vis[y]=true;
				pq.push(mp(y,dist[y]));
			}
		}
		v[x].clear();
	}
	disp(src,dest,par);
	if(d==0){
		return 0;
	}
	else{
		int p = cost(src,dest,par);
		return p;
	}
}
void consmap()//To assign values to metro stations
{
	ifstream fin;
	string s;
	fin.open("list.txt",ios::in);
	ll l=0;
	fin.seekg(0);
	fin.clear();
	while(!fin.eof())
	{
		getline(fin,s);
		M[s]=l;
		station[l]=s;
		l++;
	}
	N=l-1;
	fin.close();
	map<string,ll> ::iterator it;
	//for(it=M.begin();it!=M.end();it++)
	//	cout<<it->se<<" "<<it->fi<<endl;
}
void addedge(char fname[],ll w)//To add edges
{
	ifstream fin;
	string s;
	ll x,y;
	fin.open(fname,ios::in);
	fin.seekg(0);
	getline(fin,s);
	x=M[s];
	char c=fname[0];
	fin.clear();
	while(!fin.eof())
	{
		getline(fin,s);
		y=M[s];
		v[x].pb(mp(y,w));
		v[y].pb(mp(x,w));
		color[x][y]=c;
		color[y][x]=c;
		x=y;
	}
	fin.close();
}
void consgraph()//To construct edges
{
	//string s;
	addedge("blueline.txt",0);
	addedge("yellowline.txt",0);
	addedge("redline.txt",0);
	addedge("greenline.txt",0);
	addedge("violetline.txt",0);
	addedge("bluext.txt",0);
	addedge("orangeline.txt",1);
}
int main()
{
	string source,destination;
	ll i,x,y,w,src,dest,k,choice,dec;
	char ch;
	gettour();
	consmap();
	do
	{
		system("cls");
		cout<<endl;
		cout<<"#---------LIST OF ALL THE ACTIONS------------#"<<endl;
		cout<<"1. SHOW THE LIST OF METRO STATION\n";
		cout<<"2. SHOW LIST OF TOURIST PLACE\n";
		cout<<"3. GET SHORTEST PATH (ECONOMICALLY) TO REACH FROM A 'SOURCE' STATION TO 'DESTINATION' STATION\n";
		cout<<"4. GET SHORTEST PATH (DISTANCE WISE) TO REACH FROM A 'SOURCE' STATION TO 'DESTINATION' STATION\n";
		cout<<"5. TO CHECK NEAREST METRO STATION TO A TOURIST PLACE\n";
		cout<<"6. GET THE COST OF TRAVELLING\n";
		cout<<"7. To Recharge your Smart Card\n";
		cout<<"8. Exit\n";
		cout<<"\nEnter Choice : ";
		cin>>dec;
		string s;
		ifstream fl,f2,f3,f4,f5,f6,f7,f8;
		switch(dec)
		{
			case 1:
				do
					{
						cout<<"\n#----------CHOOSE COLOUR OF LINE FOR METRO STATION----------#\n";
						cout<<"1. BlueLine Metro Stations\n";
						cout<<"2. RedLine Metro Stations\n";
						cout<<"3. GreenLine Metro Stations\n";
						cout<<"4. VioletLine Metro Stations\n";
						cout<<"5. YellowLine Metro Stations\n";
						cout<<"6. BlueExt Metro Stations\n";
						cout<<"7. OrangeLine Metro Stations\n";
						cout<<"\nEnter Choice : ";
						int cl;
						cin>>cl;
						switch(cl){
							case 1:
							fl.open("blueline.txt",ios::in);
							while(true){
								getline(fl,s);
								if(fl.eof())
									break;
								else {
									cout<<s<<"\n";
								}
							}
							fl.close();
							break;
							case 2:
							f2.open("redline.txt",ios::in);
							while(true){
								getline(f2,s);
								if(f2.eof())
									break;
								else {
									cout<<s<<"\n";
								}
							}
							f2.close();
							break;
							case 3:
							f3.open("greenline.txt",ios::in);
							while(true){
								getline(f3,s);
								if(f3.eof())
									break;
								else {
									cout<<s<<"\n";
								}
							}
							f3.close();
							break;
							case 4:
							f4.open("violetline.txt",ios::in);
							while(true){
								getline(f4,s);
								if(f4.eof())
									break;
								else {
									cout<<s<<"\n";
								}
							}
							f4.close();
							break;
							case 5:
							f5.open("yellowline.txt",ios::in);
							while(true){
								getline(f5,s);
								if(f5.eof())
									break;
								else {
									cout<<s<<"\n";
								}
							}
							f5.close();
							break;
							case 6:
							f6.open("bluext.txt",ios::in);
							while(true){
								getline(f6,s);
								if(f6.eof())
									break;
								else {
									cout<<s<<"\n";
								}
							}
							f6.close();
							break;
							case 7:
							f7.open("orangeline.txt",ios::in);
							while(true){
								getline(f7,s);
								if(f7.eof())
									break;
								else {
									cout<<s<<"\n";
								}
							}
							f7.close();
							break;
						}
						cout<<"\nDo you wish to check for any other list of station(Y/N) : ";
						cin>>ch;
					}while(ch=='Y'||ch=='y');
					break;
			case 2:
					cout<<"\nList OF TOURIST PLACES\n\n";
						f8.open("tourplace.txt",ios::in);
							while(true){
								getline(f8,s);
								if(f8.eof())
									break;
								else {
									cout<<s<<"\n";
								}
							}
							f8.close();
						break;
			case 3:
					do
					{
						consgraph();//To build the adjacency matrix
						cout<<"\nEnter station 1 : ";
						//getline(cin,source);
						fflush(stdin);
						getline(cin,source);
						//cout<<source<<endl;
						cout<<"\nEnter station 2 : ";
						getline(cin,destination);
						//cout<<destination<<endl;
						src=M[source];
						dest=M[destination];
						bfs(src,dest);
						cout<<"Do you wish to check for any other station(Y/N) : ";
						cin>>ch;
					}while(ch=='Y'||ch=='y');	
					break;	
			case 4:
					do
					{
						consgraph();
						cout<<"\nEnter station 1 : ";
						fflush(stdin);
						getline(cin,source);
						cout<<"\nEnter station 2 : ";
						getline(cin,destination);
						src=M[source];
						dest=M[destination];
						dijkstra(src,dest,0);
						cout<<"Do you wish to check for any other station(Y/N) : ";
						cin>>ch;
					}while(ch=='Y'||ch=='y');	
					break;
			case 5:
					do
					{
						string place;
						cout<<"\nEnter a place : ";
						fflush(stdin);
						//getline(cin,place);
						getline(cin,place);
						string st;
						st=tourm[place];
						cout<<st<<endl;
						cout<<"\nDo you wish to check for any other place(Y/N) : ";
						cin>>ch;
					}while(ch=='Y'||ch=='y');
					break;
			case 6:
					do
					{
						consgraph();
						cout<<"\nEnter station 1 : ";
						fflush(stdin);
						getline(cin,source);
						cout<<"\nEnter station 2 : ";
						getline(cin,destination);
						src=M[source];
						dest=M[destination];
						int ans=dijkstra(src,dest,1);
						cout<<"Total price: "<<ans<<endl;
						cout<<"\nDo you wish to check for another path(Y/N) : ";
						cin>>ch;
					}while(ch=='Y'||ch=='y');
					break;
			case 7:
					do
					{
						recharge();
						cout<<"\nDo you wish to recharge some other smart card(Y/N) : ";
						cin>>ch;
					}while(ch=='Y'||ch=='y');
					break;
			case 8:
					exit(0);
		}
		cout<<"\nDo you wish to go back to main menu(Y/N) : ";
		cin>>ch;
	}while(ch=='Y'||ch=='y');
	return 0;
}