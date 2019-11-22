#include "graph.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void printSuccess(){
	printf("SUCCESS!\n");
}
void printFailure(){
	printf("FAILURE!!!\n");
}

int main(int argc, char const *argv[])
{ 
	char* menu = "\
	1. Add Vertex | X\n\
	2. Contains Vertex | X\n\
	3. Remove Vertex | X\n\
	4. Add Edge | X Y W\n\
	5. Contains Edge | X Y\n\
	6. Remove Edge | X Y\n\
	7. Number of Vertices\n\
	8. Number of Edges\n\
	9. Total Weight\n\
	10.Get Degree | X\n\
	11. Get Edge Weight | X Y\n\
	12. is Neighbour | X Y\n\
	13. Get Predecessor | X\n\
	14. Get Successor | X\n\
	15. Has Path | X Y\n\
	16. Print\n\
	17. Output Graphviz | filename\n\
	18. Load File | filename\n\
	19. Save File | filename\n"; 
	
	int input = 0;
	Graph* graph = graph_initialize();
	while(input != -1){
		printf("%s\n", menu);
		int choice;
		int v1, v2, w;
		int* predecessor;
		int* successor;
		int returnValue;
		scanf("%d", &choice);
		printf("Switch based on %d\n", choice );
		switch(choice){
			case 1: 
				scanf("%d", &v1 );
				// v1 = strtol(strtok(NULL, " "), NULL, 10);
				returnValue = graph_add_vertex(graph, v1);
				if(returnValue == 0){
					printSuccess();
				}
				else{
					printFailure();
				}
				break;
			case 2:
				scanf("%d", &v1 );
				// v1 = strtol(strtok(NULL, " "), NULL, 10);
				returnValue = graph_contains_vertex(graph, v1);
				if(returnValue == 1){
					printSuccess();
				}
				else{
					printFailure();
				}
				break;
			case 3:
				scanf("%d", &v1 );
				// v1 = strtol(strtok(NULL, " "), NULL, 10);
				returnValue = graph_remove_vertex(graph, v1);
				if(returnValue == 0){
					printSuccess();
				}
				else{
					printFailure();
				}
				break;
			case 4:
				scanf("%d %d %d", &v1, &v2, &w );
				// v1 = strtol(strtok(NULL, " "), NULL, 10);
				// v2 = strtol(strtok(NULL, " "), NULL, 10);
				// w = strtol(strtok(NULL, " "), NULL, 10);
				returnValue = graph_add_edge(graph, v1, v2, w);
				if(returnValue == 0){
					printSuccess();
				}
				else{
					printFailure();
				}
				break;
			case 5:
				scanf("%d %d", &v1, &v2);
				// v1 = strtol(strtok(NULL, " "), NULL, 10);
				// v2 = strtol(strtok(NULL, " "), NULL, 10);
				returnValue = graph_contains_edge(graph, v1, v2);
				if(returnValue == 1){
					printSuccess();
				}
				else{
					printFailure();
				}
				break;
			case 6:
				scanf("%d %d", &v1, &v2);
				// v1 = strtol(strtok(NULL, " "), NULL, 10);
				// v2 = strtol(strtok(NULL, " "), NULL, 10);
				returnValue = graph_remove_edge(graph, v1, v2);
				if(returnValue == 0){
					printSuccess();
				}
				else{
					printFailure();
				}
				break;
			case 7:
				printf("Number of Vertices = %d\n",graph_num_vertices(graph));
				break;
			case 8:
				printf("Number of Edges = %d\n",graph_num_edges(graph));
				break;
			case 9:
				printf("Total Weight= %d\n",graph_total_weight(graph));
				break;
			case 10:
				scanf("%d", &v1);
				// v1 = strtol(strtok(NULL, " "), NULL, 10);
				printf("Degree = %d\n", graph_get_degree(graph, v1));

				break;
			case 11:
				scanf("%d %d", &v1, &v2);
				// v1 = strtol(strtok(NULL, " "), NULL, 10);
				// v2 = strtol(strtok(NULL, " "), NULL, 10);
				printf("Edge Weight = %d\n", graph_get_edge_weight(graph, v1, v2));
				break;
			case 12:
				scanf("%d %d", &v1, &v2);
				// v1 = strtol(strtok(NULL, " "), NULL, 10);
				// v2 = strtol(strtok(NULL, " "), NULL, 10);
				returnValue =  graph_is_neighbor(graph, v1, v2);
				if(returnValue == 1){
					printSuccess();
				}
				else{
					printFailure();
				}
				break;
			case 13:
				scanf("%d", &v1);
				// v1 = strtol(strtok(NULL, " "), NULL, 10);
				predecessor = graph_get_predecessors(graph, v1);
				if(predecessor == NULL){
					printFailure();
					break;
				}
				for (int i = 0; i < MAX_VERTICES || predecessor[i]!=-1; i++)
				{
					printf("Number of Predecessors = %d",predecessor[i] );
				}
				break;
			case 14:
				scanf("%d", &v1);
				// v1 = strtol(strtok(NULL, " "), NULL, 10);
				successor = graph_get_predecessors(graph, v1);
				if(successor == NULL){
					printFailure();
					break;
				}
				for (int i = 0; i < MAX_VERTICES || successor[i]!=-1; i++)
				{
					printf("Number of Successors = %d",successor[i] );
				}
				break;
			case 15:
				// Not done
				break;
			case 16:
				graph_print(graph);
				break;
			case 17:
				// Not done
				break;
			case 18:
				graph_load_file(graph, "t.txt");
				break;
			case 19:
				// Not done
				break;
			default:
				// Not done
				break;
		}
		graph_print(graph);
	}
    return 0;
}
