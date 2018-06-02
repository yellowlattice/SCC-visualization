#include<iostream>
#include<vector>
#include<cstdlib>
#include<stdio.h>

using namespace std;
int *root, *s, *DFN, *LOW, *visit, *instack;
int top = 0;
int num = 0;
int V, E;
int time = 0;
int **edge;
struct Node
{
    int id;
    Node *next;
    Node(int s = 0){id = s; next = NULL;}
};
Node *G;

void tarjan(int u){
    DFN[u] = LOW[u] = ++time;
    visit[u] = 1;
    s[top++] = u;
    instack[u] = 1;
    Node *tmp = G[u].next;
    while(tmp){
        int v = tmp->id;
        if(visit[v] == 0){
            tarjan(v);
            LOW[u] = (LOW[u] > LOW[v])?LOW[v]:LOW[u];
        }
        else if(instack[v]){
            LOW[u] = (LOW[u] > DFN[v])?DFN[v]:LOW[u];
        }
        tmp = tmp->next;
    }
    int m;
    if(DFN[u] == LOW[u]){
        num++;
        do{
            m = s[--top];
            instack[m] = 0;
            if(m!=u)
            {
                root[u]--;
                root[m] = u;
            }
        }while(m != u);
    }
}

int main(){
    freopen("Data-CCC.txt","r",stdin);
    freopen("res.txt","w",stdout);
    cin >> V >> E;
    s = new int[V];
    DFN = new int[V];
    LOW = new int[V];
    visit = new int[V];
    instack = new int[V];
    root = new int[V];
    G = new Node[V];
    int a, b;
    for(int i = 0; i < V; i++)
    {
        visit[i] = 0;
        instack[i] = 0;
        root[i] = -1;
    }
    for(int i = 0; i < E; i++)
    {
        scanf("%d %d",&a,&b);
        if(a >= 0 && b >= 0)
        {
            Node *p = new Node(b);
            p->next = G[a].next;
            G[a].next = p;
        }
    }
    for(int i = 0; i < V; i++)if(visit[i] == 0) tarjan(i);
    //int maxr = 0;
    //cout << num << endl;
    printf("{\n\"nodes\":[\n");
    for(int i = 0; i < V; i++) if(root[i] < -1) printf("{\"id\": \"%d\", \"group\": %d},\n", i, -root[i]);
    printf("]\n,");
    printf("\"links\":[\n");
    cin >> V >> E;
    for(int i = 0; i < E; i++)
    {
        scanf("%d %d",&a,&b);
        if(root[a] > 0 && root[b] >0 && root[a] != root[b]) printf("{\"source\": \"%d\", \"target\": \"%d\", \"value\": 1},\n", root[a], root[b]);
    }
    printf("]\n}");
    //for(int i = 0; i < V; i++) if(root[i] < -1)
    //for(int i = 0; i < V; i++) if(root[i] == maxr) printf("%d ",i);
	return 0;
}
