#ifndef _DATA_STRUCTURE_H_                   // include file only once
#define _DATA_STRUCTURE_H_

#include <iostream>
#include <ctime>
#include <cstdlib>
#include <vector>
#include <assert.h>

#define VER 100
#define MAX 500

using namespace std;

struct  Edge{
	int begin;
	int end;
	int weight;
	Edge(int b=0,int e=0,int w=0){
		begin=b;end=e;weight=w;
		
	}

};

struct Vertex{
	int ver;
	int degree;
	vector<Edge> edges;
	Vertex(int _ver){
		ver=_ver; degree=0;
	}

	void addEdge(int u,int v,int w){
		if(u==v) return;
		if(u==ver) edges.push_back(Edge(ver,v,w));
		else if(v==ver) edges.push_back(Edge(ver,u,w));
		else return;
		degree++;
	}

};

class Graph{
public:
	vector<Vertex> vertices;
	int numOfEdges;
	int exist (int u,int v) const;       //return if edge(u-v) is exist
	Graph(int numOfVer=0);
	void empty();              //empty this graph
	bool insert(int u,int v,int w);  
	void print();
	void addPath(int s,int t,int max=MAX);   //add a path from s to t goes through all vertices in the G

};


class Path{
public:
	int l;
	vector<int> vers;
	int weight;
	//vector<vector<int>> Paths; 
	Path(int _l){l=_l;weight=0;}
	Path(Path p,int u,int _weight)
	{
		l=p.l+1;
		for(int i=0;i<p.vers.size();i++)
		{
			vers.push_back(p.vers[i]);
		}
		vers.push_back(u);
		//assert(vers.size()==l);
		weight=_weight;
	}
	void print(){
		if(l==0) return;
		//cout<<"vertex nums:"<< vers.size()<<"   l= "<<l<<endl;
		
		cout<<"Path: "<<vers[0];
		for(int i=1;i<vers.size();i++)
		{
			cout<<" -- "<<vers[i];
		}
		cout<<"     Weight = "<<weight<<endl;
	}
};

class Paths{
public:
	int l;
	//bool* containVer;

	Paths(int _l,int ver=VER){
		l=_l;
		//containVer=new bool[ver];
		//for(int i=0;i<ver;i++) containVer[i]=false;
	}
	vector<Path> ps;

};

#endif