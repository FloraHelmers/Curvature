#include <iostream>
#include "curvatureHandler.h"
#include "GraphSpecial.h"
#include <boost/graph/connected_components.hpp>

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


/*
 * Read a graphml
 */
void readGraphMLFile (Graph_t& designG, std::string &fileName ) {

    ifstream inFile;

    boost::dynamic_properties dp;

    dp = gettingProperties<Graph_t,Vertex_info_road,Edge_info_road>(designG);
    inFile.open(fileName, ifstream::in);
    try {
        boost::read_graphml(inFile, designG, dp);
    }
    catch (const std::exception &exc) {
        cerr << exc.what();
        cout << " Type: " << typeid(exc).name() << "\n";
    }
//    for(auto ve = boost::edges(designG);ve.first!=ve.second;++ve.first){
//        designG[*(ve.first)].distance=designG[*(ve.first)];
//    }
    cout << "Num Vertices: " << num_vertices(designG) << endl;
    cout << "Num Edges: " << num_edges(designG) << endl;
    inFile.close();
}


int main(int argc, char **argv)  {
    Graph_t *g=new Graph_t, *gin=new Graph_t, *ginter;
    string filename, path;
    int iterationIndex=0;
    AlgoType algo;
    if( argc > 2 ) {
        string command1(argv[1]);
        if (command1 == "-P") {
            path=string(argv[2]);
        }
        string command2(argv[3]);
        if (command2 =="-F")
            filename= string(argv[4]);
        string command3(argv[5]);
        if (command3 =="-A")
            algo=MSMD;
        algo=MSMD;
        if (string(argv[6])=="SSSD")
            algo=SSSD;
        if (string(argv[6])=="SSMD")
            algo=SSMD;
        if (string(argv[6])=="MSMD")
            algo=MSMD;
    }

    string pfilename=path+"/"+filename;
    readGraphMLFile(*gin,pfilename );
    int numIteration=500;
    vector<Graph_t *> vect;
//    preProcess(gin, vect);
    k_core2(*gin,*g, 2);

    double oldRescaling=1.0;
    ricci_flow(g, numIteration, iterationIndex,path, algo);
    return 0;
}