#include "graph.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void printFailure(){
	printf("TEST FAILED!!!!!!!!\n");
	system("pause");
}

int main(int argc, char const *argv[])
{
	Graph* graph = graph_initialize();
	for (int i = 0; i < 6; i++)
	{
		graph_add_vertex(graph, i);
	}
	graph_print(graph);

	// Self-edges
	graph_add_edge(graph, 0, 0, 5);
	graph_add_edge(graph, 2, 2, 5);
	graph_add_edge(graph, 3, 3, 5);
	graph_add_edge(graph, 4, 4, 5);
	graph_add_edge(graph, 5, 5, 5);

	graph_add_edge(graph, 0, 3, 5);
	graph_add_edge(graph, 0, 1, 5);
	graph_add_edge(graph, 1, 0, 5);
	graph_add_edge(graph, 1, 3, 5);
	graph_add_edge(graph, 1, 4, 5);
	graph_add_edge(graph, 1, 5, 5);
	graph_add_edge(graph, 4, 5, 5);
	graph_add_edge(graph, 2, 1, 5);


	graph_print(graph);

	printf("Number of vertices = %d\n",graph_num_vertices(graph));
	printf("Number of Edges = %d\n",graph_num_edges(graph));

	graph_remove_edge(graph, 1, 0);
	graph_remove_edge(graph, 1, 3);
	graph_remove_edge(graph, 1, 4);
	graph_remove_edge(graph, 1, 5);
	graph_remove_edge(graph, 2, 1);
	graph_remove_edge(graph, 2, 2);

	graph_print(graph);

	printf("Number of vertices = %d\n",graph_num_vertices(graph));
	printf("Number of Edges = %d\n",graph_num_edges(graph));

	graph_print(graph);

	// graph_remove_edge(graph, 0, 0);
	// printf("Number of vertices = %d\n",graph_num_vertices(graph));
	// graph_print(graph);
	system("pause");
	getchar();
	return 0;
}