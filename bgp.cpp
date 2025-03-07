//
// Created by Kave Salamatian on 20/04/2021.
//


#include <iostream>
#include <utility>
#include "curvatureHandler.h"
#include "GraphSpecial.h"

using namespace boost;
using namespace std;
using namespace code_machina;
using std::chrono::high_resolution_clock;
using std::chrono::duration_cast;
using std::chrono::duration;
using std::chrono::milliseconds;
using std::chrono::microseconds;




//typedef boost::adjacency_list <boost::vecS, boost::vecS, boost::undirectedS, Vertex_info_BGP, Edge_info_BGP, Graph_info > Graph_t;
//typedef boost::adjacency_list <boost::vecS, boost::vecS, boost::undirectedS, Vertex_info_road, Edge_info_road, Graph_info > Graph_t;
typedef unsigned int uint;

boost::dynamic_properties dp;

/*q
 * Read a graphml
 */
void readGraphMLFile (Graph_t& designG, std::string &fileName ) {

    ifstream inFile;

    boost::dynamic_properties dp;

    dp = gettingProperties<Graph_t,VertexType,EdgeType>(designG);

    cout << "Opening " << fileName << "--" << endl; 
    inFile.open(fileName, ifstream::in);
    try {
        boost::read_graphml(inFile, designG, dp, 0);
        cout << "Graph loaded \n"; 
    }
    catch (const std::exception &exc) {
        cout << "Error while loading the graph \n";
        cerr << exc.what();
        cout << " Type: " << typeid(exc).name() << "\n";
    }
    cout << "Num Vertices: " << num_vertices(designG) << endl;
    cout << "Num Edges: " << num_edges(designG) << endl;
    inFile.close();
}

struct CablePredicate {// both edge and vertex
    typedef typename graph_traits<Graph_t>::vertex_descriptor Vertex;
    typedef typename graph_traits<Graph_t>::edge_descriptor Edge;

    explicit CablePredicate(Graph_t *g, string cableName): g(g),cableName(cableName){};
    CablePredicate()= default;
    bool operator()(Edge e) const      {return false;}
    bool operator()(Vertex vd) const { return true; }
    Graph_t *g;
    string cableName;
};

using CableFiltered_Graph_t = boost::filtered_graph<Graph_t, CablePredicate, CablePredicate>;


int main(int argc, char **argv)  {
    Graph_t *g=new Graph_t, *gin=new Graph_t, *ginter, *g2=new Graph_t;
    string filename, path;
    string filter; //useful? 
    int iterationIndex=0;
    AlgoType algo;
    
    algo = MSMD; 
    string result_path = ".";
    string graph_path;

    double oldRescaling=1.0;
    int numIteration=20;

    if( argc > 2 ) {
        string command1(argv[1]);
        if (command1 == "-P") {
            result_path=string(argv[2]);
        }
        string command2(argv[3]);
        if (command2 =="-G")
            graph_path= string(argv[4]);
        string command3(argv[5]);
        if (command3 =="-NI")
            numIteration = stoi(argv[6]);
    }

    //string pfilename=path+"/"+filename;
    readGraphMLFile(*gin,graph_path );
    k_core2(*gin,*g, 2);
    //CablePredicate predicate(g,filter);
    //CableFiltered_Graph_t fg(*g, predicate, predicate);
    //copy_graph(fg,*g2);
    int negin=num_edges(*g), necable=num_edges(*g);
    cout<<negin<<","<<necable<<endl;


    
    ricci_flow(g, numIteration,iterationIndex,result_path,algo);

    return 0;

}


