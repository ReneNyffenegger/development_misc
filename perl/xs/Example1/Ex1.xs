#include "EXTERN.h"
#include "perl.h"
#include "XSUB.h"

#include "ppport.h"


MODULE = Ex1		PACKAGE = Ex1		

void
func()
  CODE:
    printf("Ex1::func is called!\n");
