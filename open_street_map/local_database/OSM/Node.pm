package OSM::Node;

sub new {

  my $class = shift;

  my $id    = shift;
  my $lon   = shift;
  my $lat   = shift;

  my $self  = {id => $id, lon=>$lon, lat=>$lat};
  
  bless $self, $class;

  return $self;
}

1;
