#include "EXTERN.h"
#include "perl.h"
#include "XSUB.h"

MODULE = Ex3		PACKAGE = Ex3

void 
in_out(int param)
CODE:
  param = param * 2;
OUTPUT:
  param
