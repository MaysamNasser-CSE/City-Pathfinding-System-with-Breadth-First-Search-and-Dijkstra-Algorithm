#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_DISTANCE 1000
#define MAX_LINE_LENGTH 100
#include <string.h>
#include <limits.h>
#define MAX_NODES 100
#define INF INT_MAX
#define MinQueueSize 100
struct Queue_record {
int Capacity;
int Rear;
int Size;
int Front;
int *Array;
};
typedef struct Queue_record *Queue;
int Empty(Queue Q) {
return Q->Size == 0;
}
typedef struct {
char ENDD[100];
char source[100];
int distance;
} edgee;
typedef struct {
char Name[100];
int index;
} Node;
int Num_Nodes = 0;
Node nodes[MAX_NODES];
int Full(Queue Q) {
return Q->Size == Q->Capacity;
}
//function creat queue
Queue Create_queue(int Max_Elements) {
Queue qq;
if (Max_Elements < MinQueueSize) {
printf("Queue size is too small\n");
return NULL;
}
qq = (Queue)malloc(sizeof(struct Queue_record));//allocating memory for a Queue object using malloc
if (qq == NULL) {
printf("Out of space\n");
return NULL;
}
qq->Array = (int *)malloc(sizeof(int) * Max_Elements);//allocating memory for a Queue object using malloc
if (qq->Array == NULL) {
printf("Out of space\n");
free(qq);
return NULL;
}
qq->Capacity = Max_Elements;//capacity for qeuq equal number of element
Make_empty(qq);//
return qq;
}
//deallocate the memory occupied by a Queue object
void dispose_Queue(Queue q) {
if (q != NULL) {
free(q->Array);
free(q);
}
}
//function you provided increments the valuee parameter and checks if it has reached the capacity of the Queue object
int Succ(int valuee, Queue q) {
if (++valuee == q->Capacity)
valuee = 0;
return valuee;
}
void Make_empty(Queue q) {// used to clear the contents of a queue, making it empty and ready for reuse
q->Size = 0;
q->Front = 1;
q->Rear = 0;
}
void enqueue(int y, Queue q){ //function is used to insert an element at the rear of the queue
if (Full(q))
printf("Full Queue\n");
else {
q->Size++;
q->Rear = Succ(q->Rear, q);
q->Array[q->Rear] = y;
}
}
void dequeue(Queue q) {//function is used to remove the element at the front of the queue
if (Empty(q))
printf("Empty Queue!!\n");
else {
q->Size--;
q->Front = Succ(q->Front, q);
}
}
int frontt(Queue q) {
if (!Empty(q))
return q->Array[q->Front];
printf("Empty Queue!\n");
return 0;
}
int adjacency_Matrix[MAX_NODES][MAX_NODES];

void add_edge(char* starrt, char* endd, int distance) {//function is used to add an edge to a graph
    int source_Index = getNode_index(starrt);
    int dest_Index = getNode_index(endd);

    if (adjacency_Matrix[source_Index][dest_Index] == 0 || distance < adjacency_Matrix[source_Index][dest_Index]) {
        adjacency_Matrix[source_Index][dest_Index] = distance;
    }
}
int getNode_index(char* node_name) {// function is used to get the index of a node in the graph based on its name
for (int i = 0; i < Num_Nodes; i++) {
if (strcmp(nodes[i].Name, node_name) == 0)
return i;
}
strcpy(nodes[Num_Nodes].Name, node_name);
nodes[Num_Nodes].index = Num_Nodes;
return Num_Nodes++;
}

int findMin_distance(int distance[], int visit_cityee[]) {//function is used to find the index of the node with the minimum distance value among the unvisited cities
int min_iindex = -1;
int min_road = INF;
for (int j = 0; j < Num_Nodes; j++) {
if (visit_cityee[j] == 0 && distance[j] < min_road) {
min_road = distance[j];
min_iindex = j;
}
}
return min_iindex;
}
void Breadt_FirstSearch(char* start, char* end, FILE* fille) {
        int roadd[MAX_NODES];
    int source_index = getNode_index(start);
    int dest_index = getNode_index(end);
    int prevv[MAX_NODES] = {-1};
    int visitt[MAX_NODES] = {0};
    int Distances[MAX_NODES] = {0};
    int rodeLength = 0;
    int TotalDistance = 0; // total distance from source to destination
    Queue Q = Create_queue(MAX_NODES);
    if (Q == NULL) {
        printf("error!!Failed to create the queue.\n");
        return;
    }
    visitt[source_index] = 1;
    enqueue(source_index, Q);
    while (!Empty(Q)) {
        int n = frontt(Q);
        dequeue(Q);
        for (int y = 0; y < Num_Nodes; y++) {
            if (!visitt[y] && adjacency_Matrix[n][y]) {
                visitt[y] = 1;
                enqueue(y, Q);
                prevv[y] = n;
                Distances[y] = Distances[n] + 1;
                if (y == dest_index) {
                    // Found the destination node
                    printf("using Breadt_First_Searc \n");
                    fprintf(fille, "*using Breadt_First_Search* \n");
                    printf("Path found from %s to %s is :\n", start, end);
                    fprintf(fille, "Path found from %s to %s is :\n", start, end);
                    int currentt = dest_index;
                    while (currentt != -1) {
                        roadd[rodeLength++] = currentt;
                        currentt = prevv[currentt];
                    }
                    // Print the road and distances between each two cities and total destination
                    for (int m = rodeLength - 1; m >= 0; m--) {
                        fprintf(fille, "%s ", nodes[roadd[m]].Name);
                        printf("%s ", nodes[roadd[m]].Name);
                        if (m > 0) {
                            int DDistance = adjacency_Matrix[roadd[m]][roadd[m - 1]];
                            TotalDistance += DDistance; //Update destdestination
                            fprintf(fille, "%d km\n", DDistance);
                            printf("%d km\n", DDistance);
                        }
                    }

                    printf("total distance: %d edges\n", Distances[dest_index]);
                    fprintf(fille, "total distance: %d edges\n", Distances[dest_index]);
                     // Print the total distance (number of edges)
                    printf("total distance is : %d km\n", TotalDistance);
                    fprintf(fille, "total distance is: %d km\n", TotalDistance);
                    fprintf(fille, "\n-----------------------------------------\n");
                    dispose_Queue(Q);
                    return;
                }
            }
        }
    }
    if (strcmp(start, end) == 0) {
        printf("Total distance is: 0 edges\n");
        fprintf(fille, "Total distance is: 0 edges\n");
    } else {
        printf("error !!No road found from %s to %s\n", start, end);
        fprintf(fille, "error !!No road found from %s to %s\n", start, end);
    }

    dispose_Queue(Q);
}


void sort_distances(edgee distancess[], int num_distances) {//function is used to sort an array of edges based on their distances in ascending order.
edgee tempp;

for (int j = 0; j < num_distances - 1; j++) {
for (int i = 0; i < num_distances - j - 1; i++) {
if (strcmp(distancess[j].source, distancess[i + 1].source) > 0) {
//swap
tempp = distancess[i];
distancess[i] = distancess[i + 1];
distancess[i + 1] = tempp;
}
}
}
}
void Dijkstra(char* start, char* end,FILE *filee) {//function implements Dijkstra's algorithm to find the shortest path between two nodes in a grap

int dest_index = getNode_index(end);
int source_index = getNode_index(start);
int Distances[MAX_NODES];
int prevv[MAX_NODES];
int visit[MAX_NODES];
for (int j = 0; j < Num_Nodes; j++) {
Distances[j] = INF;
visit[j] = 0;
prevv[j] = -1;
}
Distances[source_index] = 0;
for (int countt = 0; countt < Num_Nodes - 1; countt++) {
int b = findMin_distance(Distances, visit);
visit[b] = 1;
for (int h = 0; h < Num_Nodes; h++) {
if (!visit[h] && adjacency_Matrix[b][h] && Distances[b] != INF &&
Distances[b] + adjacency_Matrix[b][h] < Distances[h]) {
Distances[h] = Distances[b] + adjacency_Matrix[b][h];
prevv[h] = b;
}
}
}
if (Distances[dest_index] == INF) {
printf("error!!No path found from %s to %s\n", start, end);
fprintf(filee,"error!!No path found from %s to %s\n", start, end);
} else {
fprintf(filee,"*using Dijkstra's algorithm*  :\n");
printf("using Dijkstra's algorithm  :\n");

printf("Shortest path from %s to %s:\n", start, end);

fprintf(filee,"Shortest path from %s to %s:\n", start, end);
// Backtrack from destination to source to get the path
int path_Length = 0;
int path[MAX_NODES];
int currentt = dest_index;
while (currentt != -1) {
path[path_Length++] = currentt;
currentt = prevv[currentt];
}
// Print the path and distances between each two cities
for (int jj = path_Length - 1; jj >= 0; jj--) {

fprintf(filee,"%s ", nodes[path[jj]].Name);
printf("%s ", nodes[path[jj]].Name);

if (jj > 0) {
int distance = adjacency_Matrix[path[jj]][path[jj - 1]];

fprintf(filee,"%d km \n", distance);
printf("%d km \n", distance);


}
}
}
// Print the total shortest cost
fprintf(filee,"\n  total shortest cost from %s to %s is : %d\n",start,end,Distances[dest_index]);
printf("\n  total shortest cost from %s to %s is : %d\n",start,end,Distances[dest_index]);

}

int main() {

  FILE* output_File = fopen("result.txt", "a"); // open file to write
    if (output_File == NULL) {
        printf("error file.\n");
        return;
    }
    int is_Runn = 1;

    while (is_Runn) {
        FILE* input_File;
        Num_Nodes=0;
        char sentance[MAX_LINE_LENGTH];
        int num_distance = 0;
        edgee distances[MAX_DISTANCE];

        input_File = fopen("Cities.txt", "r"); // open file to read
        if (input_File == NULL) {
            printf("error file.\n");
            return 1;
        }

        while (fgets(sentance, MAX_LINE_LENGTH, input_File) != NULL && num_distance < MAX_DISTANCE) {
            sscanf(sentance, "%s %s %dkm", distances[num_distance].source, distances[num_distance].ENDD,
                   &distances[num_distance].distance);
            num_distance++;
        }

        fclose(input_File);
        sort_distances(distances, num_distance);

        char start_city[100], end_city[100];
        printf("\nEnter source city (if we need to exit, write 'exit'): ");
        fgets(start_city, sizeof(start_city), stdin);
        start_city[strlen(start_city) - 1] = '\0'; // Remove newline character

        if (strcmp(start_city, "exit") == 0) {
            is_Runn = 0;
            break;
        }

        printf("Enter destination city (if we need to exit, write 'exit'): ");
        fgets(end_city, sizeof(end_city), stdin);
        end_city[strlen(end_city) - 1] = '\0'; // Remove newline character
        if (strcmp(end_city, "exit") == 0) {
            is_Runn = 0;
            break;
        }

        // find the distance records related to the specified source city and add corresponding edges to the graph
        for (int k = 0; k < num_distance; k++) {
            if (strcmp(distances[k].source, start_city) == 0) {
                add_edge(distances[k].source, distances[k].ENDD, distances[k].distance);
            }
        }
        for (int i = 0; i < num_distance; i++) {
            if (strcmp(distances[i].source, start_city) != 0) {
                add_edge(distances[i].source, distances[i].ENDD, distances[i].distance);
            }
        }

        Dijkstra(start_city, end_city,output_File); // call function

        Breadt_FirstSearch(start_city, end_city,output_File);
        printf("the output in file");

         // call function
    adjacency_Matrix;
    int q, w;
for(q = 0; q < Num_Nodes; q++) {//in order to get result long work
    for(w = 0; w < Num_Nodes; w++) {
        adjacency_Matrix[q][w] = 0;
    }

}
fclose(output_File);

}

    return 0;
}