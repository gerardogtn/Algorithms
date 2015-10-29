#include <iostream>
#include <fstream>
#include "stdafx.h"

void graphMl(PNGraph Graph);
void gexf(PNGraph Graph);
void gdf(PNGraph Graph);
void graphson(PNGraph Graph);

int main(int argc, char* argv[]) {
  typedef PNGraph PGraph;

  printf("Creating graph:\n");
  PGraph Graph = TSnap::LoadEdgeList<PNGraph>("wiki_vote.txt",0,1);

  graphMl(Graph);
  gexf(Graph);
  gdf(Graph);
  graphson(Graph);

  // for (TNGraph::TNodeI NI = Graph->BegNI(); NI < Graph->EndNI(); NI++){
  //   printf("%d %d %d\n", NI.GetId(), NI.GetOutDeg(), NI.GetInDeg());
  // }

  IAssert(Graph->IsOk());
  return 0;
}

void graphMl(PNGraph Graph){
  std::ofstream graphml;
  graphml.open("graph.graphml");
  graphml << "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n";
  graphml << "<graphml xmlns=\"http://graphml.graphdrawing.org/xmlns\"\n";
  graphml << "    xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\"\n";
  graphml << "    xsi:schemaLocation=\"http://graphml.graphdrawing.org/xmlns\n";
  graphml << "     http://graphml.graphdrawing.org/xmlns/1.1/graphml.xsd\">\n";

  graphml << "  <graph id=\"G\" edgedefault=\"directed\">\n";

  int i = 0;
  for (TNGraph::TNodeI NI = Graph->BegNI(); NI < Graph->EndNI(); NI++){
    graphml << "    <node id=\"" << NI.GetId() << "\"/>\n";
  }

  graphml << "\n";

  i = 1;
  for (TNGraph::TEdgeI EI = Graph->BegEI(); EI < Graph->EndEI(); EI++){
    graphml << "    <edge id=\"e"
            << i++
            << "\" directed=\"true"
            << "\" source=\""
            << EI.GetSrcNId()
            << "\" target=\""
            << EI.GetDstNId()
            << "\"/>\n";
  }

  graphml << "  </graph>\n";
  graphml << "</graphml>\n";
  graphml.close();
}


void gexf(PNGraph Graph){
  std::ofstream graph;
  int i = 1;
  graph.open("graph.gexf");

  graph << "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n";
  graph << "<gexf xmlns=\"http://www.gexf.net/1.2draft\" version=\"1.2\">\n";

  graph << "  <graph mode=\"static\" defaultedgetype=\"directed\">\n";

  graph << "    <nodes>\n";
  for (TNGraph::TNodeI NI = Graph->BegNI(); NI < Graph->EndNI(); NI++){
    graph << "      <node id=\"" << NI.GetId() << "\"/>\n";
  }
  graph << "    </nodes>\n";

  graph << "    <edges>\n";
  for (TNGraph::TEdgeI EI = Graph->BegEI(); EI < Graph->EndEI(); EI++){
    graph << "      <edge id=\"e"
            << i++
            << "\" directed=\"true"
            << "\" source=\""
            << EI.GetSrcNId()
            << "\" target=\""
            << EI.GetDstNId()
            << "\"/>\n";
  }
  graph << "    </edges>\n";
  graph << "  </graph>\n";
  graph << "</gexf>\n";

  graph.close();
}

void gdf(PNGraph Graph){
  std::ofstream graph;
  graph.open("graph.gdf");

  graph << "nodedef>name VARCHAR\n";
  for (TNGraph::TNodeI NI = Graph->BegNI(); NI < Graph->EndNI(); NI++){
    graph << NI.GetId() << ",\n";
  }

  graph << "edgedef>node1 VARCHAR,node2 VARCHAR\n";
  for (TNGraph::TEdgeI EI = Graph->BegEI(); EI < Graph->EndEI(); EI++){
    graph << EI.GetSrcNId() << "," << EI.GetDstNId() << "\n";
  }

  graph.close();
}

void graphson(PNGraph Graph){
  std::ofstream graph;
  const std::string TAB = "    ";
  graph.open("graph.json");

  graph << "{\n";
  graph << TAB << "\"graph\": {\n";
  graph << TAB << TAB << "\"mode\": \"NORMAL\", \n";
  graph << TAB << TAB << "\"vertices\": [\n";

  int i = 0;
  for (TNGraph::TNodeI NI = Graph->BegNI(); NI < Graph->EndNI(); NI++){
    i++;
    graph << TAB << TAB << TAB << "{\n";
    graph << TAB << TAB << TAB << TAB << "\"_id\": \"" << NI.GetId() << "\",\n";
    graph << TAB << TAB << TAB << TAB << "\"_type\": \"vertex\"\n";

    if (i == Graph->GetNodes()){
      graph << TAB << TAB << TAB << "}\n";
    } else {
      graph << TAB << TAB << TAB << "},\n";
    }
  }


  graph << TAB << TAB << "],\n";
  graph << TAB << TAB << "\"edges\": [\n";

  i = 0;
  printf("Edges: %d", Graph->GetEdges());
  for (TNGraph::TEdgeI EI = Graph->BegEI(); EI < Graph->EndEI(); EI++){
    graph << TAB << TAB << TAB << "{\n";
    graph << TAB << TAB << TAB << TAB << "\"_id\": \"" << i++ << "\",\n";
    graph << TAB << TAB << TAB << TAB << "\"_type\": \"edge\"\n";
    graph << TAB << TAB << TAB << TAB << "\"_outV\": \"" << EI.GetSrcNId() << "\"\n";
    graph << TAB << TAB << TAB << TAB << "\"_inV\": \""<< EI.GetDstNId() << "\"\n";

    if (i == Graph->GetEdges()){
      graph << TAB << TAB << TAB << "}\n";
    } else {
      graph << TAB << TAB << TAB << "},\n";
    }
  }
  graph << TAB << TAB << "]\n";
  graph << TAB << "}\n";
  graph << "}\n";

  graph.close();

}
