#include "gtest/gtest.h"
#include "../Train/Graph.h"

TEST(Graph, vertexNum)
{
	Graph5 graph;
	ASSERT_EQ(graph.vertexNum(),5);
}

TEST(Graph,setEdge)
{
	Graph5 graph;
	graph.setEdge(0,1,3);
	graph.setEdge(0,2,4);
	graph.setEdge(0,3,5);

	ASSERT_EQ(graph.edgeNum(),3);
	ASSERT_EQ(graph.weight(0,1),3);
	ASSERT_EQ(graph.weight(0,2),4);
	ASSERT_EQ(graph.weight(0,3),5);
}

TEST(Graph,createByString)
{
	Graph5 graph;
	graph.createByString(std::string("AB5,BC4,CD8,DC8,DE6,AD5,CE2,EB3,AE7"));
	ASSERT_EQ(graph.weight(0,1),5);
	ASSERT_EQ(graph.weight(1,2),4);
	ASSERT_EQ(graph.weight(2,3),8);
	ASSERT_EQ(graph.weight(3,2),8);
	ASSERT_EQ(graph.weight(3,4),6);
	ASSERT_EQ(graph.weight(0,3),5);
	ASSERT_EQ(graph.weight(2,4),2);
	ASSERT_EQ(graph.weight(4,1),3);
	ASSERT_EQ(graph.weight(0,4),7);
}

TEST(Graph,getShortestDistance)
{
	Graph5 graph;
	graph.createByString(std::string("AB5,BC4,CD8,DC8,DE6,AD5,CE2,EB3,AE7"));
	ASSERT_EQ(graph.getShortestDistance(0,1),5);
	ASSERT_EQ(graph.getShortestDistance(0,2),9);
	ASSERT_EQ(graph.getShortestDistance(0,3),5);
}

TEST(Graph,numRouteLess3Stop)
{
	std::string str;
	Graph5 graph;
	graph.createByString(std::string("AB5,BC4,CD8,DC8,DE6,AD5,CE2,EB3,AE7"));

	ASSERT_EQ(graph.numRouteLess3Stop(2,2,str),2)<<"("<<str<<")";
}

TEST(Graph,numRouteEqual4Stop)
{
	std::string str;
	Graph5 graph;
	graph.createByString(std::string("AB5,BC4,CD8,DC8,DE6,AD5,CE2,EB3,AE7"));

	ASSERT_EQ(graph.numRouteEqual4Stop(0,2,str),3)<<"("<<str<<")";
}

TEST(Graph,numRouteLess30d)
{
	std::string str;
	Graph5 graph;
	graph.createByString(std::string("AB5,BC4,CD8,DC8,DE6,AD5,CE2,EB3,AE7"));

	ASSERT_EQ(graph.numRouteLess30d(2,2,str),7)<<"("<<str<<")";
}