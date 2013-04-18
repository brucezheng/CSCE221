#ifndef GRAPH_H
#define GRAPH_H

#include <list>
#include <vector>
#include <limits.h>
#include <algorithm>
#include <cmath>
#include <string>
#include <map>
#include <fstream>

using namespace std;

template<typename Object,typename Weight>
class Graph{
   public:

      class Vertex;

      class Edge{
	 public:
	    Edge(Vertex* v,Vertex* w,Weight setweight){
	       start = v;
	       end = w;
	       v->edge.push_back(this);
	       w->inedge.push_back(this);
	       weight = setweight;
	       explored = false;
	    }
	    Edge(){
	       explored = false;
	    }
	    Weight weight;
	    Vertex* start;
	    Vertex* end;
	    bool explored;
      };

      class Vertex{
	 public:
	    Vertex(Object setelement){
	       level = 0;
	       connectedcomponent = 0;
	       element = setelement;
	       back = NULL;
	       explored = false;
	    }
	    Vertex(){
	       level = 0;
	       connectedcomponent = 0;
	       back = NULL;
	       explored = false;
	    }
	    Object element;
	    vector<Edge*> edge;
	    vector<Edge*> inedge;
	    double value;
	    unsigned int starttime, finishtime;
	    unsigned int level;
	    unsigned int connectedcomponent;
	    float rank;
	    Vertex* back;
      int color;
	    bool explored;
      };	

      /////////////////////////////////////////////////////////////////////////
   private:

      vector<Edge*> edge;

      vector<Vertex*> vertex;

      unsigned int counter;

   public:
      /////////////////////////////////////////////////////////////////////////
      Graph();

      Graph(Graph& G);

      ~Graph();

      void reset();
      void resetBack();
      void resetValues();
      void resetLevels();
      void resetExplored();
      void resetConnectedComponents();

      vector<Vertex*> incidentVertices(Vertex* v);
      vector<Edge*> incidentEdges(Vertex* v);
      vector<Edge*> outgoingEdges(Vertex* v);
      vector<Vertex*> adjacentVertices(Vertex* v);
      unsigned int indegree(Vertex* v);
      unsigned int outdegree(Vertex* v);
      unsigned int degree(Vertex* v);
      Vertex* startVertex(Edge* e);
      Vertex* endVertex(Edge* e);
      // is there an edge from v to w ?
      bool isAdjacent(Vertex* v,Vertex* w);

      Vertex* insertVertex(Object o);
      void insertEdge(Vertex* v,Vertex* w,Weight t);
      void insertUndirectedEdge(Vertex* v,Vertex* w,Weight t);
      void removeVertex(Vertex* v);
      void removeEdge(Edge* e);

      unsigned int numVertices();
      unsigned int numEdges();
      vector<Vertex*> vertices();
      vector<Edge*> edges();

      void print();
      void read_file(std::string filename);
      /////////////////////////////////////////////////////////////////////////

};



template<typename Object,typename Weight>
Graph<Object,Weight>::Graph(){
	reset();
}

template<typename Object,typename Weight>
Graph<Object,Weight>::Graph(Graph<Object,Weight>& G){
	std::map<Vertex*,Vertex*> v_map;
	for (int i = 0; i < G.vertex.size(); ++i) {
		Vertex* v = new Vertex(*G.vertex[i]);
		v_map[G.vertex[i]] = v;
		vertex.push_back(v);
	}
	for (int i = 0; i < G.edge.size(); ++i) {
		insertEdge(G.edge[i]->start,G.edge[i]->end,G.edge[i]->weight);
	}
}

template<typename Object,typename Weight>
Graph<Object,Weight>::~Graph(){
	for (int i = 0; i < vertex.size(); ++i)
		delete vertex[i];
	for (int i = 0; i < edge.size(); ++i)
		delete edge[i];
}

template<typename Object,typename Weight> 
void Graph<Object,Weight>::reset(){
   counter = 0;
   resetBack();
   resetValues();
   resetLevels();
   resetExplored();
   resetConnectedComponents();
}
template<typename Object,typename Weight>
void Graph<Object,Weight>::resetBack(){
   for(unsigned int i=0;i<vertex.size();i++)
      vertex[i]->back = NULL;
}
template<typename Object,typename Weight>
void Graph<Object,Weight>::resetValues(){
   for(unsigned int i=0;i<vertex.size();i++)
      vertex[i]->value = INT_MAX;
}
template<typename Object,typename Weight>
void Graph<Object,Weight>::resetLevels(){
   for(unsigned int i=0;i<vertex.size();i++)
      vertex[i]->level = 0;
}
template<typename Object,typename Weight>
void Graph<Object,Weight>::resetExplored(){
   for(unsigned int i=0;i<vertex.size();i++)
      vertex[i]->explored = false;
}
template<typename Object,typename Weight>
void Graph<Object,Weight>::resetConnectedComponents(){
   for(unsigned int i=0;i<vertex.size();i++)
      vertex[i]->connectedcomponent = 0;
}

template<typename Object,typename Weight>
vector<typename Graph<Object,Weight>::Edge*> Graph<Object,Weight>::incidentEdges(Vertex* v){
	return v->inedge;
}

template<typename Object,typename Weight>
vector<typename Graph<Object,Weight>::Edge*> Graph<Object,Weight>::outgoingEdges(Vertex* v){
	return v->edge;
}

template<typename Object,typename Weight>
vector<typename Graph<Object,Weight>::Vertex*> Graph<Object,Weight>::incidentVertices(Vertex* v){
   vector<Vertex*> result;
   //fill result
   for (int i = 0; i < v->inedge.size(); ++i) {
		result.push_back(v->inedge[i]->start);
   }
   return result;
}

template<typename Object,typename Weight>
vector<typename Graph<Object,Weight>::Vertex*> Graph<Object,Weight>::adjacentVertices(Vertex* v){
   vector<Vertex*> result;
   //fill result
   for (int i = 0; i < v->edge.size(); ++i) {
		result.push_back(v->edge[i]->end);
   }
   return result;
}

template<typename Object,typename Weight>
unsigned int Graph<Object,Weight>::outdegree(Vertex* v){
   return v->edge.size();
}

template<typename Object,typename Weight>
unsigned int Graph<Object,Weight>::indegree(Vertex* v){
   return v->inedge.size();
}

template<typename Object,typename Weight>
unsigned int Graph<Object,Weight>::degree(Vertex* v){
   return v->inedge.size() + v->edge.size();
}

template<typename Object,typename Weight>
typename Graph<Object,Weight>::Vertex* Graph<Object,Weight>::startVertex(Edge* e){
   return e->start;
}

template<typename Object,typename Weight>
typename Graph<Object,Weight>::Vertex* Graph<Object,Weight>::endVertex(Edge* e){
   return e->end;
}

// is there an edge from v to w ?
template<typename Object,typename Weight>
bool Graph<Object,Weight>::isAdjacent(Vertex* v,Vertex* w){
	for (int i = 0; i < v->edge.size(); ++i) {
		if (v->edge[i]->end == w) return true;
	}
	for (int i = 0; i < v->inedge.size(); ++i) {
		if (v->inedge[i]->start == w) return true;
	}
	return false;
}

template<typename Object,typename Weight>
typename Graph<Object,Weight>::Vertex* Graph<Object,Weight>::insertVertex(Object o){
	Vertex* v = new Vertex(o);
	vertex.push_back(v);
}

template<typename Object,typename Weight>
void Graph<Object,Weight>::insertEdge(Vertex* v,Vertex* w,Weight t){
	Edge* e = new Edge(v,w,t);
	edge.push_back(e);
}

template<typename Object,typename Weight>
void Graph<Object,Weight>::removeEdge(Edge* e){
	typename vector<Edge*>::iterator it = e->start->edge.begin();
	while (*it != e) ++it;
	e->start->edge.erase(it);
	it = e->end->inedge.begin();
	while (*it != e) ++it;
	e->end->inedge.erase(it);
	it = edge.begin();
	while (*it != e) ++it;
	edge.erase(it);
	delete e;
}

template<typename Object,typename Weight>
void Graph<Object,Weight>::insertUndirectedEdge(Vertex* v,Vertex* w,Weight t){
	insertEdge(v,w,t);
	insertEdge(w,v,t);
}

template<typename Object,typename Weight>
void Graph<Object,Weight>::removeVertex(Vertex* v){
	// remove edges for adjacent verticies
	for (int i = 0; i < v->edge.size(); ++i) {
		Edge* e = v->edge[i];
		typename vector<Edge*>::iterator it = e->end->inedge.begin();
		while (*it != e) ++it;
		e->end->inedge.erase(it);
		it = edge.begin();
		while (*it != e) ++it;
		edge.erase(it);
	}
	// remove edges for incident verticies
	for (int i = 0; i < v->inedge.size(); ++i) {
		Edge* e = v->edge[i];
		typename vector<Edge*>::iterator it = e->end->edge.begin();
		while (*it != e) ++it;
		e->end->edge.erase(it);
		it = edge.begin();
		while (*it != e) ++it;
		edge.erase(it);
	}
	typename vector<Vertex*>::iterator it = vertex.begin();
	while (it != v) ++it;
	vertex.erase(it);
	delete v;
}

template<typename Object,typename Weight>
unsigned int Graph<Object,Weight>::numVertices(){
	return vertex.size();
}

template<typename Object,typename Weight>
unsigned int Graph<Object,Weight>::numEdges(){
	return edge.size();
}

template<typename Object,typename Weight>
vector<typename Graph<Object,Weight>::Vertex* > Graph<Object,Weight>::vertices(){
	return vertex;
}

template<typename Object,typename Weight>
vector<typename Graph<Object,Weight>::Edge* > Graph<Object,Weight>::edges(){
	return edge;
}

template<typename Object,typename Weight>
void Graph<Object,Weight>::print(){
   cout << "vertices:" << endl;
   for(unsigned int i=0;i<vertex.size();i++)
      cout << vertex[i]->element << endl;
   cout << "edges:" << endl;
   for(unsigned int i=0;i<edge.size();i++)
      cout << "(" << edge[i]->start->element << "," << edge[i]->end->element << ")" << endl;
}

template<typename Object,typename Weight>
void Graph<Object,Weight>::read_file(std::string filename)
{
	std::ifstream ifs;
	ifs.open(filename.c_str());
	reset();
	int size;
	ifs >> size;
	for (int i = 0; i < size; ++i) {
		Object o;
		insertVertex(o);
	}
	int source;
	int destination;
	int weight;
	while (ifs) {
		ifs >> source >> destination >> weight;
		insertEdge(vertex[source],vertex[destination],weight);
	}
}




#endif



