#include <iostream>
#include <fstream>
#include <string>
#include "Graph.h"

#include <sstream>

using namespace std;

static const string FILE_INPUT = "input.txt";
static const string FILE_OUTPUT = "output.txt";

int main(int argc, char* argv[])
{
	std::string fileNameInput = FILE_INPUT;
	std::string fileNameOutput = FILE_OUTPUT;
	if(argc>1){
		fileNameInput = argv[1];
	}
	if(argc>2){
		fileNameOutput = argv[2];
	}

	std::string input;
	ofstream fout(fileNameOutput);
	ifstream fin(fileNameInput);
	if(!fin){
		cout<<"打开文件:"<<fileNameInput<<"失败"<<endl;
	}
	fin>>input;


	std::string routesOutput;
	Graph5 graph;
	graph.createByString(input);

	//1.The distance of route A-B-C
	cout<<"Output #1: "<<graph.outputDistance("ABC")<<endl;
	fout<<"Output #1: "<<graph.outputDistance("ABC")<<endl;

	//2.The distance of route A-D
	cout<<"Output #2: "<<graph.outputDistance("AD")<<endl;
	fout<<"Output #2: "<<graph.outputDistance("AD")<<endl;

	//3.The distance of route A-D-C
	cout<<"Output #3: "<<graph.outputDistance("ADC")<<endl;	
	fout<<"Output #3: "<<graph.outputDistance("ADC")<<endl;	

	//4.The distance of route A-E-B-C-D
	cout<<"Output #4: "<<graph.outputDistance("AEBCD")<<endl;
	fout<<"Output #4: "<<graph.outputDistance("AEBCD")<<endl;

	//5.The distance of route A-E-D
	cout<<"Output #5: "<<graph.outputDistance("AED")<<endl;
	fout<<"Output #5: "<<graph.outputDistance("AED")<<endl;

	//6.The number of trips of C to C maximum of 3 stops
	cout<<"Output #6: "
		<<graph.numRouteLess3Stop(2,2,routesOutput)
		<<"("<<routesOutput<<")"
		<<endl;
	fout<<"Output #6: "
		<<graph.numRouteLess3Stop(2,2,routesOutput)
		<<endl;


	//7.The number of trips of C to C maximum of 3 stops
	cout<<"Output #7: "
		<<graph.numRouteEqual4Stop(0,2,routesOutput)
		<<"("<<routesOutput<<")"		
		<<endl;
	fout<<"Output #7: "
		<<graph.numRouteEqual4Stop(0,2,routesOutput)
		<<endl;

	//8.The lenth of shortest route from A to C
	cout<<"Output #8: "<<graph.getShortestDistance(0,2)<<endl;
	fout<<"Output #8: "<<graph.getShortestDistance(0,2)<<endl;

	//9.The lenth of shortest route from B to B
	cout<<"Output #9: "<<graph.getShortestDistance(1,1)<<endl;
	fout<<"Output #9: "<<graph.getShortestDistance(1,1)<<endl;

	//10.The number of trips of C to C maximum of 3 stops
	cout<<"Output #10: "
		<<graph.numRouteLess30d(2,2,routesOutput)
		<<"("<<routesOutput<<")"		
		<<endl;		
	fout<<"Output #10: "
		<<graph.numRouteLess30d(2,2,routesOutput)
		<<endl;

	return 0;
}