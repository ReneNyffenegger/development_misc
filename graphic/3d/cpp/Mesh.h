#include <vector>

class Mesh {

  public:

    struct Edge {
      int node_from;
      int node_to;
      Edge(int from, int to) {
        node_from = from;
        node_to   = to;
      }
    };

    std::vector<point3d> nodes;
    std::vector<Edge>    edges;

};


Mesh CreateIcosahedronMesh(double len = 1) {
//
  static const double X = 0.525731112119133696;
  static const double Z = 0.850650808352039932;


  Mesh mesh;


  mesh.nodes.push_back(point3d(-X  * len, 0.0 * len,  Z  * len));
  mesh.nodes.push_back(point3d( X  * len, 0.0 * len,  Z  * len));
  mesh.nodes.push_back(point3d(-X  * len, 0.0 * len, -Z  * len));
  mesh.nodes.push_back(point3d( X  * len, 0.0 * len, -Z  * len));
  mesh.nodes.push_back(point3d(0.0 * len,  Z  * len,  X  * len));
  mesh.nodes.push_back(point3d(0.0 * len,  Z  * len, -X  * len));
  mesh.nodes.push_back(point3d(0.0 * len, -Z  * len,  X  * len));
  mesh.nodes.push_back(point3d(0.0 * len, -Z  * len, -X  * len));
  mesh.nodes.push_back(point3d( Z  * len,  X  * len, 0.0 * len));
  mesh.nodes.push_back(point3d(-Z  * len,  X  * len, 0.0 * len));
  mesh.nodes.push_back(point3d( Z  * len, -X  * len, 0.0 * len));
  mesh.nodes.push_back(point3d(-Z  * len, -X  * len, 0.0 * len));

//Trianlge 1
  mesh.edges.push_back(Mesh::Edge( 1, 4));
  mesh.edges.push_back(Mesh::Edge( 4, 0));
  mesh.edges.push_back(Mesh::Edge( 0, 1));

//Triangle 2
  mesh.edges.push_back(Mesh::Edge( 4, 9));
  mesh.edges.push_back(Mesh::Edge( 9, 0));
//mesh.edges.push_back(Mesh::Edge( 0, 4));

//Triangle 3
  mesh.edges.push_back(Mesh::Edge( 4, 5));
  mesh.edges.push_back(Mesh::Edge( 5, 9));
//mesh.edges.push_back(Mesh::Edge( 9, 4));

//Triangle 4
  mesh.edges.push_back(Mesh::Edge( 8, 5));
//mesh.edges.push_back(Mesh::Edge( 5, 4));
  mesh.edges.push_back(Mesh::Edge( 4, 8));

//Triangle 5
  mesh.edges.push_back(Mesh::Edge( 1, 8));
//mesh.edges.push_back(Mesh::Edge( 8, 4));
//mesh.edges.push_back(Mesh::Edge( 4, 1));

//Triangle 6
  mesh.edges.push_back(Mesh::Edge( 1,10));
  mesh.edges.push_back(Mesh::Edge(10, 8));
//mesh.edges.push_back(Mesh::Edge( 8, 1));

//Triangle 7
  mesh.edges.push_back(Mesh::Edge(10, 3));
  mesh.edges.push_back(Mesh::Edge( 3, 8));
//mesh.edges.push_back(Mesh::Edge( 8,10));

//Triangle 8
//mesh.edges.push_back(Mesh::Edge( 8, 3));
  mesh.edges.push_back(Mesh::Edge( 3, 5));
//mesh.edges.push_back(Mesh::Edge( 5, 8));

//Triangle 9
  mesh.edges.push_back(Mesh::Edge( 3, 2));
  mesh.edges.push_back(Mesh::Edge( 2, 5));
//mesh.edges.push_back(Mesh::Edge( 5, 3));

//Triangle 10
  mesh.edges.push_back(Mesh::Edge( 3, 7));
  mesh.edges.push_back(Mesh::Edge( 7, 2));
//mesh.edges.push_back(Mesh::Edge( 2, 3));

//Triangle 11
//mesh.edges.push_back(Mesh::Edge( 3,10));
  mesh.edges.push_back(Mesh::Edge(10, 7));
//mesh.edges.push_back(Mesh::Edge( 7, 3));

//Triangle 12
  mesh.edges.push_back(Mesh::Edge(10, 6));
  mesh.edges.push_back(Mesh::Edge( 6, 7));
//mesh.edges.push_back(Mesh::Edge( 7,10));

//Triangle 13
  mesh.edges.push_back(Mesh::Edge( 6,11));
  mesh.edges.push_back(Mesh::Edge(11, 7));
//mesh.edges.push_back(Mesh::Edge( 7, 6));

//Triangle 14
  mesh.edges.push_back(Mesh::Edge( 6, 0));
  mesh.edges.push_back(Mesh::Edge( 0,11));
//mesh.edges.push_back(Mesh::Edge(11, 6));

//Triangle 15
  mesh.edges.push_back(Mesh::Edge( 6, 1));
//mesh.edges.push_back(Mesh::Edge( 1, 0));
//mesh.edges.push_back(Mesh::Edge( 0, 6));

//Triangle 16
//mesh.edges.push_back(Mesh::Edge(10, 1));
//mesh.edges.push_back(Mesh::Edge( 1, 6));
//mesh.edges.push_back(Mesh::Edge( 6,10));

//Triangle 17
//mesh.edges.push_back(Mesh::Edge(11, 0));
//mesh.edges.push_back(Mesh::Edge( 0, 9));
  mesh.edges.push_back(Mesh::Edge( 9,11));

//Triangle 18
  mesh.edges.push_back(Mesh::Edge( 2,11));
//mesh.edges.push_back(Mesh::Edge(11, 9));
  mesh.edges.push_back(Mesh::Edge( 9, 2));

//Triangle 19
//mesh.edges.push_back(Mesh::Edge( 5, 2));
//mesh.edges.push_back(Mesh::Edge( 2, 9));
//mesh.edges.push_back(Mesh::Edge( 9, 5));

//Triangle 20
//mesh.edges.push_back(Mesh::Edge(11, 2));
//mesh.edges.push_back(Mesh::Edge( 2, 7));
//mesh.edges.push_back(Mesh::Edge( 7,11));

// done. Check for dupliacate edges:
// done. --------------------------:
// done.  for (std::vector<Mesh::Edge>::reverse_iterator rit = mesh.edges.rbegin(); rit < mesh.edges.rend(); ++rit) {
// done.  for (std::vector<Mesh::Edge>::reverse_iterator sit = rit+1              ; sit < mesh.edges.rend(); ++sit) {
// done.
// done.    if ((rit->node_from == sit->node_from &&
// done.         rit->node_to   == sit->node_to  ) ||
// done.        (rit->node_to   == sit->node_from &&
// done.         rit->node_from == sit->node_to)) {
// done.
// done.      char buffer[50];
// done.
// done.      sprintf(buffer, "from:%d to:%d", sit->node_from , sit->node_to);
// done.
// done.      MessageBox(0, buffer, 0, 0);
// done.
// done.    }
// done.
// done.  }}


  return mesh;

};


// TODO: is parameter Viewer really necessary?
void DrawMesh(HDC dc, matrix_4 const& matrix, Mesh const& mesh, Viewer const& viewer, double mult) {
  
  for (std::vector<Mesh::Edge>::const_iterator it = mesh.edges.begin(); it < mesh.edges.end(); ++it) {

    DrawLine(dc, matrix, viewer, 
      mesh.nodes[it->node_from] /* * mult */, // TODO...
      mesh.nodes[it->node_to  ] /* * mult */
    );

  }

}
