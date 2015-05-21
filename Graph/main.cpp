#include <iostream>
#include "Graph.h"

using namespace std;

Graph<int>::NodeVisitor nodeVisitor = [] (const Graph<int>::NodeHandle& node) -> void {
    cout << node.value << " ";
};

void showNodes(Graph<int> const & graph) {
    graph.forEachNode(nodeVisitor);
}
void showEdges(Graph<int> const & graph) {
    graph.forEachNode([&](const Graph<int>::NodeHandle& node) -> void {
        graph.forEachEdge(node, [&](Graph<int>::EdgeHandle const &edge) -> void {
            cout << "edge : " << edge.firstNode.number << " " << edge.secondNode.number << "\n";
        });
    });
}

int main() {
    Graph<int> graph;
    auto & a = graph.addNode(5);
    auto & b = graph.addNode(4);
    auto & c = graph.addNode(255);
    auto & d = graph.addNode(-1);
    auto & new_node = graph.addNode(1234);
    a.value  = 15;
    b.value  = 25;
    graph[a] = 17;
    graph[b] = 155;
    graph.addEdge(a, b);
    graph.addEdge(a, c);
    graph.addEdge(c, new_node);
    showNodes(graph);
    cout << endl;
    showEdges(graph);
    graph.dfs(a, d, nodeVisitor);

    return 0;
}