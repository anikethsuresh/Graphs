#include "graph.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void DFS(Graph *graph,int v1, int v2, int* arrOfVertices);

Graph *graph_initialize(){
	Graph*  newGraph = malloc(sizeof(Graph));
	if(newGraph == NULL){
		return NULL;
	}
	newGraph->max_vertex = 0;
	int i = 0, j = 0;
	for (i = 0; i < MAX_VERTICES; i++)
	{
		for (j = 0; j < MAX_VERTICES; j++)
		{
			// Inititlize to 0
			newGraph->adj_matrix[i][j] = 0;
		}
	}
	for (i = 0; i < MAX_VERTICES; i++)
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
		return 0; // Already exists
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
	int i = 0;
	for (i = 0; i < MAX_VERTICES; i++)
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
	int i = 0;
	for (i = 0; i < MAX_VERTICES; i++)
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
	if(wt<=0){
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
	if(graph->adj_matrix[v1][v2] == 0 || graph->adj_matrix[v1][v2] == -1){
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
	// Flags
	int v1Change = 1;
	int v2Change = 1;
	// Possible that both vertice exists without any edges
	int i = 0;
	for (i = 0; i < MAX_VERTICES; i++)
	{
		// For v1
		// Check if there are edges FROM v1 TO other vertices
		if(graph->adj_matrix[v1][i] != 0){
			v1Change = 0;
			break;
		}
		// Check if there are edges TO v1 FROM other vertices
		if(graph->adj_matrix[i][v1] != 0){
			v1Change = 0;
			break;
		}
	}
	if(v1Change == 1){
		graph->adj_matrix[v1][v1] = -1;
	}
	for (i = 0; i < MAX_VERTICES; i++)
	{
	// For v2
		// Check if there are edges FROM v2 TO other vertices
		if(graph->adj_matrix[v2][i] != 0){
			v2Change = 0;
			break;
		}
		// Check if there are edges TO v2 FROM other vertices
		if(graph->adj_matrix[i][v2] != 0){
			v2Change = 0;
			break;
		}
	}
	if(v2Change == 1){
		graph->adj_matrix[v2][v2] = -1;
	}
	return 0;

}

// Graph Metrics Operations
// Errors = -1
int graph_num_vertices(Graph *graph){
	if(graph == NULL){
		return -1;
	}
	int numOfVertices = 0;
	int i = 0, j = 0;
	for (i = 0; i < MAX_VERTICES; i++)
	{
		int numRow = 0;
		int numColumn = 0;
		for (j = 0; j < MAX_VERTICES; j++)
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
	int i = 0, j = 0;
	for (i = 0; i < MAX_VERTICES; i++)
	{
		for ( j = 0; j < MAX_VERTICES; j++)
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
	int i = 0, j = 0;
	for (i = 0; i < MAX_VERTICES; i++)
	{
		for ( j = 0; j < MAX_VERTICES; j++)
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
	int i = 0;
	for (i = 0; i < MAX_VERTICES; i++)
	{
		if(graph->adj_matrix[v1][i] != 0){
			degree +=1;
		}
		if(graph->adj_matrix[i][v1] != 0){
			degree +=1;
		}
	}
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
		if(graph->adj_matrix[v1][v2] == -1){
			return 0;
		}
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
		return NULL;
	}
	int* predecessors = malloc(sizeof(int) * MAX_VERTICES);
	if(predecessors == NULL){
		return NULL;
	}
	int index = 0;
	int i = 0;
	for (i = 0; i < MAX_VERTICES; i++)
	{
		if(graph->adj_matrix[i][v1] != 0){
			predecessors[index] = i;
			index ++;
		}
	}
	predecessors[index] = -1;
	return predecessors;
	
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
		return NULL;
	}
	int* successor = (int*) malloc(sizeof(int) * MAX_VERTICES);
	if(successor == NULL){
		return NULL;
	}
	int index = 0;
	int i = 0;
	for (i = 0; i < MAX_VERTICES; i++)
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
int graph_has_path(Graph *graph, int v1, int v2){
	if(graph == NULL){
		return 0;
	}
	if(graph_contains_vertex(graph, v1) == 0 || graph_contains_vertex(graph, v2) == 0){
		return 0;
	}
	if(v1 == v2){
		if(graph->adj_matrix[v1][v2] == -1 || graph->adj_matrix[v1][v2] == 0){
			return 0;
		}
		else{
			return 1;
		}
	}
	int arrOfVertices[MAX_VERTICES] = {0}; 
	DFS(graph,v1,v2, arrOfVertices);
	if(arrOfVertices[v2] == 1){
		return 1;
	}
	else{
		return 0;
	}
}

void DFS(Graph *graph,int v1, int v2, int* arrOfVertices){
	arrOfVertices[v1] = 1;
	int i = 0;
	for (i = 0; i < MAX_VERTICES; i++)
	{
		if(v1 == i){
			continue;
		}
		if(graph->adj_matrix[v1][i] != 0 && graph->adj_matrix[v1][i] != -1){
			DFS(graph, i, v2, arrOfVertices);
		}
	}
}

// Input/Output Operations
void graph_print(Graph *graph){
	if(graph == NULL){
		return;
	}
	char* filler = "-";
	int i = 0, j = 0;
	for (i = 0; i < MAX_VERTICES; i++)
	{
		printf("%3d", i);
	}
	printf("\n");
	for (i = 0; i < MAX_VERTICES; i++)
	{
		printf("%3s",filler );
	}
	printf("\n");
	for (i = 0; i < MAX_VERTICES; i++)
	{
		for (j = 0; j < MAX_VERTICES; j++)
		{
			printf("%3d", graph->adj_matrix[i][j]);
		}
		printf("\n");
	}
	printf("\n");
}

void graph_output_dot(Graph *graph, char *filename){
	if(graph == NULL){
		return;
	}
	if(filename == NULL){
		return;
	}
	FILE* fp = fopen(filename, "w");
	if(fp == NULL){
		return;
	}
	char* start = "digraph {";
	char* end = "}";
	char* semicolon = ";";

	fprintf(fp, "%s\n", start);
	int i = 0, j = 0;
	for (i = 0; i < MAX_VERTICES; i++)
	{
		for (j = 0; j < MAX_VERTICES; j++)
		{
			if(i==j){
				if(graph->adj_matrix[i][j] == -1){
					fprintf(fp, "%d%s\n",i, semicolon);
					continue;
				}
				else if(graph->adj_matrix[i][j] != 0){
					fprintf(fp, "%d -> %d [label = %d]%s\n", i, j,graph->adj_matrix[i][j], semicolon);
					continue;
				}
			}
			else{
				if(graph->adj_matrix[i][j] != 0){
					fprintf(fp, "%d -> %d [label = %d]%s\n", i, j,graph->adj_matrix[i][j], semicolon);
					continue;
				}
			}
		}
	}

	fprintf(fp, "%s\n", end);
	fclose(fp);
	return;
}


int graph_load_file(Graph *graph, char *filename){
	if(graph == NULL){
		return -1;
	}
	if(filename == NULL){
		return -1;
	}
	FILE* fp = fopen(filename, "r");
	if(fp == NULL){
		return -1;
	}
	int i = 0, j = 0;
	for (i = 0; i < MAX_VERTICES; i++)
	{
		for (j = 0; j < MAX_VERTICES; j++)
		{
			graph->adj_matrix[i][j] = 0;
		}
	}
	char line[FILE_ENTRY_MAX_LEN];
	char* vertex1Token;
	char* vertex2Token;
	char* edgeToken;
	int vertex1;
	int vertex2;
	int edge;
	while(feof(fp) == 0){
		fgets(line, FILE_ENTRY_MAX_LEN, fp);
		vertex1Token = strtok(line, ",");
		vertex2Token=strtok(NULL, ",");
		if(vertex2Token == NULL){
			// Only vertex
			sscanf(vertex1Token, "%d", &vertex1);
			if(graph_contains_vertex(graph, vertex1) == 0){
				graph_add_vertex(graph, vertex1);
			}
		}
		else{
			edgeToken = strtok(NULL, ",");
			sscanf(vertex1Token, "%d", &vertex1);
			sscanf(vertex2Token, "%d", &vertex2);
			sscanf(edgeToken, "%d", &edge);
			if(graph_contains_vertex(graph, vertex1) == 0){
				graph_add_vertex(graph, vertex1);
			}
			if(graph_contains_vertex(graph, vertex2) == 0){
				graph_add_vertex(graph, vertex2);
			}
			graph_add_edge(graph, vertex1, vertex2, edge);
		}

	}
	fclose(fp);
	return 0;
}

int graph_save_file(Graph *graph, char *filename){
	if(graph == NULL){
		return -1;
	}
	if(filename == NULL){
		return -1;
	}
	FILE* fp = fopen(filename, "w");
	if(fp == NULL){
		return -1;
	}
	int i = 0, j = 0;
	for (i = 0; i < MAX_VERTICES; i++)
	{
		for (j = 0; j < MAX_VERTICES; j++)
		{
			if(i==j){
				if(graph->adj_matrix[i][j] == -1){
					fprintf(fp, "%d\n",i);
					continue;
				}
				else if(graph->adj_matrix[i][j] != 0){
					fprintf(fp, "%d,%d,%d\n", i, j,graph->adj_matrix[i][j]);
					continue;
				}
			}
			else{
				if(graph->adj_matrix[i][j] != 0){
					fprintf(fp, "%d,%d,%d\n", i, j,graph->adj_matrix[i][j]);
					continue;
				}
			}
		}
	}

	fclose(fp);
	return 0;
}