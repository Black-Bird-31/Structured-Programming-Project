#include <stdio.h>

// Structure to represent a node in the graph
struct Node {
    int nodeid;         // Node ID
    int adjcount;       // Number of adjacent nodes
    int adjs[10];       // Array to store adjacent node IDs
    int costs[10];      // Array to store costs of edges to adjacent nodes
};

// Function to add a new node to the graph
int addNode(struct Node *p, int nid, int count) {
    int i, ncount = count;
    // Check if the node already exists
    for (i = 0; i < count; i++) {
        if (p[i].nodeid == nid) {
            break;
        }
    }
    // If the node doesn't exist, add it to the graph
    if (i == count) {
        p[i].nodeid = nid;
        p[i].adjcount = 0;
        ncount++;
    }
    return ncount;
}

// Function to add an adjacent node and its corresponding cost
void addAdjacent(struct Node *p, int nid1, int nid2, int cost, int count) {
    int i, index;
    // Find the index of the node with ID nid1
    for (i = 0; i < count; i++) {
        if (p[i].nodeid == nid1) {
            int c = p[i].adjcount;
            // Add the adjacent node and its cost to the arrays
            p[i].adjs[c] = nid2;
            p[i].costs[c] = cost;
            p[i].adjcount = c + 1;
            break;
        }
    }
}

// Function to check if a node is already in a list
int added(int *list, int lcount, int nid) {
    int i;
    for (i = 0; i < lcount; i++) {
        if (list[i] == nid) {
            return 1;
        }
    }
    return 0;
}

// Function to find paths in the graph
void findpath(struct Node *p, int count, int start, int end, int *list, int *clist, int lcount, int arr[], int x) {
    int index = 0, i = 0, k = 0;
    // If the last node in the list is the end node, print the path
    if (list[lcount - 1] == end) {
        for (i = 1; i < lcount - 1; i++) {
            for (int j = 0; j < x; j++) {
                if (arr[j] == list[i]) {
                    k++;
                }
            }
        }
        if ((lcount - 2) == k) {
            printf("\nPath found:");
            for (i = 0; i < lcount; i++) {
                printf(" %d ", list[i]);
            }
            printf("\n");
        }
        return;
    }
    // Find the index of the starting node
    for (i = 0; i < count; i++) {
        if (p[i].nodeid == start) {
            index = i;
            break;
        }
    }
    // Traverse adjacent nodes recursively
    for (i = 0; i < p[index].adjcount; i++) {
        int a = added(list, lcount, p[index].adjs[i]);
        if (a == 0) {
            list[lcount] = p[index].adjs[i];
            clist[lcount] = p[index].costs[i];
            lcount++;

            findpath(p, count, p[index].adjs[i], end, list, clist, lcount, arr, x);
            lcount--;
        }
    }
}

int main() {
    struct Node nodes[50];  // Array to store nodes
    int nodecount = 0;      // Number of nodes in the graph
    int n1 = 0, n2 = 0, c = 0;  // Variables to store input values

    // Input nodes and edges until -9 is entered
    while (1) {
        printf("n1, n2, cost ? ");
        scanf("%d %d %d", &n1, &n2, &c);
        if (n1 == -9 || n2 == -9 || c == -9) {
            break;
        }
        // Add nodes and edges to the graph
        nodecount = addNode(&nodes[0], n1, nodecount);
        nodecount = addNode(&nodes[0], n2, nodecount);
        addAdjacent(&nodes[0], n1, n2, c, nodecount);
        addAdjacent(&nodes[0], n2, n1, c, nodecount);
    }

    int start, end;
    printf("start, end ? ");
    scanf("%d %d", &start, &end);

    int list[50], clist[50], lcount = 0;  // Arrays to store path and cost
    list[0] = start;
    clist[0] = 0;
    lcount = 1;

    int arr1[50], i = 0, x;  // Array to store visas for the graph
    printf("Enter visas for this Graph:\n");
    while (1) {
        scanf("%d", &arr1[i]);
        if (arr1[i] == -9) {
            x = i;
            break;
        }
        i++;
    }

    // Find paths in the graph
    findpath(nodes, nodecount, start, end, list, clist, lcount, arr1, x);

    return 0;
}
