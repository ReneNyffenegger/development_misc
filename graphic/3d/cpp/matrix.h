// Make (M_PI) available:
#define _USE_MATH_DEFINES

#include <cmath>
#include "point3d.h"

class vector_4 {
public:

  // http://knol.google.com/k/matrices-for-3d-applications-translation-rotation#
  // ----------------------------------------------------------------------------
  //     A homogeneous coordinate is a 3D coordinate with an extra fourth
  //     coordinate w added to it. For example if we have a 3D coordinate [2,3,4] ,
  //     the homogeneous coordinate is formed by [2,3,4,1].
  //

  friend class matrix_4;

  vector_4() {
//  elem[0] = 0;
//  elem[1] = 0;
//  elem[2] = 0;
//  elem[3] = 0;
  }

  double elem[4];

  public:

    vector_4(double m0, double m1, double m2, double m3) {
      elem[0] = m0;
      elem[1] = m1;
      elem[2] = m2;
      elem[3] = m3;
    }

    vector_4(point3d const& point) {
      elem[0] = point.x;
      elem[1] = point.y;
      elem[2] = point.z;
      elem[3] = 1;
    }

//  vector_4(const vector_4& other) {
//    elem[0] = other.elem[0];
//    elem[1] = other.elem[1];
//    elem[2] = other.elem[2];
//    elem[3] = other.elem[3];
//  }

   point3d make_point_3d() {

   // if (elem[3] != 1) {
   //    MessageBox(0, "elem[3] != 1", "fail", 0);
   // }

       return point3d(elem[0] / elem[3],
                      elem[1] / elem[3],
                      elem[2] / elem[3]);
   }

};

class matrix_4 {

// TODO: wegnehmen
public:
  
   double elem[4][4];

   double x;

   public: 
     
     void init(
               double m_00,        double m_10,        double m_20,        double m_30,
               double m_01,        double m_11,        double m_21,        double m_31,
               double m_02,        double m_12,        double m_22,        double m_32,
               double m_03,        double m_13,        double m_23,        double m_33) 
       {
         elem[0][0] = m_00; elem [1][0] = m_10; elem [2][0] = m_20; elem [3][0] = m_30;
         elem[0][1] = m_01; elem [1][1] = m_11; elem [2][1] = m_21; elem [3][1] = m_31;
         elem[0][2] = m_02; elem [1][2] = m_12; elem [2][2] = m_22; elem [3][2] = m_32;
         elem[0][3] = m_03; elem [1][3] = m_13; elem [2][3] = m_23; elem [3][3] = m_33;
       }

   vector_4 operator* (vector_4 const& vect) const {

     vector_4 ret;

     for (int elem_v=0; elem_v<4; elem_v++) {
       ret.elem[elem_v] = 0;

//     for (int elem_y=0; elem_y<4; elem_y++) {
//          ret.elem[elem_v] += vect.elem[elem_v] * elem[elem_v][elem_y];
//     }

       for (int elem_xy=0; elem_xy<4; elem_xy++) {
            ret.elem[elem_v] += vect.elem[elem_xy] * elem[elem_xy][elem_v];
//          std::cout << "elem_v: " << elem_v << ", elem_xy: " << elem_xy << " : " << ret.elem[elem_v] << 
//               " ... " << vect.elem[elem_v] << "*" << elem[elem_xy][elem_v] <<
//          std::endl;
       }
     }

     return ret;
   }
    
   matrix_4 operator* (matrix_4 const& other) {
     matrix_4 ret;


     for (int elem_x=0; elem_x<4; elem_x++){
     for (int elem_y=0; elem_y<4; elem_y++){
          ret.elem[elem_x][elem_y] = 0;

          for (int k=0; k<4; k++) {
             ret.elem[elem_x][elem_y] += this->elem[k][elem_y] * other.elem[elem_x][k];
//           ret.elem[elem_x][elem_y] += (other.elem[k][elem_y]) * (this->elem[elem_x][k]);
          }
     }}
     return ret;
   }

   point3d  operator* (point3d const& point) const {
     
      // Apply the matrix-transformation onto the point

      vector_4 v4 (point);

      vector_4 translated_4 = *this * v4;

      return translated_4.make_point_3d();

   }

   void translation(double x, double y, double z) {

     init (  1 , 0 , 0 , x ,
             0 , 1 , 0 , y ,
             0 , 0 , 1 , z ,
             0 , 0 , 0 , 1 
          );

   }

   void rotation_x(double angle) {
   // http://www.cprogramming.com/tutorial/3d/rotationMatrices.html

      double ca = std::cos(angle);
      double sa = std::sin(angle);
        

      init ( 1 ,   0 ,   0 ,  0,  // Left handed.
             0 ,  ca , -sa ,  0,
             0 ,  sa ,  ca ,  0,
             0 ,   0 ,   0 ,  1
           );

   }

   void rotation_y(double angle) {
   // http://www.cprogramming.com/tutorial/3d/rotationMatrices.html
      double ca = std::cos(angle);
      double sa = std::sin(angle);
        
      init ( ca ,   0 ,  sa ,  0,  // Left handed.
              0 ,   1 ,   0 ,  0,
            -sa ,   0 ,  ca ,  0,
              0 ,   0 ,   0 ,  1
           );

   }

   void rotation_z(double angle) {
   // http://www.cprogramming.com/tutorial/3d/rotationMatrices.html
      double ca = std::cos(angle);
      double sa = std::sin(angle);
        
      init ( ca , -sa ,   0 ,  0,  // Left handed.
             sa ,  ca ,   0 ,  0,
              0 ,   0 ,   1 ,  0,
              0 ,   0 ,   0 ,  1
           );

   }

   void rotation(double x, double y, double z, double angle ) { // Rotation about an arbitrary Axis
   // http://www.cprogramming.com/tutorial/3d/rotation.html

      double c = std::cos(angle);
      double s = std::sin(angle);
      double t = 1.0-c;

      double n = std::sqrt(x*x + y*y + z*z);

      x=x/n;
      y=y/n;
      z=z/n;
     
      init (  t*x*x +   c  ,  t*x*y - s*z  ,  t*x*z + s*y  ,  0   ,  // Left handed.
              t*x*y + s*z  ,  t*y*y +   c  ,  t*y*z - s*x  ,  0   ,
              t*x*z - s*y  ,  t*y*z + s*x  ,  t*z*z +   c  ,  0   ,
                    0      ,        0      ,        0      ,  1   
           );
      
   }

   void scale(double s) {

        init (s , 0 , 0 , 0 ,
              0 , s , 0 , 0 ,
              0 , 0 , s , 0 ,
              0 , 0 , 0 , 1 );

   }

};
