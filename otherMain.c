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
	int returnValue;
	for (int i = 0; i < 6; i++)
	{
		returnValue = graph_add_vertex(graph, i);
		if(returnValue != 0){
			printFailure();
		}
	}
	for (int i = MAX_VERTICES; i < MAX_VERTICES + 3; i++)
	{
		returnValue = graph_add_vertex(graph, i);
		if(returnValue != -1){
			printFailure();
		}
	}


	
	

	graph_add_edge(graph, 0, 1, 2);
	graph_add_edge(graph, 0, 0, 2);
	graph_add_edge(graph, 1, 2, 2);
	graph_add_edge(graph, 2, 2, 2);
	graph_add_edge(graph, 2, 0, 2);
	graph_add_edge(graph, 3, 0, 2);
	graph_add_edge(graph, 3, 4, 2);
	graph_add_edge(graph, 3, 2, 2);
	graph_add_edge(graph, 4, 2, 2);
	graph_add_edge(graph, 4, 4, 2);
	graph_add_edge(graph, 4, 1, 2);

	graph_print(graph);

	// graph_remove_vertex(graph, 2);

	
	graph_print(graph);



	graph_print(graph);
	system("pause");
	return 0;
}