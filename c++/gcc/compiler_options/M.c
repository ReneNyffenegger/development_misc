//
//   gcc -M  -MF M.d  -IM  M.c
//       
//       Writes dependency information including
//       system header files into a file named «M.d»
//   -----------------------------------------------
//
//   gcc -MM -MF MM.d -IM  M.c
//
//       Writes dependency information without
//       system header files into a file named «MM.d»
//   -----------------------------------------------
//

#include <stdio.h>
#include "M_a.h"
#include "M_b.h"
#include "M_c.h"

int main() {

}
