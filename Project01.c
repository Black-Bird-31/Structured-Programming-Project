#include <stdio.h>
struct Node{
    int nodeid;
    int adjcount;
    int adjs[10];
    int costs[10];
};
int addNode(struct Node *p, int nid, int count) {
    int i, ncount = count;
    for (i = 0; i < count; i++) {
        if (p[i].nodeid == nid) {
            break;
        }
    }
    if (i == count) {
        p[i].nodeid = nid;
        p[i].adjcount = 0;
        ncount++;
    }
    return ncount;
}
void addAdjacent(struct Node *p, int nid1, int nid2, int cost, int count) {
    int i, index;
    for (i = 0; i < count; i++) {
        if (p[i].nodeid == nid1) {
            int c = p[i].adjcount;
            p[i].adjs[c] = nid2;
            p[i].costs[c] = cost;
            p[i].adjcount = c + 1;
            break;
        }
    }
}
int added(int *list, int lcount, int nid) {
    int i;
    for (i = 0; i < lcount; i++) {
        if (list[i] == nid) {
            return 1;
        }
    }
    return 0;
}
void findpath(struct Node *p, int count, int start, int end, int *list, int *clist, int lcount, int arr[], int x) {
    int index = 0, i = 0, k = 0;
    if (list[lcount - 1] == end) {
        for (i = 1; i < lcount-1; i++) {
            for (int j = 0; j < x; j++) {
                if (arr[j] == list[i]) {
                    k++;
                }
            }
        }
        if ((lcount-2) == k){
            printf("\nPath found:");
            for (i = 0; i < lcount; i++) {
                printf(" %d ", list[i]);
            }
            printf("\n");
        }
        return;
    }
    for (i = 0; i < count; i++) {
        if (p[i].nodeid == start) {
            index = i;
            break;
        }
    }
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
    struct Node nodes[50];
    int nodecount = 0;
    int n1 = 0, n2 = 0, c = 0;
    while (1) {
        printf("n1, n2, cost ? ");
        scanf("%d %d %d", &n1, &n2, &c);
        if (n1 == -9 || n2 == -9 || c == -9) {
            break;
        }
        nodecount = addNode(&nodes[0], n1, nodecount);
        nodecount = addNode(&nodes[0], n2, nodecount);
        addAdjacent(&nodes[0], n1, n2, c, nodecount);
        addAdjacent(&nodes[0], n2, n1, c, nodecount);
    }
    int start, end;
    printf("start, end ? ");
    scanf("%d %d", &start, &end);
    int list[50], clist[50], lcount = 0;
    list[0] = start;
    clist[0] = 0;
    lcount = 1;
    int arr1[50], i = 0, x;
    printf("Enter visas for this Graph:\n");
    while (1) {
        scanf("%d",&arr1[i]);
        if (arr1[i] == -9){
            x = i;
            break;
        }
        i++;
    }
    findpath(nodes, nodecount, start, end, list, clist, lcount, arr1, x);
    return 0;
}