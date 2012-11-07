#include <iostream>
#include "matrix.h"

int main() {

  matrix_4 m;

  m.translation(1, 2, 3);

  std::cout << m.elem[0][0] << " " << m.elem[1][0] << " " << m.elem[2][0] << " " << m.elem[3][0] << std::endl;
  std::cout << m.elem[0][1] << " " << m.elem[1][1] << " " << m.elem[2][1] << " " << m.elem[3][1] << std::endl;
  std::cout << m.elem[0][2] << " " << m.elem[1][2] << " " << m.elem[2][2] << " " << m.elem[3][2] << std::endl;
  std::cout << m.elem[0][3] << " " << m.elem[1][3] << " " << m.elem[2][3] << " " << m.elem[3][3] << std::endl;

  std::cout << std::endl;

  vector_4 v(5, 10, 15, 1);

  std::cout << v.elem[0] << std::endl;
  std::cout << v.elem[1] << std::endl;
  std::cout << v.elem[2] << std::endl;
  std::cout << v.elem[3] << std::endl;

  std::cout << std::endl;

  vector_4 e = m * v;

  std::cout << e.elem[0] << std::endl;
  std::cout << e.elem[1] << std::endl;
  std::cout << e.elem[2] << std::endl;
  std::cout << e.elem[3] << std::endl;
}
