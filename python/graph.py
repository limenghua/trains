class Graph:
    INFINITE = 100000
    
    def __init__(self,vertexNum):
        self.vertexNum = vertexNum
        self.matrix = []
        for i in range(vertexNum):
            self.matrix.append([])
            for j in range(vertexNum):
                self.matrix[i].append(self.INFINITE)

        self.numEdge = 0

    def edgeNum(self):
        return self.numEdge

    def setEdge(self,v1,v2,w):
        if(self.matrix[v1][v2] == self.INFINITE):
            self.numEdge += 1 

        self.matrix[v1][v2] = w

    def weight(self,v1,v2):
        return self.matrix[v1][v2]

    def neighbors(self,v):
        return [p for p in range(self.vertexNum) if self.matrix[v][p] != self.INFINITE]
        
