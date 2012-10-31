package Ex2;

use 5.010001;
use strict;
use warnings;

require Exporter;
require DynaLoader; # TODO: see what happens if DynaLoader is omitted

our @ISA = qw(Exporter DynaLoader); # TODO: see what happens if DynaLoader is omitted

# Items to export into callers namespace by default. Note: do not export
# names by default without a very good reason. Use EXPORT_OK instead.
# Do not simply export all your public functions/methods/constants.

# This allows declaration	use Ex2 ':all';
# If you do not need this, moving things directly into @EXPORT or @EXPORT_OK
# will save memory.
our %EXPORT_TAGS = ( 'all' => [ qw(
	
) ] );

our @EXPORT_OK = ( @{ $EXPORT_TAGS{'all'} } );

our @EXPORT = qw(
	
);

our $VERSION = '0.01';

require XSLoader;
XSLoader::load('Ex2', $VERSION);

# Preloaded methods go here.

1;
__END__

=head1 NAME

Ex2 - René Nyffeneggers first Perl extension, only for testing purposes.

=head1 SYNOPSIS

  use Ex2;

=head1 DESCRIPTION

This package is used to check wheter a package can be built that
calls c functionality.


=head1 AUTHOR

René Nyffenegger

=head1 COPYRIGHT AND LICENSE

Copyright (C) 2011 René Nyffenegger

This library is free software; you can redistribute it and/or modify
it under the same terms as Perl itself, either Perl version 5.10.1 or,
at your option, any later version of Perl 5 you may have available.


=cut
