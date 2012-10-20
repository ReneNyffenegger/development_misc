package Filter;

use     feComposite;
use     feGaussianBlur;
use     feMerge;
use     feOffset;
use     feSpecularLighting;

my $id=1;
sub new {

  my $self = {};
  bless $self, shift;

  $self -> {id}    = 'filter' . $id++;
  $self -> {label} =  $self->{id};

  return $self;
}

sub write {
  my $self    = shift;
  my $svgFile = shift;

  print $svgFile "    <filter\n";
  print $svgFile "       id=\"$self->{id}\"\n";
  print $svgFile "       inkscape:label=\"$self->{label}\">\n";

  for my $effect (@{$self->{effects}}) {
    $effect -> write($svgFile);
  }

  print $svgFile "    </filter>\n";
}

my $result=0;
sub result_ {
  my $filterEffect = shift;

  return $filterEffect->{result} if exists $filterEffect->{result};

  $filterEffect->{result} = 'result' . $result++;

  return $filterEffect->{result};
}

#  Add filter effects {

sub composite {
  my $self = shift;

  my $filterEffect = new feComposite(@_);

  push @{$self->{effects}}, $filterEffect;

  return $filterEffect;
}

sub gaussianBlur {
  my $self = shift;

  my $filterEffect = new feGaussianBlur(@_);

  push @{$self->{effects}}, $filterEffect;

  return $filterEffect;
}

sub merge {
  my $self = shift;

  my $filterEffect = new feMerge(@_);

  push @{$self->{effects}}, $filterEffect;

  return $filterEffect;
}

sub offset {
  my $self = shift;

  my $filterEffect = new feOffset(@_);

  push @{$self->{effects}}, $filterEffect;

  return $filterEffect;
}

sub specularLighing {
  my $self = shift;

  my $filterEffect = new feSpecularLighting(@_);

  push @{$self->{effects}}, $filterEffect;

  return $filterEffect;
}

# }

1;
