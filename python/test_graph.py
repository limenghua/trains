import unittest
import graph

class TestGraphFunctions(unittest.TestCase):

    def setUp(self):
        self.graph = graph.Graph(5)

    def test_construct(self):
        self.assertEqual(self.graph.numEdge,0)
        self.assertEqual(self.graph.weight(0,2),self.graph.INFINITE)

    def test_vertexNum(self):
        self.assertEqual(self.graph.vertexNum,5)

    def test_setEdge(self):
        self.graph.setEdge(0,1,3)        
        self.assertEqual(self.graph.edgeNum(),1)
        self.assertEqual(self.graph.weight(0,1),3)

    def test_neighbors(self):
        self.graph.setEdge(0,1,3)
        self.graph.setEdge(0,3,2)
        self.graph.setEdge(0,4,1)

        self.assertEqual(self.graph.neighbors(0),[1,3,4])



if __name__ == '__main__':
    unittest.main()
