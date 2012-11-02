#ifndef POINT_3D_H
#define POINT_3D_H

#include <cmath>

class point3d {

  public:

    point3d(double x_, double y_, double z_) : x(x_), y(y_), z(z_) {};

    double x;
    double y;
    double z;

    double length() {
      return std::sqrt(x*x + y*y + z*z);
    }

};

#endif
