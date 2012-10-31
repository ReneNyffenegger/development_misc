// under {perl}/lib/CORE
#include "EXTERN.h"
#include "perl.h"
#include "XSUB.h"

// h2xs -A -n Ex2 added the following line
//#include "ppport.h"

MODULE = Ex2		PACKAGE = Ex2		


void
print_defines()
  CODE:
    printf("Ex2: %s\nVERSION        : %s\nXS_VERSION     : %s\n", EX2_DEFINE, VERSION, XS_VERSION);

double 
add(double d1, double d2, double d3)
  CODE:
    RETVAL = d1 + d2 + d3;
  OUTPUT:
    RETVAL
