#ifndef __GRAPH_H
#define __GRAPH_H

#include <vector>
#include <sstream>
#include <iostream>

template <int N>
class GraphBase
{
public:
	static const int N_VERTEX = N;
	static const int INFINITE = 100000; //�ǳ����Ȩֵ�����������
public:
	GraphBase()
	{
		numVertex = N_VERTEX;
		for(int i=0;i<N_VERTEX;i++){
			mark[i] = 0;
			for(int j=0;j<N_VERTEX;j++){
				matrix[i][j] = INFINITE;
			}
		}
		numEdge = 0;
	}

	int vertexNum()
	{
		return numVertex;
	}
	
	int edgeNum()
	{
		return numEdge;
	}

	int firstNghbr(int v)
	{
		for(int i=0;i<numVertex;i++){
			if(matrix[v][i] != INFINITE){
				return i;
			}
		}
		return numVertex;
	}

	int nextNghbr(int v1,int v2)
	{
		for(int i=v2+1;i<numVertex;i++){
			if(matrix[v1][i] != INFINITE){
				return i;
			}
		}
		return numVertex;
	}

	void setEdge(int v1,int v2,int wgt)
	{
		if(matrix[v1][v2] == INFINITE){
			numEdge ++;
		}
		matrix[v1][v2] = wgt;
	}

	void delEdge(int v1,int v2)
	{
		if(matrix[v1][v2] != INFINITE){
			numEdge--;
		}
		matrix[v1][v2] = INFINITE;
	}

	void delAllEdge()
	{
		for(int i=0;i<numVertex;i++){
			for(int j=0;j<numVertex;j++){
				delEdge(i,j);
			}
		}
	}

	int weight(int v1,int v2)
	{
		return matrix[v1][v2];
	}

	int getMark(int v)
	{
		return mark[v];
	}

	void setMark(int v,int val)
	{
		mark[v] = val;
	}
	void clearMark()
	{
		for(int i=0;i<numVertex;i++){
			mark[i] = 0;
		}
	}

protected:
	int numVertex;
	int	numEdge;
	int matrix[N_VERTEX][N_VERTEX];
	int mark[N_VERTEX];	//����״̬
};



class Graph5:public GraphBase<5>
{
public:
	//���ַ�����������ͼ��str:"AB5,BC4,CD8,DC8,DE6,AD5,CE2,EB3,AE7"
	//����ɹ�����true
	bool createByString(std::string & str)
	{
		delAllEdge();
		//�������еĶ���ȫ���滻Ϊ�ո�
		for(auto it = str.begin();it!= str.end();it++){
			if(*it == ',')
				*it = ' ';
		}

		std::istringstream lineIn(str);
		std::string edgeStr;
		while(lineIn>>edgeStr)
		{
			std::istringstream edgeIn(edgeStr);
			char beginCode,endCode;
			int weight;
			edgeIn>>beginCode>>endCode>>weight;
			setEdge(beginCode-'A',endCode-'A',weight);
		}

		return true;
	}

	//���ַ������·�����ȣ�·�����������"NO SUCH ROUTE"
	//routeStr: "ABC","AC","ABED",ex.
	std::string outputDistance(std::string routeStr){

		int dis = distanceOfRoute(routeStr);
		std::ostringstream strOut;
		if(dis != INFINITE){
			strOut<<dis;
		}else{
			strOut<<"NO SUCH ROUTE";
		}

		return strOut.str();
	}

	//Dijkstra�㷨Ӧ�ã������·������
	int getShortestDistance(int start,int dest)
	{
		int D[N_VERTEX];		//�洢���õ�Դ���е�������еĹ�����С����
		bool flag[N_VERTEX];	//�ҵ����·���ĵ㣬��־Ϊtrue
		int v;
		int shortest = INFINITE;

		for(int i=0;i<N_VERTEX;i++)
		{
			flag[i] = false;
			D[i] = weight(start,i);
		}

		for(int i=0;i<numVertex;i++){
			shortest = INFINITE;
			v = -1;
			//��ʣ������ҵ�һ�����·���ĵ�
			for(int j=0;j<numVertex;j++){
				if(!flag[j] && D[j]<shortest){
					v = j;
					shortest = D[j];
				}
			}
			if(v == -1){
				continue;
			}
			flag[v] = true;
			//��������ʣ���
			for(int k=0;k<numVertex;k++){
				if(D[k]>D[v]+weight(v,k)){
					D[k] = D[v]+weight(v,k);
				}
			}

		}

		return D[dest];
	}

	//��start�㵽dest��·�����������پ���3���ڵ�
	int numRouteLess3Stop(int start,int dest,std::string & routesOutput)
	{
		routesOutput.clear();
		std::string routeStr;
		return numRouteLess3Stop(start,dest,0,routeStr,routesOutput);

	}

	//��start�㵽dest��·�����������þ���4���ڵ�
	int numRouteEqual4Stop(int start,int dest,std::string &routesOutput)
	{
		routesOutput.clear();
		std::string routeStr;
		return numRouteEqual4Stop(start,dest,0,routeStr,routesOutput);
	}
	//��start�㵽dest��·��������·���ܳ��Ȳ�����30
	int numRouteLess30d(int start,int dest,std::string &routesOutput)
	{
		routesOutput.clear();
		std::string routeStr;
		return numRouteLess30d(start,dest,0,routeStr,routesOutput);
	}
private:
	//routeStr: "ABC","AC","ABED",ex.
	int distanceOfRoute(std::string & routeStr)
	{
		int totalDistance = 0;
		if(routeStr.size()<2)
			return INFINITE;

		auto it1 = routeStr.begin();
		auto it2 = it1;
		it2++;
		while(it2 != routeStr.end()){
			int dis = weight(*it1-'A',*it2 - 'A');
			if(dis == INFINITE){
				return INFINITE;
			}
			totalDistance += dis;
			it1++;
			it2++;
		}
		return totalDistance;
	}

	int numRouteLess3Stop(int start,int dest,int nStops,std::string & routeStr,std::string &routesOutput)
	{
		int count = 0;
		routeStr.push_back((char)('A'+start));

		if(start == dest && nStops!=0){
			routesOutput = routesOutput + "," + routeStr;
			count++;
		}
		if(nStops>=3){
			routeStr.pop_back();
			return count;
		}
		for(int v = firstNghbr(start);v<numVertex;v=nextNghbr(start,v)){
			count += numRouteLess3Stop(v,dest,nStops+1,routeStr,routesOutput);
		}
		routeStr.pop_back();
		return count;
	}

	int numRouteEqual4Stop(int start,int dest,int nStops,std::string & routeStr,std::string &routesOutput)
	{
		int count = 0;
		routeStr.push_back((char)('A'+start));

		if(start == dest && nStops==4){
			routesOutput = routesOutput + "," + routeStr;
			count++;
		}
		if(nStops>=4){
			routeStr.pop_back();
			return count;
		}
		for(int v = firstNghbr(start);v<numVertex;v=nextNghbr(start,v)){
			count += numRouteEqual4Stop(v,dest,nStops+1,routeStr,routesOutput);
		}
		routeStr.pop_back();
		return count;
	}

	int numRouteLess30d(int start,int dest,int nDistance,std::string & routeStr,std::string & routesOutput){
		int count = 0;
		routeStr.push_back((char)('A'+start));

		if(start == dest && nDistance<30 && nDistance != 0){
			routesOutput = routesOutput + "," + routeStr;
			count++;
		}
		if(nDistance>=30){
			routeStr.pop_back();
			return count;
		}
		for(int v = firstNghbr(start);v<numVertex;v=nextNghbr(start,v)){
			int dis = weight(start,v);
			count += numRouteLess30d(v,dest,nDistance+dis,routeStr,routesOutput);
		}
		routeStr.pop_back();
		return count;
	}

	void display()
	{
		std::cout.width(4);
		std::cout<<' ';
		for(int i=0;i<numVertex;i++){
			std::cout.width(4);
			std::cout<<(char)('A'+ i);
		}
		std::cout<<std::endl;
		for(int i=0;i<numVertex;i++){
			std::cout.width(4);
			std::cout<<(char)('A'+ i);
			for(int j=0;j<numVertex;j++){
				std::cout.width(4); 
				if(matrix[i][j] == INFINITE){
					std::cout<<"--";
				}
				else{
					std::cout<<matrix[i][j];
				}
			}
			std::cout<<std::endl;
		}

	}

};


#endif //__GRAPH_H