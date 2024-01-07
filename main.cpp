#include "DynamicArray.h"
#include <fstream>

#define SCALE 10
#define GRAPHVIZ_CMD "dot -Tpng g.gv -o file.png"

class NodeInGraph{
public:
    double x, y;
    int index;

    NodeInGraph() {}
    NodeInGraph(double x, double y, int index) : x(x), y(y), index(index) {}
};

class EdgeInTheGraph{
public:
    int start;
    int end;
    double cost;

    EdgeInTheGraph() {}
    EdgeInTheGraph(int start, int end, double cost) : start(start), end(end), cost(cost) {}

    bool operator>(const EdgeInTheGraph temp) const {
        return cost > temp.cost;
    }

    bool operator<(const EdgeInTheGraph temp) const {
        return cost < temp.cost;
    }

    bool operator==(const EdgeInTheGraph temp) const {
        return cost == temp.cost;
    }
};

class UnionFind{
public:
    int* arrayParent;
    int* arrayRank;

    UnionFind(int n){
        arrayParent = new int[n];
        arrayRank = new int[n];

        for (int i = 0; i < n; i++) {
            arrayParent[i] = i;
            arrayRank[i] = 0;
        }
    }

    int find(int i) {
        if (arrayParent[i] == i){
            return i;
        }
        return find(arrayParent[i]);
    }

    void connect(int index1, int index2) {
        int s1 = find(index1);
        int s2 = find(index2);

        if (s1 != s2) {
            if (arrayRank[s1] < arrayRank[s2]) {
                arrayParent[s1] = s2;
            }
            else if (arrayRank[s1] > arrayRank[s2]) {
                arrayParent[s2] = s1;
            }
            else {
                arrayParent[s2] = s1;
                arrayRank[s1] += 1;
            }
        }
    }
};

class Graph{
public:
    DynamicArray<NodeInGraph>* nodes;
    DynamicArray<EdgeInTheGraph>* edges;

    Graph() {
        nodes = new DynamicArray<NodeInGraph>();
        edges = new DynamicArray<EdgeInTheGraph>();
    }

    ~Graph() {
        delete nodes;
        delete edges;
    }

    void addNode(double x, double y, int index){
        nodes->add(NodeInGraph(x, y, index));
    }
    void addEdge(int start, int end, double cost){
        edges->add(EdgeInTheGraph(start, end, cost));
    }

    void kruskal(){
        edges->bubleSort();
        int count = nodes->size;
        UnionFind finder(count);

        DynamicArray<EdgeInTheGraph> mst;

        for(const auto& temp : *edges){
            if(finder.find(temp.start) != finder.find(temp.end)){
                mst.add(temp);
                finder.connect(temp.start, temp.end);
            }
        }

        for(const auto& temp: mst){
            cout<<"Krawedzi "<<temp.start<<"-"<<temp.end<<" | "<<"z kosztem: "<<temp.cost<<endl;
        }
    }
};

Graph* readFile(){
    Graph* graph = new Graph();
    ifstream in("g1.txt");

    long nodeCount;

    if (in.is_open()) {
        double x, y;
        in >> nodeCount;

        for(long i = 0; i < nodeCount; i++){
            in >> x >> y;
            graph->addNode(x, y, i);
        }

        long edgeCount;
        in >> edgeCount;

        for(long i = 0; i < edgeCount; i++){
            int start, end;
            double cost;
            in >> start >> end >> cost;
            graph->addEdge(start, end, cost);
        }
    }
    in.close();
    return graph;
}

int main() {
    Graph* graph = readFile();
    clock_t t1 = clock();
    graph->kruskal();
    clock_t t2 = clock();
    double time = static_cast<double>(t2 - t1) / CLOCKS_PER_SEC;
    cout << "Time to kruskal algorithm: " << time << " seconds" << endl;
    //saveGraph(graph);
    return 0;
}
