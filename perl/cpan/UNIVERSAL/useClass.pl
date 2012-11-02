use warnings;
use strict;
use Class;

use feature 'say';


#     Is there a method called «some_method»?
#     If so, it returns a referenc to the sub:
say  "Class can some_method"     if     Class->can('some_method');

say  "Class is a UNIVERSAL"      if     Class->isa('UNIVERSAL');
say  "Class is not a Special"    unless Class->isa('Special');

say  "Class does UNIVERSAL"      if     Class->DOES('UNIVERSAL');
say  "Class does not Special"    unless Class->DOES('Special');

my    $obj = new Class;

say  "Version is: ", $obj->VERSION;
