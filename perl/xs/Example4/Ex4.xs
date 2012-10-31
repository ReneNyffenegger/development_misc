#include "add.h"

#include "EXTERN.h"
#include "perl.h"
#include "XSUB.h"

MODULE = Ex4		PACKAGE = Ex4

double
add(double a, double b)
  CODE:
    RETVAL = add(a, b);
  OUTPUT:
    RETVAL
