/* Data Structure */
/* Prof. Dong Soo S. Kim */

/* Assignment10 */
/* dijkstra.cpp */
/* by Ji Min Kim */

/* This code is programmed at window visual studio 2010.
So, will be not compiled at linux. */

#include <iostream>
#include <iomanip>
#include <climits>
#include <string>
#include "graph.h"

using namespace std;

/* Function declare */
bool read_position(graph *g, node u, char *b);		// read_position is function that read attribute of node.
bool read_weight(graph *g, edge e, char *b);		// read_weight is function that read attribute or weight of edge.
double get_weight(graph *g, node u, node v);		// get_weight is cost function for shortest_path function.

void shortest_path(graph *g,node source, double (*cost)(graph *g, node u, node v),
				double *distance, node *parent, bool *visited);				// shortest_path is function that search shortest length and sequence of each node pair.
void initialize(graph *g, node s, double *d, node *p, bool *v);				// initialize, relax, choose is function used in shortest_path function.
void relax(graph *g, node u, node v, double(*cost)(graph *g, node u, node v), double *d, node *p);
node choose(graph *g, double *d, node *p, bool *visited);



int main(){

	graph g;

	node source;
	double **distance;	// distance matrix
	node *parent;
	bool *visited;
	string *name;		// string array for storing city name

	double* max;		// max array
	double* avg;		// avg array
	double radius=DBL_MAX;	// radius
	double diameter=0;		// diameter
	

	init_graph(&g);
	/* Set read node,edge function before reading. */
	g.read_node_attr = read_position;
	g.read_edge_attr = read_weight;
	read_graph("italy.gl", &g);

	/* Seize memory space for parameter */
	distance = new double*[number_of_nodes(&g)];
	for(int i=0; i<number_of_nodes(&g); i++)
		distance[i] = new double[number_of_nodes(&g)];
	parent = new node[number_of_nodes(&g)];
	visited = new bool[number_of_nodes(&g)];
	name = new string[number_of_nodes(&g)];
	max = new double[number_of_nodes(&g)];
	avg = new double[number_of_nodes(&g)];

	int count=0;


	/* Calculate shortest path between all nodes. */
	forall_nodes(source,&g){
		shortest_path(&g, source, get_weight, distance[count], parent, visited);
		get_node_attr(&g, source, &name[count]);	// Store each node city name.
		count++;
	}

	/* Calculate and Print Max, Avg, Diameter, Radius*/
	cout <<"		  MAX	   AVG	"<<endl;
	for(int i=0; i<number_of_nodes(&g); i++){
		max[i]=0;
		avg[i]=0;
		for(int j=0; j<number_of_nodes(&g); j++){
			if( distance[i][j] > max[i] ) max[i]=distance[i][j];	// For each city, calculate maximum distance to all other cities.
			avg[i] = avg[i] + distance[i][j];
		}
		avg[i] = avg[i]/(number_of_nodes(&g)-1);	// For each city, calculate average distance to all other cities. (excluding itself)
		if( max[i] > diameter )	diameter=max[i]; // diameter is maximum value among city's maximum distances.				
		if(	max[i] < radius ) radius=max[i];	// radius is minimum value among city's maximum distances.
				

		cout << setw(11) << name[i] <<" : "<< setw(7) << max[i] << "	 " << setw(7) << avg[i] << endl;
	}
		cout << endl;
		cout << "=> diameter is "<< diameter << endl;
		cout << "=> radius is " << radius << endl;

	
	delete_graph(&g);

	/* Release memory space */
	delete []avg;
	delete []max;
	delete []visited;
	delete []parent;
	for(int i=0; i<number_of_nodes(&g); i++)
		delete distance[i];
	delete []distance;

	return 0;
}

/* Function definition */
/* read_position is function that read attribute of node. */
bool read_position(graph *g, node u, char *b){ 
	string p;	// For reading city name.

	b = strtok(b, " ");	
	if (b == NULL || *b == NULL)
		return false;
	p = b;
	set_node_attr(g, u, &p, sizeof(p)); 
	return true;
}

/* read_weight is function that read attribute or weight of edge. */
bool read_weight(graph *g, edge e, char *b){ 
	double w;	// For reading edge distance. 
	b = strtok(b, " "); 
	if (b == NULL || *b == NULL) 
		return false; 
	w = atof(b); 
	set_edge_attr(g, e, &w, sizeof(double)); 
	return true; 
}

/* get_weight is cost function for shortest_path function. */
double get_weight(graph *g, node u, node v){
	double w;
	if ( get_edge_attr(g, edge(u,v), &w) )
		return w;
	return DBL_MAX;
}

/* shortest_path is function that search shortest length and sequence of each node pair. */
void shortest_path(graph *g,node source, double (*cost)(graph *g, node u, node v),
				double *distance, node *parent, bool *visited)
{
		node n,u;

		initialize(g, source, distance, parent, visited);	// Call initialize

		for (int i=0; i<number_of_nodes(g)-1; i++) {
			u =choose(g, distance, parent, visited);		// Call choose
			forall_adj_nodes(n, u, g)
				relax(g,u,n,cost,distance,parent);			// Call relax
		}
}

/* initialize is function that initialize distance array, parent array, visited array. */
void initialize(graph *g, node s, double *d, node *p, bool *v)
{
	node n;

	forall_nodes(n, g) {
		d[n] = DBL_MAX;
		p[n] = NULL;
		v[n] = false;
	}
	d[s] = 0;
	p[s] = s;
}

/* choose is function that choose next visit node. */
node choose(graph *g, double *d, node *p, bool *visited)
{
	node cand = NULL;
	double min = DBL_MAX;
	node n;

	forall_nodes(n,g) {
		if (!visited[n] && d[n] < min) {
			min = d[n];
			cand = n;
		}
	}
	visited[cand] = true;
	return cand;
}

/* relax is function that refresh minimum distance. */
void relax(graph *g, node u, node v,
		double(*cost)(graph *g, node u, node v), double *d, node *p)
{
	if (d[u]+cost(g,u,v) < d[v]) {
		d[v] = d [u] + cost(g,u,v);
		p[v] = u;
	}
}




