/* Data Structure */
/* Prof. Dong Soo S. Kim */

/* Assignment9 */
/* erdos.cpp */
/* by Ji Min Kim */

/* This code is programmed at window visual studio 2010.
So, will be not compiled at linux. */
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <time.h>
#include "graph.h"

using namespace std;

/* erdos_renyi_graph is function that draw Erdos-Renyi graph. */
graph* erdos_renyi_graph(int n, double p, int seed=0, int directed=0){

        graph* g;

	g = new graph;
        init_graph(g);

	/* Set directed or undirected */
	if( directed ) make_directed(g);
	else make_undirected(g);

        for(int i=0; i<n; i++) insert_node(g, i);

	/* If seed=0, use time seed. */
	if( seed ) srand( seed );
	else srand(time(NULL));

	/* Draw edge according to p(probablity) */
        for(int i=0; i<n; i++){
		/* If dirceted, check all pair. Else, check half pair */
                for(int j=(directed==1) ? 0:i; j<n; j++){
                        if( i==j ) continue;	// skip self edge
                        double check = (double)rand()/RAND_MAX;
                        if( check <= p ) insert_edge(g, edge(i,j)); // When in probablity, draw edge.
                }
        }

        return g;
}


int main (int argc, char **argv){
        graph* g;
	node n;
	edge e;
	int counter=0;

        g = erdos_renyi_graph(100, 0.2, 1, 1);

	/* Check each node degree. */
	ofstream outfile ("erdos_p=0.2_seed=1_direction=1.txt");

	if(outfile.is_open()){
		/* increase counter if node has out edge. */
		forall_nodes(n, g){
			forall_out_edges(e,n,g){
				counter++;
			}
		outfile<<counter<<endl;
		counter=0;

		}
	outfile.close();
	}


        delete_graph(g);

	return 0;
}
