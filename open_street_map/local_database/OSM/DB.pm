use warnings;
use strict;

use DBI;
use utf8;

package OSM::DB;

use OSM::Way;
use OSM::Node;
use OSM::Relation;

sub new {

  my $class = shift;

  my $self  = {};

  my $db       = shift;
  my $username = shift;
  my $password = shift;

  $self -> {dbh} = DBI-> connect($db, $username, $password);

# TODO: Really necessary?
  $self -> {dbh} -> do('use osm');
# http://www.gyford.com/phil/writing/2008/04/25/utf8_mysql_perl.php
  $self -> {dbh} -> do('set names utf8');
  $self -> {dbh} -> {mysql_enable_utf8} = 1;

  bless $self, $class;

  return $self;

}

sub Way {

  my $self        = shift;
  my $way_id      = shift;

  my $way  = new OSM::Way ($way_id);

  #  TODO: should only be prepared once
  my $sth_way = $self -> {dbh} -> prepare(<<"SQL") or die;

        select
           node_in_way.way_id,
           node.id      node_id,
           node.lon,
           node.lat
        from 
           node_in_way,
           node
         where
           node_in_way.way_id = ? and
           node_in_way.node_id = node.id
       order by order_

SQL

   $sth_way -> execute($way_id);

   while (my $r_nodes_in_way = $sth_way -> fetchrow_hashref) {
     # TODO: lat before lon
     $way -> addNode(new OSM::Node($r_nodes_in_way -> {node_id}, $r_nodes_in_way->{lon}, $r_nodes_in_way->{lat}));
   }

   return $way;
}

sub Relation {

  my $self        = shift;
  my $relation_id = shift;

  my $relation = new OSM::Relation($relation_id);


   my $sth_ways_in_relation = $self -> {dbh} -> prepare (<<"SQL");

     select 
       way_id,
       role
     from
       way_in_relation
     where
       relation_id = ?
SQL

   $sth_ways_in_relation -> execute($relation_id);

   while (my $r_ways_in_relation = $sth_ways_in_relation->fetchrow_hashref) {

     my $way = $self -> Way($r_ways_in_relation->{way_id}); 

      $relation -> addWay($way, $r_ways_in_relation->{role});
   }

   return $relation;
}

sub BuildingsInRect {

  my $self = shift;
  my $rect = shift;

  if ($rect -> {lon_e} > $rect -> {lon_w}) {
     die sprintf("lon_e %f < lon_w %f", $rect->{lon_e}, $rect->{lon_w});
  }
  if ($rect -> {lat_n} < $rect -> {lat_s}) {
     die sprintf("lat %f < lat_s %f", $rect->{lat_n}, $rect->{lat_s});
  }


   my $sth_buildings_in_rect = $self -> {dbh} -> prepare (<<"SQL");
   
   select 
     way_id 
   from 
     way_coordinates, way 
  where way_coordinates.way_id = way.id and 
  way.building = 1 and
         way_coordinates.lon_max > ?              and 
         way_coordinates.lon_min < ?              and 
         way_coordinates.lat_max > ?              and 
         way_coordinates.lat_min < ?              

SQL


   my @returned_building_ways = ();
   $sth_buildings_in_rect -> execute($rect->{lon_e}, $rect->{lon_w}, $rect->{lat_s}, $rect -> {lat_n});

   while (my $r_buildings_in_rect = $sth_buildings_in_rect->fetchrow_hashref) {

      my $current_building = $self->Way($r_buildings_in_rect->{way_id});
      push @returned_building_ways, $current_building;

  }

  return @returned_building_ways;
}

1;
