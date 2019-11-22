#include "graph.h"
#include <stdio.h>
#include <stdlib.h>

Graph *graph_initialize(){
	Graph*  newGraph = malloc(sizeof(Graph*));
	if(newGraph == NULL){
		return NULL;
	}
	newGraph->max_vertex = 0;
	for (int i = 0; i < MAX_VERTICES; i++)
	{
		for (int j = 0; j < MAX_VERTICES; j++)
		{
			newGraph->adj_matrix[i][j] = 0;
		}
	}
	for (int i = 0; i < MAX_VERTICES; i++)
	{
		newGraph->visited[i] = 0;
	}
	return newGraph;
}

// Vertex Operations
int graph_add_vertex(Graph *graph, int v1){
	if(graph == NULL){
		return -1;
	}
	if(graph_contains_vertex(graph,v1) == 1){
		return -1; // Already exists
	}
	if(v1 >= MAX_VERTICES || v1 < 0){ // TO-DO - Write helper function for this
		return -1; // Bad Vertex
	}
	else{ // Doesn't exist
		graph->adj_matrix[v1][v1] = -1;
		return 0;
	}
}

int graph_contains_vertex(Graph *graph, int v1){
	if(graph == NULL){
		return 0;
	}
	if(v1 >= MAX_VERTICES || v1 < 0){ // TO-DO - Write helper function for this
		return 0; // Bad Vertex
	}
	if(graph->adj_matrix[v1][v1] == -1){
		return 1;
	}
	
	for (int i = 0; i < MAX_VERTICES; i++)
	{
		// Check if there are edges FROM v1 TO other vertices
		if(graph->adj_matrix[v1][i] != 0){
			return 1;
		}
		// Check if there are edges TO v1 FROM other vertices
		if(graph->adj_matrix[i][v1] != 0){
			return 1;
		}
	}
	// Should never really get to this next line
	return 0;

}

int graph_remove_vertex(Graph *graph, int v1){
	if(graph == NULL){
		return -1;
	}
	if(graph_contains_vertex(graph,v1) == 0){
		return 0;
	}
	if(v1 >= MAX_VERTICES || v1 < 0){ // TO-DO - Write helper function for this
		return -1; // Bad Vertex
	}
	// Only vertex without edges
	if(graph->adj_matrix[v1][v1] == -1){
		graph->adj_matrix[v1][v1] = 0;
	}
	// Remove all edges FROM and TO V1
	for (int i = 0; i < MAX_VERTICES; i++)
	{
		// Delete edges FROM v1 TO other vertices
		graph->adj_matrix[v1][i] = 0;
		// Delete edges TO v1 FROM other vertices
		graph->adj_matrix[i][v1] = 0;
	}
	// Success
	return 0;

}

// Edge Operations
// Errors = -1
// Success = 0
int graph_add_edge(Graph *graph, int v1, int v2, int wt){
	if(graph == NULL){
		return -1;
	}
	// Not in graph
	if(graph_contains_vertex(graph, v1) == 0 || graph_contains_vertex(graph, v2) == 0){
		return -1;
	}
	if(graph->adj_matrix[v1][v1] == -1){
		graph->adj_matrix[v1][v1] = 0;
	}
	if(graph->adj_matrix[v2][v2] == -1){
		graph->adj_matrix[v2][v2] = 0;
	}
	graph->adj_matrix[v1][v2] = wt;
	return 0;
}

int graph_contains_edge(Graph *graph, int v1, int v2){
	if(graph == NULL){
		return 0;
	}
	// Not in graph
	if(graph_contains_vertex(graph, v1) == 0 || graph_contains_vertex(graph, v2) == 0){
		return 0;
	}
	if(graph->adj_matrix[v1][v2] == 0){
		return 0;
	}
	else{
		return 1;
	}
}


int graph_remove_edge(Graph *graph, int v1, int v2){
	if(graph == NULL){
		return -1;
	}
	// Not in graph
	if(graph_contains_vertex(graph, v1) == 0 || graph_contains_vertex(graph, v2) == 0){
		return -1;
	}
	// Edge doesn't even exists
	if(graph->adj_matrix[v1][v2] == 0){
		return 0;
	}
	// Remove edge
	graph->adj_matrix[v1][v2] = 0;

	// Possible that both vertice exists without any edges
	for (int i = 0; i < MAX_VERTICES; i++)
	{
		// For v1
		// Check if there are edges FROM v1 TO other vertices
		if(graph->adj_matrix[v1][i] != 0){
			return 0;
		}
		// Check if there are edges TO v1 FROM other vertices
		if(graph->adj_matrix[i][v1] != 0){
			return 0;
		}
	}
	graph->adj_matrix[v1][v1] = -1;
	for (int i = 0; i < MAX_VERTICES; i++)
	{
	// For v2
		// Check if there are edges FROM v2 TO other vertices
		if(graph->adj_matrix[v2][i] != 0){
			return 0;
		}
		// Check if there are edges TO v2 FROM other vertices
		if(graph->adj_matrix[i][v2] != 0){
			return 0;
		}
	}
	graph->adj_matrix[v2][v2] = -1;
	return 0;

}

// Graph Metrics Operations
// Errors = -1
int graph_num_vertices(Graph *graph){
	if(graph == NULL){
		return -1;
	}
	int numOfVertices = 0;
	for (int i = 0; i < MAX_VERTICES; i++)
	{
		int numRow = 0;
		int numColumn = 0;
		for (int j = 0; j < MAX_VERTICES; j++)
		{
			if(graph->adj_matrix[i][j] != 0){
				numRow +=1;
			}
			if(graph->adj_matrix[j][i] != 0){
				numColumn +=1;
			}
		}
		if(numRow > 0 || numColumn > 0){
			numOfVertices +=1;
		}
	}
	return numOfVertices;
}

int graph_num_edges(Graph *graph){
	if(graph == NULL){
		return -1;
	}
	int numOfEdges = 0;
	for (int i = 0; i < MAX_VERTICES; i++)
	{
		for (int j = 0; j < MAX_VERTICES; j++)
		{
			if(graph->adj_matrix[i][j] == -1){
				continue;
			}
			if(graph->adj_matrix[i][j] != 0){
				numOfEdges +=1;
			}
		}
	}
	return numOfEdges;
}

int graph_total_weight(Graph *graph){
	if(graph == NULL){
		return -1;
	}
	int totalWeight = 0;
	for (int i = 0; i < MAX_VERTICES; i++)
	{
		for (int j = 0; i < MAX_VERTICES; j++)
		{
			if(graph->adj_matrix[i][j] == -1){
				continue;
			}
			if(graph->adj_matrix[i][j] != 0){
				totalWeight += graph->adj_matrix[i][j];
			}
		}
	}
	return totalWeight;
}

// Vertex Metrics Operations
int graph_get_degree(Graph *graph, int v1){
	if(graph == NULL){
		return -1;
	}
	if(graph_contains_vertex(graph,v1) == 0){
		return -1; // Doesn't exist
	}
	if(graph->adj_matrix[v1][v1] == -1){
		// Just exists no edges to and from v1
		return 0;
	}
	int degree = 0;
	for (int i = 0; i < MAX_VERTICES; i++)
	{
		if(graph->adj_matrix[v1][i] != 0){
			degree +=1;
		}
		if(graph->adj_matrix[i][v1] != 0){
			degree +=1;
		}
	}
	// if(graph->adj_matrix[v1][v1] != 0){
	// 	degree -=1;
	// }
	return degree;
}

int graph_get_edge_weight(Graph *graph, int v1, int v2){
	if(graph == NULL){
		return -1;
	}
	// Not in graph
	if(graph_contains_vertex(graph, v1) == 0 || graph_contains_vertex(graph, v2) == 0){
		return -1;
	}
	if(graph->adj_matrix[v1][v2] == 0){
		return -1;
	}
	return graph->adj_matrix[v1][v2];
}

int graph_is_neighbor(Graph *graph, int v1, int v2){
	if(graph == NULL){
		return 0;
	}
	if(graph_contains_vertex(graph, v1) == 0 || graph_contains_vertex(graph, v2) == 0){
		return 0;
	}
	if(v1 == v2){
		if(graph->adj_matrix[v1][v2] != 0){
			return 1;
		}
	}
	if(graph->adj_matrix[v1][v2] != 0 || graph->adj_matrix[v2][v1] != 0){
		return 1;
	}
	return 0;


}

int *graph_get_predecessors(Graph *graph, int v1){
	if(graph == NULL){
		return NULL;
	}
	if(graph_contains_vertex(graph, v1) == 0){
		return NULL;
	}
	if(graph->adj_matrix[v1][v1] == -1){
		//  Vertex only exists - No edges To and From
		return 0;
	}
	int* predecesors = malloc(sizeof(int) * MAX_VERTICES);
	int index = 0;
	for (int i = 0; i < MAX_VERTICES; i++)
	{
		if(graph->adj_matrix[i][v1] != 0){
			predecesors[index] = i;
			index ++;
		}
	}
	predecesors[index] = -1;
	return predecesors;
	
}
int *graph_get_successors(Graph *graph, int v1){
	if(graph == NULL){
		return NULL;
	}
	if(graph_contains_vertex(graph, v1) == 0){
		return NULL;
	}
	if(graph->adj_matrix[v1][v1] == -1){
		//  Vertex only exists - No edges To and From
		return 0;
	}
	int* successor = malloc(sizeof(int) * MAX_VERTICES);
	int index = 0;
	for (int i = 0; i < MAX_VERTICES; i++)
	{
		if(graph->adj_matrix[v1][i] != 0){
			successor[index] = i;
			index ++;
		}
	}
	successor[index] = -1;
	return successor;

}

// Graph Path Operations
int graph_has_path(Graph *graph, int v1, int v2);

// Input/Output Operations
void graph_print(Graph *graph){
	if(graph == NULL){
		return;
	}
	char* filler = "-";
	for (int i = 0; i < MAX_VERTICES; i++)
	{
		printf("%3d", i);
	}
	printf("\n");
	for (int i = 0; i < MAX_VERTICES; i++)
	{
		printf("%3s",filler );
	}
	printf("\n");
	for (int i = 0; i < MAX_VERTICES; i++)
	{
		for (int j = 0; j < MAX_VERTICES; j++)
		{
			printf("%3d", graph->adj_matrix[i][j]);
		}
		printf("\n");
	}
	printf("\n");
}
void graph_output_dot(Graph *graph, char *filename);

int graph_load_file(Graph *graph, char *filename){
	printf("GOT HERE\n");
	if(graph == NULL){
		return -1;
	}
	printf("GOT HERE\n");
	printf("%s\n", filename);
	FILE* fp = fopen(filename, "r");
	printf("GOT HERE\n");
	if(fp == NULL){
		return -1;
	}
	printf("GOT HERE\n");
	char buffer[FILE_ENTRY_MAX_LEN];
	while(feof(fp) == 0){
		fgets(buffer, FILE_ENTRY_MAX_LEN, fp);
		printf("%s\n",buffer );
	}
	fclose(fp);
	return 0;
}

int graph_save_file(Graph *graph, char *filename);