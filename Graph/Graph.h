//
// Created by vitalii on 11.04.15.
//

#ifndef GRAPH_GRAPH_H
#define GRAPH_GRAPH_H


#include <functional>
#include <vector>
#include <iostream>
#include <fstream>


template<typename NodePayload>
class Graph {
public:
    // struct representing a node
    struct NodeHandle {
        std::vector<int> children ;
        NodeHandle() = default;
        NodeHandle(NodePayload value, int number) : value(value), number(number) { }
        NodePayload value;
        int number;
    } ;
    // struct representing an edge
    struct EdgeHandle{
        EdgeHandle() = default;
        EdgeHandle(NodeHandle firstNode, NodeHandle secondNode) : firstNode(firstNode), secondNode(secondNode) { }
        NodeHandle firstNode;
        NodeHandle secondNode;
    };
    typedef std::function<void(NodeHandle const &)> NodeVisitor;
    typedef std::function<void(EdgeHandle const &)> EdgeVisitor;
    void showMatrix();

public:
    Graph() {
        nodes.reserve(1000);
    };
    ~Graph() = default;
    /**
     * loads graph from file
     * @param filename - name of the file from where lgraph should be loaded
     */
    void loadFromFile(std::string const & filename);
    /**
     * saves graph to the file
     * @param filename - where graph should be saved to
     */
    void saveToFile(std::string const & filename);
    //adds node to graph with value
    // @param value
    NodeHandle & addNode(NodePayload value = NULL);
    //adds edge between nodes
    void addEdge(NodeHandle & a, NodeHandle & b) {
        a.children.push_back(b.number);
        b.children.push_back(a.number);
    }

    /**
     * invokes function for each node in the graph
     * @param visitor - reference to function that has to be applied
     */
    void forEachNode(std::function<void(NodeHandle const &)> const & visitor) const;
    // returns number of nodes in the graph
    size_t getNodesCount() const;
    /**
     * invokes function for each edge given node is part of
     * @param visitor - function that should be invoked
     * @param origin - from what node edges have to be taken
     */
    void forEachEdge(NodeHandle const & source, EdgeVisitor const & visitor) const;
    //moves node in given edge
    NodeHandle move(NodeHandle const & origin, EdgeHandle const & edge);
    NodePayload & operator[](NodeHandle  & node);
    /**
     * implements non-recursive depth-first search in graph and applies given function for each node
     * that's been met.
     * @param startNode - node dfs has to be started from
     * @param visitor - function that has to be invoked
     * @param endNode - function will end when finds this node
     */
    void dfs(NodeHandle const & startNode, NodeHandle const & endNode, NodeVisitor const & discoverNode);
private:
    std::vector<NodeHandle> nodes;
    size_t nodeCounts = 0;
};

template <typename NodePayload>
// loading graph from file named @filename
void Graph<NodePayload>::loadFromFile(std::string const &filename) {
    std::ifstream ifs(filename, std::ios_base::binary);
    unsigned long vectorSize;
    ifs >>  vectorSize;
    nodes.clear();
    for (int i = 0; i < vectorSize; i++) {
        Graph<NodePayload>::NodeHandle a;
        unsigned long childrenSize;
        ifs >> childrenSize;
        for (int j = 0; j < childrenSize; j++) {
            int child;
            ifs >> child;
            a.children.push_back(child);
        }
        NodePayload value;
        int number;
        ifs >> number >> value;
        a.number = number;
        a.value = value;
        nodes.push_back(a);
    }
    ifs.close();
}

template <typename NodePayload>
void Graph<NodePayload>::saveToFile(std::string const &filename) {
    std::ofstream ofs(filename, std::ios_base::binary);
    ofs << nodes.size() << " ";
    for (int i = 0; i < nodes.size(); i++) {
        ofs << nodes[i].children.size() << " ";
        for (int j = 0; j < nodes[i].children.size(); j++)
            ofs << nodes[i].children[j] << " ";
        ofs << nodes[i].number << " ";
        ofs << nodes[i].value << " ";
    }
    ofs.close();
}

template <typename NodePayload>
typename Graph<NodePayload>::NodeHandle & Graph<NodePayload>::addNode(NodePayload value)  {
    NodeHandle a(value, (int) nodes.size());
    nodes.push_back(a);
    nodeCounts++;
    return nodes[nodes.size() - 1];
}

template <typename NodePayload>
void Graph<NodePayload>::forEachNode(NodeVisitor const &visitor) const {
    for (auto & it : nodes) {
        visitor(it);
    }
}

template <typename NodePayload>
size_t Graph<NodePayload>::getNodesCount() const {
    return nodeCounts;
}

template <typename NodePayload>
void Graph<NodePayload>::forEachEdge(NodeHandle const &source, EdgeVisitor const &visitor) const {
    for (int it : source.children) {
        EdgeHandle edge;
        edge.firstNode  = source;
        edge.secondNode = nodes[it];
        visitor(edge);
    }
}

template <typename NodePayload>
typename Graph<NodePayload>::NodeHandle Graph<NodePayload>::move(NodeHandle const &origin, EdgeHandle const &edge) {
    std::swap(edge.firstNode.value, edge.secondNode.value);
    std::swap(edge.firstNode.number, edge.secondNode.number);
    return edge.firstNode.value == origin.value ? edge.firstNode : edge.secondNode;
}

template <typename NodePayload>
NodePayload &Graph<NodePayload>::operator[](NodeHandle & node) {
    return node.value;
}

template <typename NodePayload>
void Graph<NodePayload>::dfs(NodeHandle const &startNode, NodeHandle const &endNode,
                NodeVisitor const &discoverNode) {
    std::vector<int> nodes_to_visit;
    nodes_to_visit.push_back(startNode.number);
    char * used = new char[nodes.size()];
    while (nodes_to_visit.size() > 0) {
        int currentNode = nodes_to_visit.back();
        used[currentNode] = true;
        nodes_to_visit.pop_back();
        for (int & it : nodes[currentNode].children)
            if (used[it] != true)
                nodes_to_visit.push_back(it);
        discoverNode(nodes[currentNode]);
        if (nodes[currentNode].number == endNode.number)
            break;
    }
    delete[] used;
    return;
}

template<typename NodePayload>
void Graph<NodePayload>::showMatrix() {
    for (auto & it : nodes) {
        for (auto & child : it.children) {
            std::cout << it.number << " " << child << "\n";
        }
    }
}


#endif //GRAPH_GRAPH_H

