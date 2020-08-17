#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <cmath>
#include <set>
#include <functional>
#include <climits>
#include <ctime>
#include <stdlib.h>
#include <cstdlib>
#include <cstdint>
#include <cstring>
#include <chrono>

#include "Graph.h"
#include "Util.h"

using namespace std;
using namespace Gorder;

const int INPUTNUM=1;

int main(int argc, char* argv[]){
	ios::sync_with_stdio(false);
	int i;
	int W=5;
	clock_t start, end;
	string filename;

	if(argc==1){
		cout << "please provide parameter" << endl;
		quit();
	}

	i=1;
	while(i<argc){
		if(strcmp("-w", argv[i])==0){
			i++;
			W=atoi(argv[i]);
			if(W<=0){
				cout << "w should be larger than 0" << endl;
				quit();
			}
			i++;
		}
        else if(strcmp("-e", argv[i])==0) {
            Graph::terminate_after_map = true;
            i++;
        }
        else if(strcmp("-d", argv[i])==0) {
            i++;
            Graph::indegree_gorder=atoi(argv[i]);
            cout << Graph::indegree_gorder << endl;
            i++;
        }
		else{
			filename=argv[i++];
		}
	}

	srand(time(0));

	Graph g;
	string name;
	name=extractFilename(filename.c_str());
	g.setFilename(name);

	start=clock();
	g.readGraph(filename);
    vector<int> rcm_order;
	g.Transform(rcm_order);
	cout << name << " readGraph is complete." << endl;
	end=clock();
	cout << "Time Cost: " << (double)(end-start)/CLOCKS_PER_SEC << endl;

	start=clock();
	vector<int> order;
	g.GorderGreedy(order, W);
	end=clock();
	cout << "ReOrdered Time Cost: " << (double)(end-start)/CLOCKS_PER_SEC << endl;
	cout << "Begin Output the Reordered Graph" << endl;
#if 1
    g.PrintTwoDirectionMap(rcm_order, order);
#else
	g.PrintReOrderedGraph(order);
#endif
	cout << endl;
}

