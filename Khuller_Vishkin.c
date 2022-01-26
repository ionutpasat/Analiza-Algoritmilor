#include <stdio.h>
#include <stdlib.h>
#define MAX 20

int timp;
int c[100];
int pi[100];
int E2[100][2];
int e[20][2];
int d[100];
int b[100];
int b2[100];

/* structura de graf */
struct Graf
{
    int N;
    int mat[MAX][MAX];
};

/* fucntie ce initializeaza un graf */
struct Graf *getnewGraph(int N)
{
    struct Graf *graf;
    graf = (struct Graf *)malloc(sizeof(struct Graf));
    graf->N = N;
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
        {
            graf->mat[i][j] = 0;
        }
    return graf;
}

/* functie ce adauga muchii in matricea de adiacenta a unui graf */
void add_edges(struct Graf *graf, int m1, int m2)
{
    graf->mat[m1][m2] = 1;
    graf->mat[m2][m1] = 1;
}

/* functie care printeaza un graf */
void print_graph(struct Graf *graf)
{
    printf("\n");
    for (int i = 0; i < graf->N; i++)
    {
        for (int j = 0; j < graf->N; j++)
        {
            printf("%d ", graf->mat[i][j]);
        }
        printf("\n");
    }
}

void explorare(int *pos, int u, int E2[100][2], struct Graf *graf)
{
    d[u] = b[u] = b2[u] = ++timp;
    e[u][0] = u; e[u][1] = u;
    c[u] = 2;
    for(int v = 0; v < graf->N; v++)
        if(graf->mat[u][v] == 1)
        {
            if(c[v] == 1)
            {
                pi[v] = u;
                E2[*pos][0] = u; E2[*pos][1] = v; *pos = *pos + 1;
                explorare(pos, v, E2, graf);
                if(b[v] < b[u]) {b[u] = b[v]; e[u][0] = e[v][0]; e[u][1] = e[v][1];}
                if(d[u] < b2[v])
                {
                    if(d[u] < b[v])
                    {
                        E2[*pos][0] = e[v][0]; E2[*pos][1] = e[v][1]; *pos = *pos + 1;;
                        b2[v] = b[v];
                    }
                }
                b2[v] = b[v];
            }
        }
        else
        {
            if(pi[u] != v)
                if(d[v] < b[u]) {b[u] = d[v]; e[u][0] = u; e[u][1] = v;}
        }
    c[u] = 3;    
}

int arc_2_conectat(struct Graf *graf)
{
    int V = graf->N;
    for (int u = 0; u < V; u++)
    {
        c[u] = 1;
        pi[u] = 0;
    }
    timp = 0;
    for(int i = 0; i < 100; i++)
        for(int j = 0; j < 2; j++)
            E2[i][j] = 0;
    int r = 0;
    int pos = 0;
    explorare(&pos, r, E2, graf);
    return pos;
}


int main()
{
    struct Graf *first_graf;
    int  N1, m1, m2;
    printf("Introduceti nr. de noduri din graful curent: ");
    scanf("%d", &N1);
    /* definesc intai graful */
    first_graf = getnewGraph(N1);
    printf("Introduceti perechile de muchii pt. primul graf[(-1 -1) pt. a iesi]: \n");
    while (1)
    {
        scanf("%d %d", &m1, &m2);
        if (m1 == -1 && m2 == -1)
            break;
        add_edges(first_graf, m1, m2);
    }
    int pos = arc_2_conectat(first_graf);
    for(int i = 0; i < pos; i++)
    {
        for (int j = 0; j < 2; j++)
        {
           printf("%d ", E2[i][j]); 
        }
        printf("\n");
    }
}