
#include "dataStructure.h"


Graph::Graph(int numOfVer)
{
	numOfEdges=0;
	for(int i=0;i<numOfVer;i++)
	{
		vertices.push_back(Vertex(i));
	}
}

void Graph::print()
{
	cout<<vertices.size()<<" vertices and "<<numOfEdges<<" edges."<<endl;
	for(int i=0;i<vertices.size();i++)
	{
		cout<<i<<" : ";
		for(int j=0;j<vertices[i].edges.size();j++)
		{
			if((vertices[i].edges)[j].begin!=i) return;
			cout<<(vertices[i].edges)[j].end<<"  ";
		}
		cout<<endl;
	}


}
void Graph::addPath(int s,int t,int max)
{
	int w;
	int v;
	int value;
	int Vers=vertices.size();
	for(int i =0;i<Vers-1;i++)
	{
		w=(s+i)%Vers;
		v=(s+i+1)%Vers;
		if(v==t) {i++;continue;}
		value=rand()%max+1;
		if(!exist(w,v)){insert(w,v,value);
		//cout<<"Add edge "<<w<<"--"<<v<<" with weight "<<value<<endl;
		}
		//else cout<< "Existed!"<<endl;
	}
	if(!exist(w,v)){insert(v,t,rand()%max+1);
	//cout<<"Add edge "<<v<<"--"<<t<<" with weight "<<value<<endl;
	}



}

void Graph::empty(){
	int numOfVer=vertices.size();

	numOfEdges=0;
	vertices.clear();
	for(int i=0;i<numOfVer;i++)
	{
		vertices.push_back(Vertex(i));
	}

}

bool Graph::insert(int u,int v,int w)
{
    if(u>=vertices.size()||v>=vertices.size())return false;
	if(exist(u,v)) return false;
	vertices[u].addEdge(u,v,w);
	vertices[v].addEdge(v,u,w);
	numOfEdges++;

    return true;
}

int Graph::exist(int u,int v)const
{
	if(u>=vertices.size()||v>=vertices.size())return 0;
	for(int i=0;i<vertices[u].edges.size();i++)
	{
		if (vertices[u].edges[i].end==v) return vertices[u].edges[i].weight;  //exist
	}
	return 0;


	//if(find(v.begin(), v.end(), val) != v.end())
}