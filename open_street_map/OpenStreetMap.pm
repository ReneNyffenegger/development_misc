package OpenStreetMap;

require LWP::UserAgent;

sub new {
  my $self = {};

  $self -> {ua} = LWP::UserAgent->new;

  bless  $self;
  return $self;
}

sub api_call_ {
  my $self       = shift;
  my $name       = shift;
  my $parameters = shift;

  my $call_ = $name;

  if (defined $parameters) {
     $call_ .= "?$parameters";
  }

  my $response = $self -> {ua} -> get("http://api.openstreetmap.org/api/0.6/$call_");

  return $response -> decoded_content;
}

sub capabilities {
  my $self = shift;
  return $self -> api_call_('capabilities');
}

sub map {
  my $self   = shift;

  my $west   = shift;
  my $east   = shift;
  my $north  = shift;
  my $south  = shift;

  return $self -> api_call_('map', "bbox=$west,$south,$east,$north");
}

1;
