#include <ctime>
#include <cstdlib>
#include <iostream>
#include <cmath>

#include "dataStructure.h"



using namespace std;

Paths findPaths(Paths Pl,vector<int> V1,Graph* g,int h,bool first=false);

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


int main(){

	cout<<"hello"<<endl;
	double dur;
    clock_t start,end;

    start = clock();
    Graph *g1=new Graph(VER);   //
	create(g1);
	end = clock();
    dur = (double)(end - start);
	cout<<"G2 has been created: "<<dur*1000/CLOCKS_PER_SEC<<" ms"<<endl;
	//g1->print();
	g1->addPath(0,VER);

	Paths Pl(0);
	//Pl.ps.push_back(Path(0));
	vector<int> V1;
	for(int i=0;i<g1->vertices.size();i++)
	{
		V1.push_back(i);
	}
	start = clock();
	Paths res = findPaths(Pl,V1,g1,5,true);
	cout<<res.ps.size()<<endl;

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
	cout<<res.ps.size()<<endl;
	res.ps[maxIn].print();
	

	
	end = clock();
	dur = (double)(end - start);
	cout<<"G2 has been created: "<<dur*1000/CLOCKS_PER_SEC<<" ms"<<endl;

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
					assert(p.l=p.vers.size());
					//Plh.containVer[u]=true;
					Plh.ps.push_back(p);
				}
			}
			
		}
		return Plh;
	}
	//cout<<"mid"<<endl;
	for(int i=0;i<3*pow(2,h);i++)
	{
		//cout<<i<<endl;
		if(first) cout<<i<<endl;
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
				assert(PR.ps[j].l==Pl.l+h);
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
							//Plh.ps.erase(Plh.ps.begin()+k);
							//Plh.ps.push_back(PR.ps[j]);        //replace
							Plh.ps[k]=PR.ps[j];
							
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
