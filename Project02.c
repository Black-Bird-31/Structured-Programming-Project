#include <stdio.h>
struct Node
{
    int nodeid;
    int adjcount;
    int adjs[10];
    int costs[10];
};
int addNode(struct Node *p, int nid, int count)
{
    int i = 0, ncount = count;
    for (i = 0; i < count; i++)
    {
        if (p[i].nodeid == nid)
        {
            break;
        }
    }
    if (i == count)
    {
        p[i].nodeid = nid;
        p[i].adjcount = 0;
        ncount++;
    }
    return ncount;
}
void addAdjacent(struct Node *p, int nid1, int nid2, int cost, int count)
{
    int i = 0, index;
    for (i = 0; i < count; i++)
    {
        if (p[i].nodeid == nid1)
        {
            int c = p[i].adjcount;
            p[i].adjs[c] = nid2;
            p[i].costs[c] = cost;
            p[i].adjcount = c + 1;

            break;
        }
    }
}
int added(int *list, int lcount, int nid)
{
    int i = 0;
    for (i = 0; i < lcount; i++)
    {
        if (list[i] == nid)
        {
            return 1;
        }
    }
    return 0;
}
void findpath(struct Node *p, int count, int start, int end, int *list, int *clist, int lcount)
{
    int index = 0, i = 0;
    if (list[lcount - 1] == end)
    {
        int tcost = 0;
        printf("\n");
        for (i = 0; i < lcount; i++)
        {
            printf(" %d ", list[i]);
            tcost += clist[i];
        }
        printf(" cost = %d", tcost);
        return;
    }
    for (i = 0; i < count; i++)
    {
        if (p[i].nodeid == start)
        {
            index = i;
            break;
        }
    }
    for (i = 0; i < p[index].adjcount; i++)
    {
        int a = added(list, lcount, p[index].adjs[i]);
        if (a == 0)
        {
            list[lcount] = p[index].adjs[i];
            clist[lcount] = p[index].costs[i];
            lcount++;

            findpath(p, count, p[index].adjs[i], end, list, clist, lcount);
            lcount--;
        }
    }
}

void findTriangles(struct Node *p, int count)
{
    for (int i = 0; i < count; i++)
    {
        for (int j = i + 1; j < count; j++)
        {
            for (int k = j + 1; k < count; k++)
            {
                int node1 = p[i].nodeid;
                int node2 = p[j].nodeid;
                int node3 = p[k].nodeid;
                int edge1 = 0, edge2 = 0, edge3 = 0;
                for (int x = 0; x < p[i].adjcount; x++)
                {
                    if (p[i].adjs[x] == node2 || p[i].adjs[x] == node3)
                    {
                        edge1++;
                    }
	         	}

                for (int x = 0; x < p[j].adjcount; x++)
                {

                    if (p[j].adjs[x] == node1 || p[j].adjs[x] == node3)
                    {
                        edge2++;
                    }
                }
                for (int x = 0; x < p[k].adjcount; x++)
                {

                    if (p[k].adjs[x] == node1 || p[k].adjs[x] == node2)
                    {
                        edge3++;
                    }
                }
                if (edge1 == 2 && edge2 == 2 && edge3 == 2)
                {
                    printf("Triangle found: %d %d %d %d\n", node1,node2,node3,node1);
                }
            }
        }
    }
}
int main()
{
    struct Node nodes[50];
    int nodecount = 0;
    int n1 = 0, n2 = 0, c = 0;

    while (1)
    {
        printf("n1, n2, cost ? ");
        scanf("%d %d %d", &n1, &n2, &c);
        if (n1 == -9 || n2 == -9 || c == -9)
        {
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

    findTriangles(nodes, nodecount);

    return 0;
}