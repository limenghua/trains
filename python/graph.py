# -*- coding:utf8
import string

class Graph:
    """
        使用邻接矩阵表示的带权有向图，martrix[v1][v2]表示从v1到v2的权值
        [0，INFINITE]，INFINITE=100000代表无穷大
    """
    INFINITE = 100000
    
    def __init__(self,vertexNum):
        self.vertexNum = vertexNum
        self.matrix = []
        for i in range(vertexNum):
            self.matrix.append([])
            for j in range(vertexNum):
                self.matrix[i].append(self.INFINITE)

        self.numEdge = 0

    def deleteAllEdge(self):
        for i in range(self.vertexNum):
            for j in range(self.vertexNum):
                self.matrix[i][j] = self.INFINITE

        self.numEdge = 0

    def createByString(self,str):
        """
            从一个字符串中构造图结构，节点使用字符A~Z表示，A映射为0
            str："AB5,BC4,CD8,DC8,DE6,AD5,CE2,EB3,AE7"
        """
        words = string.split(str,",")
        for elem in words:
            v1 = elem[0:1]
            v2 = elem[1:2]
            w = elem[2:]
            v1 = ord(v1)- ord("A")
            v2 = ord(v2)- ord("A")
            w = int(w)

            self.setEdge(v1,v2,w)
            
        

    def edgeNum(self):
        return self.numEdge

    def setEdge(self,v1,v2,w):
        if(self.matrix[v1][v2] == self.INFINITE):
            self.numEdge += 1
        self.matrix[v1][v2] = w

    def weight(self,v1,v2):
        return self.matrix[v1][v2]

    def neighbors(self,v):
        """
            返回指定节点的所有邻接点
        """
        return [p for p in range(self.vertexNum) if self.matrix[v][p] != self.INFINITE]
        

    def destanceByString(self,str):
        """
            由字符串确定一个路径，返回该路径的总长度
            str:"A-B-C",代表从A到B再到C的路径长度
            如果路径长度为无穷大，返回"NO SUCH ROUTE"
        """
        totalDistance = 0
        vertexs = string.split(str,"-")
        for i in range(1,len(vertexs)):
            v1 = ord(vertexs[i-1]) - ord("A")
            v2 = ord(vertexs[i]) - ord("A")
            dis = self.weight(v1,v2)
            if(dis == self.INFINITE):
                return "NO SUCH ROUTE"                

            totalDistance += dis

        return totalDistance

    def getShortestDistance(self,v1,v2):
        """
            获取从v1点到v2点的最短路径长度
        """
        flag     = [False] * self.vertexNum
        D = self.matrix[v1][:]

        v = 0
        minValue = self.INFINITE

        for i in range(self.vertexNum):
            minValue = self.INFINITE
            v = -1

            for j in range(self.vertexNum):
                if (not flag[j]) and D[j]<minValue:
                    v = j
                    minValue = D[j]

            if(v == -1):continue
            flag[v] = True

            for k in range(self.vertexNum):
                if D[k] > D[v]+self.weight(v,k):
                    D[k] = D[v]+self.weight(v,k)

        return D[v2]

    def numRouteLess3Stop(self,v1,v2,nStops = 0):
        """
            从v1点出发至v2点，经过节点数不超过3个的路径的总数量
        """
        count = 0

        if v1 == v2 and nStops != 0:count += 1
        if nStops >= 3:
            return count

        for v in self.neighbors(v1):
            count += self.numRouteLess3Stop(v,v2,nStops+1)

        return count
    
    def numRouteEqual4Stop(self,v1,v2,nStops = 0):
        """
            从v1点出发至v2点，经过节点数正好为4个的路径的总数量
        """
        count = 0

        if v1 == v2 and nStops == 4:count += 1
        if nStops >= 4:
            return count

        for v in self.neighbors(v1):
            count += self.numRouteEqual4Stop(v,v2,nStops+1)

        return count
    
    def numRouteLess30d(self,v1,v2,nDistance = 0):
        """
            从v1点出发至v2点，经过路径总长度不超过30的路径的总数量
        """
        count = 0

        if v1 == v2 and nDistance != 0 and nDistance<30:count += 1
        if nDistance >= 30:
            return count

        for v in self.neighbors(v1):
            count += self.numRouteLess30d(v,v2,nDistance+self.weight(v1,v))

        return count    



if __name__ == "__main__":
    fp = open("input.txt")
    line = fp.readline()
    graph = Graph(5)
    graph.createByString(line);
    print "Output #1:",graph.destanceByString("A-B-C")
    print "Output #2:",graph.destanceByString("A-D")
    print "Output #3:",graph.destanceByString("A-D-C")
    print "Output #4:",graph.destanceByString("A-E-B-C-D")
    print "Output #5:",graph.destanceByString("A-E-D")
    print "Output #6:",graph.numRouteLess3Stop(2,2)
    print "Output #7:",graph.numRouteEqual4Stop(0,2)
    print "Output #8:",graph.getShortestDistance(0,2)
    print "Output #9:",graph.getShortestDistance(1,1)    
    print "Output #10:",graph.numRouteLess30d(2,2)    
