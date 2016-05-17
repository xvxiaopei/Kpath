#include <ctime>
#include <cstdlib>
#include <iostream>
#include <cmath>
#include <algorithm>
#include "dataStructure.h"



using namespace std;

Paths findPaths(Paths Pl,vector<int> V1,Graph* g,int h,bool first=false);
void testDag();
void create(Graph * graph)
{
	srand((unsigned)time(0));
	int random;
	int count;
	int randomValue;
	for (int i = 0 ; i < VER ; i++)
	{
		count=0;
		while (graph->vertices[i].degree < 6) 
		{
				//cout<<"??"<<endl;
				random = ((rand() % (VER-i))+ i)%graph->vertices.size();    //randomly choose an end
				while(graph->vertices[random].degree>=6 || i==random)
				{
					random++;
					random=random%VER;
					count++;
					if(count>VER*3) 
					{
						//for(;;);
						break;
					}
				}
				if(count>VER*3) break;
				randomValue = rand()%MAX+1;
				graph->insert(i,random,randomValue);
				//cout<<"select "<<random<<endl;
		}
		if(count>VER*3) break;
		//graph->printVertex(i);
	}
	if(count>VER*3){
		cout<<"reshuffle!!"<<endl;
		graph->empty();
		create(graph);
	}

}


Path DAG(Graph * g,int k,int* vertices=NULL);

Path rDAG(Graph * g,int k);

int main(){
	
	cout<<"hello"<<endl;
	double dur;
    clock_t start,end;

	//testDag();

	
    start = clock();
    Graph *g1=new Graph(VER);   //
	create(g1);
	end = clock();
    dur = (double)(end - start);
	cout<<"Graph has been created: "<<dur*1000/CLOCKS_PER_SEC<<" ms"<<endl;
	//g1->print();
	g1->addPath(0,VER);


	for(int k=3;k<9;k++){

	cout<<"K = "<<k<<endl;

	start = clock();
	rDAG(g1,k).print();
	end = clock();
	dur = (double)(end - start);
	cout<<"DAG: "<<dur/CLOCKS_PER_SEC<<" s"<<endl;





	Paths Pl(0);
	//Pl.ps.push_back(Path(0));
	vector<int> V1;
	for(int i=0;i<g1->vertices.size();i++)V1.push_back(i);

	start = clock();
	Paths res = findPaths(Pl,V1,g1,k,true);
	//cout<<res.ps.size()<<endl;
	end = clock();


	int maxWeight=0;
	int maxIn=-1;
	for(int i=0;i<res.ps.size();i++){
		//res.ps[i].print();
		if(res.ps[i].weight>maxWeight)
		{
			maxWeight=res.ps[i].weight;
			maxIn=i;
		}
	}
	//cout<<res.ps.size()<<endl;
	res.ps[maxIn].print();
	
	
	
	//end = clock();
	dur = (double)(end - start);
	cout<<"Divide and conquer: "<<dur/CLOCKS_PER_SEC<<" s"<<endl;
	}

	cout<<"Hello";
}

Paths findPaths(Paths Pl,vector<int> V1,Graph* g,int h,bool first)
{
	//cout<<"begin  h = "<<h<<endl;
	Paths Plh(Pl.l+h);    //P l+h
	if(h==1){
		
		//if(Pl.ps.size()==1 && Pl.ps[0].vers.empty())   //Pl={p0}    //O(n)
		if(Pl.l==0)
		{
			//cout<<"Pl.l==0"<<endl;

			for(int i=0;i<V1.size();i++)
			{
				int u=V1[i];
				Path p(1);
				p.vers.push_back(u);          //(u,1)-path
				Plh.ps.push_back(p);
				//Plh.containVer[u]=true;
			}
		}
		else{
			//cout<<"Pl.l!=0"<<endl;
			for(int j=0;j<V1.size();j++)
			{
				int u=V1[j];
				int maxWeight=0;
				int maxPath=-1;
				//cout<<"u = "<<u<<endl;
				for(int i=0;i<Pl.ps.size();i++)
				{
					if(Pl.ps[i].vers.empty()) continue;
					int w=Pl.ps[i].vers.back();
					int weight=g->exist(u,w);
					if(weight==0)continue;           //not exist such an edge
					
					if(maxWeight<Pl.ps[i].weight+weight){
						maxWeight=Pl.ps[i].weight+weight;
						maxPath=i;
					}
				}
				//cout<<"path = "<<maxPath<<" while index < "<< Pl.ps.size()<<endl;
				if(maxPath!=-1)                    //exist
				{
					
					Path p(Pl.ps[maxPath],u,maxWeight);
					//assert(p.l=p.vers.size());
					//Plh.containVer[u]=true;
					Plh.ps.push_back(p);
				}
			}
			
		}
		return Plh;
	}
	//cout<<"mid"<<endl;
	int time =(1<<h)*3;
	for(int i=0;i<time;i++)
	{
		//cout<<i<<endl;
		//if(first) cout<<i<<endl;
		vector<int> VR,VL;
		for(int j=0;j<V1.size();j++)
		{
			if(rand()%2) VR.push_back(V1[j]);
			else VL.push_back(V1[j]);
		}
		//cout<<Pl.l<<"  ,h = "<<h<<endl;
		Paths PL=findPaths(Pl,VL,g,(h+1)/2);
		//cout<<"l = "<<PL.l<<endl;
		if(!PL.ps.empty()){
			//cout<<"Not empty! h ="<<h<<endl;
			//PL.ps[0].print();
			Paths PR=findPaths(PL,VR,g,h/2);
			//cout<<"PR Found!"<<endl;
			/*if(PR.ps.empty()) cout<<"Not found!"<<endl;
			else {
				cout<<PR.ps[0].l<<"  found!"<<endl;
				PR.ps[0].print();
			
			}*/


			for(int j=0;j<PR.ps.size();j++ )         
			{
				int u=PR.ps[j].vers.back();
				//assert(PR.ps[j].l==Pl.l+h);
				bool find = false;
				//cout<<"u found!"<<endl;
				for(int k=0;k<Plh.ps.size();k++)     //   size<= VER
				{
					if (Plh.ps[k].vers.empty()) continue;
					if(Plh.ps[k].vers.back()!=u )continue;
					else
					{
						find=true;
						if(Plh.ps[k].weight<PR.ps[j].weight)
						{
							Plh.ps.erase(Plh.ps.begin()+k);
							Plh.ps.push_back(PR.ps[j]);        //replace
							//Plh.ps[k]=PR.ps[j];
							
						}
						break;
					}
				}
				//cout<<"u out!"<<endl;
				if(!find) Plh.ps.push_back(PR.ps[j]);
			}
			//cout<<"Plh found"<<endl;
		}
		

	}
	return Plh;

}

int color[VER];
int topoi;

void DFS(int v,Graph *g,int *A)
{
	//cout<<v<<endl;
	color[v]=0;  //gray
	for(int i=0;i<g->vertices[v].edges.size();i++ ){
		if(color[g->vertices[v].edges[i].end]==1) DFS(g->vertices[v].edges[i].end,g,A);
		assert(color[g->vertices[v].edges[i].end]!=0);
	}
	color[v]=2; //black
	A[topoi--]=v;
}

int * topoSort(Graph * g)
{
	int *A=new int[g->vertices.size()];
	topoi=g->vertices.size()-1;
	for(int v=0;v<g->vertices.size();v++) color[v]=1; //white


	for(int v=0;v<g->vertices.size();v++) if(color[v]==1) DFS(v,g,A);
	return A;
}

Path rDAG(Graph * g,int k)
{
	int len=g->vertices.size();
	int *topo=new int[len];
	Path res(0);

	for(int i=0;i<len;i++)topo[i]=i;
    int fac=1;
	for(int i=1;i<=k;i++) fac*=i;
	fac*=10;
	for(int i=0;i<fac;i++)
	{
		random_shuffle(&topo[0],&topo[len]);  //permutation
		Graph * newg=g->toTopo(topo);                       //construct DAG
		Path p=DAG(newg,k,topo);
		if(p.l==0)continue;
		if(res.l==0L) res=p;
		else{
			if(res.weight<p.weight)res=p;
		}
		delete newg;
	}
	return res;

}


int findMax(int ** mat,int h,int length)
{
	int max=-1;
	int maxInt=-1;
	for(int i=0;i<length;i++)
	{
		if(max<mat[i][h]){
			max=mat[i][h];
			maxInt=i;
		}
	}
	return maxInt;
}

Path DAG(Graph * g,int k,int * vertices)
{
	if(vertices==NULL)vertices=topoSort(g);   //1
	int * toNewVer = new int[g->vertices.size()];
	Path res(k);
	//vector<Vertex> new_ver;
	for(int i=0;i<g->vertices.size();i++) toNewVer[vertices[i]]=i;




	int **w=new int *[g->vertices.size()];
	int **x=new int *[g->vertices.size()];
	for(int i = 0; i < g->vertices.size(); i++) {   //2
		w[i]=new int[k+1];
		x[i]=new int[k+1];
	}

	for(int i=0;i<g->vertices.size();i++)
	{
		for(int h=1;h<=k;h++)
		{
			w[i][h]=-1;x[i][h]=0;
		}
	}
	 
	for(int i=0;i<g->vertices.size();i++) w[i][1]=0;   //3


	for(int i=0;i<g->vertices.size()-1;i++)
	{
		int vi=vertices[i];
		for(int j=0;j<g->vertices[vi].edges.size();j++)
		{
			int vj=g->vertices[vi].edges[j].end;
			int nj=toNewVer[vj];   
			int weight=g->vertices[vi].edges[j].weight;
			for(int h=1;h<k;h++)
			{
				if(w[i][h]!=-1 && w[nj][h+1]<w[i][h]+weight)
				{
					w[nj][h+1]=w[i][h]+weight;
					x[nj][h+1]=i;
				}
			}
		}
	}

	int end=findMax(w,k,g->vertices.size());
	if(end==-1 || w[end][k]<0) return Path(0);   //no k path

	res.vers.insert(res.vers.begin(),vertices[end]);
	res.weight=w[end][k];

	for(int h=k;h>1;h--)
	{
		end=x[end][h];
		res.vers.insert(res.vers.begin(),vertices[end]);

	}

	for(int i = 0; i < g->vertices.size(); i++) {   //2
		delete [] w[i];
		delete [] x[i];
	}
	delete []w; 
    delete []x; 
	

	return res;


}

void testDag()
{
	Graph *g = new Graph(8);
	



	g->insert(0,7,3,false);
	g->insert(1,5,1,false);
	g->insert(4,5,2,false);
	g->insert(6,2,1,false);
	g->insert(6,1,2,false);
	g->insert(1,3,1,false);
	g->insert(1,4,2,false);
	g->insert(3,5,1,false);
	g->insert(7,6,1,false);
	g->insert(7,2,4,false);
	cout<<"Construct!"<<endl;

	int *tp=topoSort(g);

	g->insert(2,6,5);
	cout<<"Construct!"<<endl;

	Graph * newg=g->toTopo(tp);
	cout<<"Construct!"<<endl;
	for(int i=0;i<8;i++)
	{
		cout<<tp[i]<<"  ";
	}
	cout<<endl;

	DAG(newg,5,tp).print();



}
