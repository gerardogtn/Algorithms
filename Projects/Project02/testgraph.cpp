#include <iostream>
#include <iomanip>
#include <chrono>
#include <utility>
#include <vector>
#include <deque>
#include <string>
#include <fstream>
#include <stack>
#include <algorithm>
#include <utility>
#include <limits>
#include "stdafx.h"

#undef max


class myVis {
public:
  myVis() { }
  myVis(const int& Nodes){ }
  void DiscoverNode(int NId) { printf("%i\n",NId); }
  void FinishNode(const int& NId) { }
  void ExamineEdge(const int& NId1, const int& NId2) { }
  void TreeEdge(const int& NId1, const int& NId2) { }
  void BackEdge(const int& NId1, const int& NId2) { }
  void FwdEdge(const int& NId1, const int& NId2) { }
};

bool sortFunction(int a, int b,std::vector<float> distancias);
bool sortFunction2(std::pair<int, int> a, std::pair<int, int> b, std::vector<float> distancias);

class sorter {
  std::vector<float> type_;
public:
  sorter(std::vector<float> type) : type_(type) {}
  bool operator()(int o1, int o2) const
  {
    return sortFunction(o1, o2, type_ );
  }
};

class sorter2 {
  std::vector<float> type_;
public:
  sorter2(std::vector<float> type) : type_(type) {}
  bool operator()(std::pair<int, int> o1,std::pair<int, int> o2) const
  {
    return sortFunction2(o1, o2, type_ );
  }
};

//DECLARACIÓN OF DIJKSTRA'S ALGORITHM
//dijkstra (Grafo,Nodo origen)
void dijkstra(TPt<TNodeEDatNet<TInt, TFlt> >  graph, const int &SrcNId);
void prim(TPt<TNodeEDatNet<TInt, TFlt> >  graph, const int &v);
void printVector(std::vector<int> vector);
void menu(TPt<TNodeEDatNet<TInt, TFlt> >  graph);
void kruskal(TPt<TNodeEDatNet<TInt, TFlt> > graph);
void fw(TPt<TNodeEDatNet<TInt, TFlt> >  graph);



int main(int argc, char* argv[]) {
  
  //Declaración del grafo dirigido
  TPt<TNodeEDatNet<TInt, TFlt> >  grafo = TNodeEDatNet<TInt, TFlt>::New();
  
//  menu(grafo);
  
  //Codigo comentado para test
    //ADD NODES
    //AddNode(id)
    for (int i = 1; i<15; i++)
    {
      grafo->AddNode(i);
    }
    //ADD EDGES
    //(Origen, Desitno, Weight)
    grafo->AddEdge(1,4,8);
    grafo->AddEdge(1,3,8);
    grafo->AddEdge(2,5,7);
    grafo->AddEdge(3,10,4);
    grafo->AddEdge(3,5,8);
    grafo->AddEdge(3,2,7);
    grafo->AddEdge(4,7,3);
    grafo->AddEdge(4,5,1);
    grafo->AddEdge(4,8,2);
    grafo->AddEdge(5,6,9);
    grafo->AddEdge(6,13,4);
    grafo->AddEdge(7,4,6);
    grafo->AddEdge(8,9,3);
    grafo->AddEdge(8,7,3);
    grafo->AddEdge(9,10,2);
    grafo->AddEdge(9,12,4);
    grafo->AddEdge(10,3,10);
    grafo->AddEdge(10,6,6);
    grafo->AddEdge(11,12,6);
    grafo->AddEdge(12,11,8);
    grafo->AddEdge(12,9,2);
    grafo->AddEdge(12,14,9);
    grafo->AddEdge(13,14,6);
    grafo->AddEdge(14,13,2);
  
    // Floyd warshall.
    std::cout << "++++++FLOYD-WARSHALL: " << std::endl;
    auto rbt_ib = std::chrono::high_resolution_clock::now();
    fw(grafo);
    auto rbt_ie = std::chrono::high_resolution_clock::now();
    auto rbt_i = std::chrono::duration_cast<std::chrono::microseconds>(rbt_ie-rbt_ib);
    std::cout << "Tiempo en microsegundos: " << rbt_i.count() << std::endl;
  
    //BFS
    std::cout << "++++++BFS: " << std::endl;
    rbt_ib = std::chrono::high_resolution_clock::now();
    PNGraph GBFS =TSnap::GetBfsTree(grafo, 1, true, true);
    rbt_ie = std::chrono::high_resolution_clock::now();
    rbt_i = std::chrono::duration_cast<std::chrono::microseconds>(rbt_ie-rbt_ib);
    std::cout << "Tiempo en microsegundos: " << rbt_i.count() << std::endl;
    for (TNGraph::TNodeI NI = GBFS->BegNI(); NI < GBFS->EndNI(); NI++)
    {
      printf("%d\n", NI.GetId());
    }
  
    //DFS
    std::cout << "++++++DFS: " << std::endl;
    rbt_ib = std::chrono::high_resolution_clock::now();
    myVis vis(grafo->GetNodes());
    TCnCom::GetDfsVisitor(grafo, vis);
    rbt_ie = std::chrono::high_resolution_clock::now();
    rbt_i = std::chrono::duration_cast<std::chrono::microseconds>(rbt_ie-rbt_ib);
    std::cout << "Tiempo en microsegundos: " << rbt_i.count() << std::endl;
  
  
    //Dijkstra
    std::cout << "++++++DJIKSTRA: " << std::endl;
    rbt_ib = std::chrono::high_resolution_clock::now();
    dijkstra(grafo, 1);
    rbt_ie = std::chrono::high_resolution_clock::now();
    rbt_i = std::chrono::duration_cast<std::chrono::microseconds>(rbt_ie-rbt_ib);
    std::cout << "Tiempo en microsegundos: " << rbt_i.count() << std::endl;
  
    //Prim
    std::cout << "++++++PRIM: " << std::endl;
    rbt_ib = std::chrono::high_resolution_clock::now();
    prim(grafo, 1);
    rbt_ie = std::chrono::high_resolution_clock::now();
    rbt_i = std::chrono::duration_cast<std::chrono::microseconds>(rbt_ie-rbt_ib);
    std::cout << "Tiempo en microsegundos: " << rbt_i.count() << std::endl;
  
    //Kruskal
    std::cout << "++++++KRUSKAL: " << std::endl;
    rbt_ib = std::chrono::high_resolution_clock::now();
    kruskal(grafo);
    rbt_ie = std::chrono::high_resolution_clock::now();
    rbt_i = std::chrono::duration_cast<std::chrono::microseconds>(rbt_ie-rbt_ib);
    std::cout << "Tiempo en microsegundos: " << rbt_i.count() << std::endl;

  
  return 0;
}

//IMPLEMENTATION OF DIJKSTRA'S ALGORITHM
//dijkstra (Grafo,Nodo origen)
void dijkstra(TPt<TNodeEDatNet<TInt, TFlt> >  graph, const int &v)
{
  int size = graph->GetNodes();
  std::vector<float> distances (size,INFINITY);
  std::vector<int> parents (size,-1);
  std::deque<int> noVisitados;
  std::vector<int> visitados;
  for(int i=0; i<size; i++)
  {
    noVisitados.push_back(i+1);
  }
  distances[v-1] = 0;
  while(!noVisitados.empty())
  {
    //Ordenar los no visitados en base a su distancia
    std::sort(noVisitados.begin(), noVisitados.end(), sorter(distances));
    
    int u = noVisitados[0];//El primero de los no visitados es el de la distancia mas corta
    noVisitados.pop_front();//Sacar al mas corto de la cola
    visitados.push_back(u); //Meterlo en la lista de los que ya se visitaron
    int sourceNode = u; //Asignar este con el siguiente nodo de inicio
    
    TNodeEDatNet<TInt, TFlt>::TNodeI NI = graph->GetNI(sourceNode);
    
    //Iterar por cada arista que sale de el nodo
    for (int e = 0; e < NI.GetOutDeg(); e++)
    {
      int destNode = NI.GetOutNId(e);//Sacar el nodo destino
      TNodeEDatNet<TInt, TFlt>::TEdgeI EI = graph->GetEI(sourceNode,destNode);//Sacar la arista
      float edgeWeight = (float)EI.GetDat(); //Sacar el dato de la arista (peso)
      
      //Si la distancia es menor susituir, si no se deja igual
      if(distances[destNode-1] > distances[sourceNode-1] + edgeWeight)
      {
        distances[destNode-1] = distances[sourceNode-1] + edgeWeight;
        parents[destNode-1] = sourceNode;
      }
    }
  }
  int node = 1;
  
  //Impresión de el camino mas corto
  for (int i = 0 ; i< parents.size(); i++)
  {
    std::cout << parents[node-1] << " -> " << node << " distance:  " << distances[node-1] << std::endl;
    node++;
  }
}


//Función para imprimir un vector de ints
void printVector(std::vector<int> vector)
{
  printf("[ ");
  for (int i = 0; i < vector.size(); i++)
  {
    printf("%d ",vector[i]);
  }
  printf("] \n");
}

//Función para poder ordenar el vector de noVisitados en relación a su distancia
bool sortFunction(int a, int b, std::vector<float> distancias)
{
  return distancias[a-1] < distancias[b-1];
}

bool sortFunction2(std::pair<int, int> a, std::pair<int, int> b, std::vector<float> distancias)
{
  return distancias[a.first-1] < distancias [b.first-1];
}


//Función del algoritmo de prim
void prim(TPt<TNodeEDatNet<TInt, TFlt> >  graph, const int &v)
{
  int size = graph->GetNodes();
  int tam = size;
  int graphMatrix[tam][tam];
  int peso = 0;
  for (int i = 0; i<size; i++)
  {
    for (int j = 0; j<size; j++)
    {
      peso = graph->GetEDat(i+1, j+1);
      if (peso > 0)
      {
        graphMatrix[i][j] = peso;
      }
      else
      {
        graphMatrix[i][j] = INFINITY;
      }
    }
  }
  //Código para poder imprimir la matriz de el gráfo
  //  for (int i = 0; i<size; i++)
  //  {
  //    for (int j = 0; j<size; j++)
  //    {
  //      std::cout << graphMatrix[i][j] << " ";
  //    }
  //    std::cout << std::endl;
  //  }
  
  
  int selected[tam], i, j,ne;
  int min, x, y;
  for (i = 0; i<tam; i++)
  {
    selected[i] = false;
  }
  
  selected[0] = true;
  ne = 0;
  
  while (ne < tam-1)
  {
    min=INFINITY;
    
    for(i=0;i<tam;i++)
    {
      if(selected[i]==true)
      {
        for(j=0;j<tam;j++)
        {
          if(selected[j]==false)
          {
            
            if(min > graphMatrix[i][j])
            {
              min=graphMatrix[i][j];
              x=i;
              y=j;
            }
          }
        }
      }
    }
    selected[y]=true;
    
    //Imprimir padre y su hijo
    std::cout<<x+1<<" --> "<<y+1 << "\n";
    ne=ne+1;
  }
}

void kruskal(TPt<TNodeEDatNet<TInt, TFlt> > graph)
{
  const int N = graph->GetNodes();
  
  std::vector<std::pair<int, int>> connections;
  std::vector<std::pair<int, int>> tree;
  std::vector<float> distances;
  std::vector<int> visited;
  
  for (int i = 0; i < N; i++){
    for (int j = 0; j < N; j++){
      int peso = graph->GetEDat(i+1, j+1);
      if (peso != 0){
        connections.push_back(std::make_pair(i, j));
        distances.push_back(peso);
      }
    }
  }
  
  std::sort(connections.begin(), connections.end(), sorter2(distances));
  tree.push_back(connections[0]);
  visited.push_back(connections[0].first);
  visited.push_back(connections[0].second);
  int i = 1;
  while(i < connections.size() || tree.size() < N){
    bool firstFound = false;
    bool secondFound = false;
    
    for (int j = 0; j < visited.size(); j++){
      if (visited[i] == connections[i].first){
        firstFound = true;
      }
      if (visited[i] == connections[i].second){
        secondFound = true;
      }
    }
    
    if (!firstFound || !firstFound){
      tree.push_back(connections[i]);
      if (!firstFound){
        visited.push_back(connections[i].first);
      }
      if (!secondFound){
        visited.push_back(connections[i].second);
      }
    }
    
    i++;
  }
  
  for (int i = 0; i < tree.size(); i++){
    printf("parent[%d] = %d\n", tree[i].first, tree[i].second);
  }
  
}

void fw(TPt<TNodeEDatNet<TInt, TFlt> >  graph)
{
  std::cout << "Entering Floyd Warshall: " << std::endl;
  const int N = graph->GetNodes();
  int size = N;
  int distances[N][N];
  int peso = 0;
  for (int i = 0; i<size; i++)
  {
    for (int j = 0; j<size; j++)
    {
      peso = graph->GetEDat(i+1, j+1);
      if(i==j)
      {
        distances[i][j]=0;
      }
      else if (peso > 0)
      {
        distances[i][j] = peso;
      }
      else
      {
        distances[i][j] = 999999999;
      }
      std::cout << std::setw(9) << distances[i][j] << " ";
    }
    std::cout << "\n";
  }
  
  for (int k = 0; k < N; k++)
  {
    std::cout << "Distance matrix after iteration " << k + 1 << "\n";
    for (int i = 0; i < N; i++)
    {
      for (int j = 0; j < N; j++)
      {
        if (distances[i][j] > distances[i][k] + distances[k][j])
        {
          distances[i][j] = distances[i][k] + distances[k][j];
        }
        std::cout << std::setw(9) << distances[i][j] << " ";
      }
      std::cout << "\n";
    }
  }
  
}



void menu(TPt<TNodeEDatNet<TInt, TFlt> >  graph)
{
  int cont = 1;
  int opcion=0;
  int nodoOrigen;
  int nodoDestino;
  int v;
  while (opcion !=9)
  {
    std::cout << "\tBienvenido" << std::endl;
    std::cout << "Dame una opción" << std::endl;
    std::cout << std::endl;
    std::cout << "1. Añade un nodo" << std::endl;
    std::cout << "2. Añade una arista" << std::endl;
    std::cout << "3. Borra un nodo" << std::endl;
    std::cout << "4. Borra una arista" << std::endl;
    std::cout << "5. Dijkstra" << std::endl;
    std::cout << "6. Prim" << std::endl;
    std::cout << "7. BFS" << std::endl;
    std::cout << "8. DFS" << std::endl;
    std::cout << "9. Salir" << std::endl;
    std::cin >> opcion;
    std::cout << std::endl;
    switch (opcion)
    {
      case 1:
        graph->AddNode(cont);
        cont++;
        break;
      case 2:
        std::cout << "Dame el id del nodo origen" << std::endl;
        std::cin >> nodoOrigen;
        std::cout << std::endl;
        std::cout << "Dame el id del nodo destino" << std::endl;
        std::cin >> nodoDestino;
        std::cout << std::endl;
        graph->AddEdge(nodoOrigen, nodoDestino);
        break;
      case 3:
        std::cout << "Dame el id del nodo que quieres borrar" << std::endl;
        std::cin >> v;
        graph->DelNode(v);
        break;
      case 4:
        std::cout << "Dame el id del nodo origen de la arista que quieres borrar" << std::endl;
        std::cin >> nodoOrigen;
        std::cout << std::endl;
        std::cout << "Dame el id del nodo destino de la arista que quieres borrar" << std::endl;
        std::cin >> nodoDestino;
        std::cout << std::endl;
        graph->DelEdge(nodoOrigen, nodoDestino);
        break;
      case 5:
        std::cout << "Dame el id del nodo del que quieres encontrar el camino mas corto" << std::endl;
        std::cin >> v;
        dijkstra(graph, v);
        break;
      case 6:
        prim(graph, 1);
        break;
      case 7:
        break;
      case 8:
        break;
      case 9:
        opcion=9;
        break;
        
      default:
        break;
    }
  }
}












