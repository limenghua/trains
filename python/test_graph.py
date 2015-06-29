import unittest
import graph

class TestGraphFunctions(unittest.TestCase):

    def setUp(self):
        self.graph = graph.Graph(5)

    def test_construct(self):
        self.assertEqual(self.graph.numEdge,0)
        self.assertEqual(self.graph.weight(0,2),self.graph.INFINITE)

    def test_createByString(self):
        self.graph.createByString("AB5,BC4,CD8,DC8,DE6,AD5,CE2,EB3,AE7")
        self.assertEqual(self.graph.edgeNum(),9)
        self.assertEqual(self.graph.weight(0,1),5)
        self.assertEqual(self.graph.weight(1,2),4)
        self.assertEqual(self.graph.weight(2,3),8)
        self.assertEqual(self.graph.weight(3,2),8)
        self.assertEqual(self.graph.weight(3,4),6)
        self.assertEqual(self.graph.weight(0,3),5)
        self.assertEqual(self.graph.weight(2,4),2)
        self.assertEqual(self.graph.weight(4,1),3)        
        self.assertEqual(self.graph.weight(0,4),7)

        self.graph.deleteAllEdge()
        
    def test_vertexNum(self):
        self.assertEqual(self.graph.vertexNum,5)

    def test_setEdge(self):
        self.graph.setEdge(0,1,3)        
        self.assertEqual(self.graph.edgeNum(),1)
        self.assertEqual(self.graph.weight(0,1),3)
        self.graph.deleteAllEdge()

    def test_neighbors(self):
        self.graph.createByString("AB5,BC4,CD8,DC8,DE6,AD5,CE2,EB3,AE7");

        self.assertEqual(self.graph.neighbors(0),[1,3,4])
        self.assertEqual(self.graph.neighbors(1),[2])
        self.assertEqual(self.graph.neighbors(2),[3,4])
        self.assertEqual(self.graph.neighbors(3),[2,4])
        self.assertEqual(self.graph.neighbors(4),[1])
        
        self.graph.deleteAllEdge()

    def test_destanceByString(self):
        self.graph.createByString("AB5,BC4,CD8,DC8,DE6,AD5,CE2,EB3,AE7");

        self.assertEqual(self.graph.destanceByString("A-B-C"),9)
        self.assertEqual(self.graph.destanceByString("A-D"),5)
        self.assertEqual(self.graph.destanceByString("A-D-C"),13)
        self.assertEqual(self.graph.destanceByString("A-E-B-C-D"),22)
        self.assertEqual(self.graph.destanceByString("A-E-D"),"NO SUCH ROUTE")
        
        self.graph.deleteAllEdge()

    def test_getShortestDistance(self):
        self.graph.createByString("AB5,BC4,CD8,DC8,DE6,AD5,CE2,EB3,AE7");

        self.assertEqual(self.graph.getShortestDistance(0,2),9)
        self.assertEqual(self.graph.getShortestDistance(1,1),9)

        self.graph.deleteAllEdge()

    def test_numRoute(self):
        self.graph.createByString("AB5,BC4,CD8,DC8,DE6,AD5,CE2,EB3,AE7");

        self.assertEqual(self.graph.numRouteLess3Stop(2,2),2)
        self.assertEqual(self.graph.numRouteEqual4Stop(0,2),3)
        self.assertEqual(self.graph.numRouteLess30d(2,2),7)
        
        self.graph.deleteAllEdge()        

if __name__ == '__main__':
    unittest.main()
