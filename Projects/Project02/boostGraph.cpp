#include <tuple>
#include <algorithm>
#include <iterator>
#include <iostream>

#include "dfs_time_visitor.cpp"
#include "bfs_time_visitor.cpp"

#include <boost/config.hpp>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/breadth_first_search.hpp>
#include <boost/graph/depth_first_search.hpp>
#include <boost/graph/dijkstra_shortest_paths.hpp>
#include <boost/graph/exterior_property.hpp>
#include <boost/graph/floyd_warshall_shortest.hpp>
#include <boost/pending/indirect_cmp.hpp>
#include <boost/graph/kruskal_min_spanning_tree.hpp>
#include <boost/graph/prim_minimum_spanning_tree.hpp>
#include <boost/property_map/property_map.hpp>

using namespace boost;

typedef int t_weight;
typedef property <edge_weight_t, t_weight> Weight;
typedef adjacency_list<vecS, vecS, directedS, no_property, Weight> graph_t;
typedef property_map<graph_t, edge_weight_t>::type WeightMap;

typedef boost::exterior_vertex_property<graph_t, t_weight> DistanceProperty;
typedef DistanceProperty::matrix_type DistanceMatrix;
typedef DistanceProperty::matrix_map_type DistanceMatrixMap;

typedef graph_traits<graph_t>::vertices_size_type size_type;
typedef graph_traits<graph_t>::edge_descriptor Edge;
typedef graph_traits<graph_t>::vertex_descriptor vertex_descriptor;

typedef size_type * Iiter;


void printMenu();
void handleOption(const int option, graph_t &g);
void addEdge(graph_t &g);
void addEdge(int a, int b, int w, bool zero, graph_t &g);
void addVertex(graph_t &g);
void removeEdge(graph_t &g);
void removeEdge(int a, int b, bool zero, graph_t &g);
void removeVertex(graph_t &g);
void dfs(graph_t &g);
void bfs(graph_t &g);
void prim(graph_t &g);
void kruskal(graph_t &g);
void djikstra(graph_t &g);
void fw(graph_t & g);
void printgraph(graph_t &g);

int main()
{
  std::cout << "******************************* \n";
  std::cout << "Demo of the boost graph library \n";
  std::cout << "******************************* \n\n";


  std::cout << "Graph Demo: \n" << std::endl;
  graph_t demo(15);

  addEdge( 1,  3,  8, true, demo);
  addEdge( 1,  4,  8, true, demo);
  addEdge( 2,  5,  7, true, demo);
  addEdge( 3,  2,  7, true, demo);
  addEdge( 3, 10,  4, true, demo);
  addEdge( 3,  5,  8, true, demo);
  addEdge( 4,  7,  4, true, demo);
  addEdge( 4,  8,  2, true, demo);
  addEdge( 5,  6,  9, true, demo);
  addEdge( 6, 13,  4, true, demo);
  addEdge( 7,  4,  6, true, demo);
  addEdge( 8,  9,  3, true, demo);
  addEdge( 9, 12,  4, true, demo);
  addEdge( 9, 10,  2, true, demo);
  addEdge(10,  3, 10, true, demo);
  addEdge(10,  6,  6, true, demo);
  addEdge(11, 12,  6, true, demo);
  addEdge(12, 14,  9, true, demo);
  addEdge(12,  9,  2, true, demo);
  addEdge(12, 11,  8, true, demo);
  addEdge(13, 14,  6, true, demo);
  addEdge(14, 13,  2, true, demo);

  dfs(demo);
  bfs(demo);
  prim(demo);
  kruskal(demo);
  djikstra(demo);
  fw(demo);
  printgraph(demo);

  std::cout << "Interactive Demo: \n" << std::endl;
  graph_t g;
  int option;

  do {
    printMenu();
    std::cin >> option;
    handleOption(option, g);
  } while(option > 0 && option < 12);

  std::cout << "Goodbye." << std::endl;
}

void printMenu()
{
  std::cout << "***************************" << std::endl;
  std::cout << "             MENU          " << std::endl;
  std::cout << "***************************" << std::endl;
  std::cout << "1. Insert vertex" << std::endl;
  std::cout << "2. Insert edge" << std::endl;
  std::cout << "3. Remove vertex" << std::endl;
  std::cout << "4. Remove edge" << std::endl;
  std::cout << "5. DFS" << std::endl;
  std::cout << "6. BFS" << std::endl;
  std::cout << "7. Prim's algorithm" << std::endl;
  std::cout << "8. Kruskal's algorithm" << std::endl;
  std::cout << "9. Djikstra's algorithm" << std::endl;
  std::cout << "10. Floyd-Warshall algorithm" << std::endl;
  std::cout << "11. Print graph." << std::endl;
  std::cout << "Any other number to exit. " << std::endl;
  std::cout << "\n" << std::endl;
}

void handleOption(const int option, graph_t &g)
{
  switch (option) {
    case 1:
      addVertex(g);
      break;
    case 2:
      addEdge(g);
      break;
    case 3:
      removeVertex(g);
      break;
    case 4:
      removeEdge(g);
      break;
    case 5:
      dfs(g);
      break;
    case 6:
      bfs(g);
      break;
    case 7:
      prim(g);
      break;
    case 8:
      kruskal(g);
      break;
    case 9:
      djikstra(g);
      break;
    case 10:
      fw(g);
      break;
    case 11:
      printgraph(g);
      break;
    default:
      break;
  }
}

void addEdge(graph_t &g)
{
  int firstEdge, secondEdge, _weight;

  std::cout << "Insert the first edge index: " << std::endl;
  std::cin >> firstEdge;

  std::cout << "Insert the second edge index:" << std::endl;
  std::cin >> secondEdge;

  std::cout << "Insert the weight of the path" << std::endl;
  std::cin >> _weight;

  addEdge(firstEdge, secondEdge, _weight, false, g);

}

void addEdge(int a, int b, int w, bool zero, graph_t &g)
{
  if (!zero)
    add_edge(a, b, Weight(w), g);
  else
    add_edge(a - 1, b - 1, Weight(w), g);
}

void addVertex(graph_t &g)
{
  boost::adjacency_list<>::vertex_descriptor v = boost::add_vertex(g);
  std::cout << "A new vertex with index: " << v << " was created" << std::endl;
}

void removeEdge(graph_t &g)
{
  int origin, destination;
  std::cout << "Insert the origin vertex: " << std::endl;
  std::cin >> origin;
  std::cout << "Insert the destination vertex:" << std::endl;
  std::cin >> destination;
  std::cout << "Removing edge" << std::endl;
  removeEdge(origin, destination, false, g);
}

void removeEdge(int a, int b, bool zero, graph_t &g)
{
  if (!zero)
    remove_edge(a, b, g);
  else
    remove_edge(a - 1, b - 1, g);
}

void removeVertex(graph_t &g)
{
  std::cout << "What vertex should we remove?" << std::endl;
  int N;
  std::cin >> N;
  remove_vertex(N, g);
}

void dfs(graph_t &g)
{
  std::cout << "Depth first search: " << std::endl;
  int N = boost::num_vertices(g);
  std::vector <size_type> dtime(num_vertices(g));
  std::vector <size_type> ftime(num_vertices(g));
  size_type t = 0;
  dfs_time_visitor<size_type *> vis(&dtime[0], &ftime[0], t);

  boost::depth_first_search(g, visitor(vis));

  std::vector<size_type> discover_order(N);
  integer_range<size_type> r(0, N);
  std::copy(r.begin(), r.end(), discover_order.begin());
  std::sort(discover_order.begin(), discover_order.end(),
  indirect_cmp<Iiter, std::less <size_type>>(&dtime[0]));
  std::cout << "Order of discovery: ";
  int i;
  for (i = 0; i < N; ++i){
      std::cout << discover_order[i] << " ";
  }
  std::cout << "\n";
}

void bfs(graph_t &g)
{
  std::cout << "Breadth first search: " << std::endl;
  int s;
  std::cout << "Insert the vertex to start the breadth first search: ";
  std::cin >> s;

  int N = boost::num_vertices(g);
  std::vector <size_type> dtime(num_vertices(g));
  size_type time = 0;
  bfs_time_visitor <size_type *>vis(&dtime[0], time);
  breadth_first_search(g, vertex(s, g), visitor(vis));

  std::vector<graph_traits<graph_t>::vertices_size_type > discover_order(N);
  integer_range < int >range(0, N);
  std::copy(range.begin(), range.end(), discover_order.begin());
  std::sort(discover_order.begin(), discover_order.end(),
            indirect_cmp <Iiter, std::less <size_type>>(&dtime[0]));

  std::cout << "Order of discovery: ";
  for (int i = 0; i < N; ++i){
    std::cout << discover_order[i] << " ";
  }
  std::cout << "\n";
}

void prim(graph_t &g)
{
  property_map<graph_t, edge_weight_t>::type weightmap = get(edge_weight, g);
  std::vector <graph_traits<graph_t>::vertex_descriptor> p(num_vertices(g));
  prim_minimum_spanning_tree(g, &p[0]);

  for (std::size_t i = 0; i != p.size(); ++i)
  {
    if (p[i] != i)
      std::cout << "parent[" << i << "] = " << p[i] << std::endl;
    else
      std::cout << "parent[" << i << "] = no parent" << std::endl;
  }
}

void kruskal(graph_t &g)
{
  std::vector<Edge> spanning_tree;
  kruskal_minimum_spanning_tree(g, std::back_inserter(spanning_tree));

  for (std::vector<Edge>::iterator ei = spanning_tree.begin();
       ei != spanning_tree.end(); ++ei) {
         std::cout << source(*ei, g) << " <--> " << target(*ei, g) << std::endl;
  }
}

void djikstra(graph_t &g)
{
  int start;
  std::cout << "Insert the index of the node were djikstra should start: " << std::endl;
  std::cin >> start;

  property_map<graph_t, edge_weight_t>::type weightmap = get(edge_weight, g);
  std::vector<vertex_descriptor> p(num_vertices(g));
  std::vector<int> d(num_vertices(g));
  vertex_descriptor s = vertex(start, g);

  dijkstra_shortest_paths(g, s,
                          predecessor_map(boost::make_iterator_property_map(p.begin(), get(boost::vertex_index, g))).
                          distance_map(boost::make_iterator_property_map(d.begin(), get(boost::vertex_index, g))));

  std::cout << "distances and parents:" << std::endl;
  graph_traits <graph_t>::vertex_iterator vi, vend;
  for (boost::tie(vi, vend) = vertices(g); vi != vend; ++vi) {
    std::cout << "distance(" << *vi << ") = " << d[*vi] << ", ";
    std::cout << "parent(" << *vi << ") = " << p[*vi] << std::
      endl;
  }
  std::cout << std::endl;
}

void fw(graph_t & g)
{
  WeightMap weight_pmap = boost::get(boost::edge_weight, g);

  // set the distance matrix to receive the floyd warshall output
  DistanceMatrix distances(num_vertices(g));
  DistanceMatrixMap dm(distances, g);

  bool valid = floyd_warshall_all_pairs_shortest_paths(g, dm,
                                            boost::weight_map(weight_pmap));

  // check if there no negative cycles
  if (!valid) {
    std::cerr << "Error - Negative cycle in matrix" << std::endl;
    return;
  }

  // print upper triangular part of the distance matrix
  std::cout << "Distance matrix: " << std::endl;
  for (std::size_t i = 0; i < num_vertices(g); ++i) {
    for (std::size_t j = i; j < num_vertices(g); ++j) {
      std::cout << "From vertex " << i+1 << " to " << j+1 << " : ";
      if(distances[i][j] == std::numeric_limits<t_weight>::max())
        std::cout << "inf" << std::endl;
      else
        std::cout << distances[i][j] << std::endl;
    }
    std::cout << std::endl;
  }
}


void printgraph(graph_t &g)
{


  std::cout << "First representation: " << std::endl;
  auto p = edges(g);
  for (auto it = p.first; it != p.second; ++it){
    std::cout << *it << std::endl;
    //std::cout << "weight[" << *it << "] = " << get(weight, p.first) << std::endl;
    //std::cout << "weight[" << *it << "] = " << get(weight, p.second) << std::endl;
  }

  std::cout << "\nSecond representation:" << std::endl;

  graph_t::vertex_iterator vertexIt, vertexEnd;
  graph_t::adjacency_iterator neighbourIt, neighbourEnd;
  boost::tie(vertexIt, vertexEnd) = boost::vertices(g);
  for (; vertexIt != vertexEnd; ++vertexIt)
  {
    std::cout << *vertexIt << " is connected with ";
    boost::tie(neighbourIt, neighbourEnd) = boost::adjacent_vertices(*vertexIt, g);
    for (; neighbourIt != neighbourEnd; ++neighbourIt){
      std::cout << *neighbourIt << " ";
    }
    std::cout << "\n";
  }
  std::cout << "\n";
}
