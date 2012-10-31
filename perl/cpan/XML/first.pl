use strict;
use warnings;

use XML::Parser;


my $xml_file_name = 'first.xml';

open my $xml_file_h, '<', $xml_file_name;

my $xml_parser = new XML::Parser(Style => 'Stream');

$xml_parser -> setHandlers (
   Start     => \&    start_element,
   End       => \&      end_element,
   Char      => \&     char_data,
   Default   => \&  default_element
);

$xml_parser -> parse($xml_file_h);


sub start_element {

  my($parseinst, $element, %attributes) = @_;

  #print "  parseinst: $parseinst\n"; 
  print "start element: [$element]\n";

  foreach my $attribute (keys %attributes) {
    print "    $attribute = $attributes{$attribute}\n"
  }

  print "\n";
}

sub end_element {
  my($parseinst, $element, %attributes) = @_;

  #print " parseinst: $parseinst\n"; 
  print "end element: [$element]\n";

# It seems as though attributes will be always
# be empty in end_element?
  foreach my $attribute (keys %attributes) {
    print "    $attribute = $attributes{$attribute}\n"
  }

  print "\n";
}

sub char_data {
  my($parseinst, $data) = @_;
  $data =~ s/{amp}/&/;

  print "character data:\n";
  print "  data: $data\n"; 

  print "\n";
}

sub default_element {

  my $parseinst = shift;

  my $what_is_this = shift;

  print "default element\n";
  print "  $what_is_this\n";

  print "\n";
}
