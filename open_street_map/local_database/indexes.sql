use osm;

create index node_in_way_node_id_ix on node_in_way (node_id);
create index node_in_way_way_id_ix  on node_in_way (way_id );
create index tag_way_id_ix          on tag (way_id);
create index node_lat_lon_ix        on node (lat, lon);


/* 

  Originally, I hoped I could have the minima and maxima of a way's lat and lon
  within that very table, and I would have updated that table with the following
  query ( see also http://dba.stackexchange.com/questions/13434/how-do-i-update-a-table-with-the-aggregted-values-min-max-of-a-related-table):

  Unfortuntatly, it turned out that the query was way too slow, so that
  I decided to create the table 'way_coordinates' with its own index instead (see below).

-------------------------------------------------------------------------------
update way 
  join (
    select 
      node_in_way.way_id,
      min(node.lat)  min_lat,
      max(node.lat)  max_lat,
      min(node.lon)  min_lon,
      max(node.lon)  max_lon
    from
      node_in_way join
      node        on node_in_way.node_id = node.id
    group by
      node_in_way.way_id
  ) way___
set
  way.min_lat = way___.min_lat,
  way.max_lat = way___.max_lat,
  way.min_lon = way___.min_lon,
  way.max_lon = way___.max_lon;

create index way_coordinates_ix in on way (min_lat, max_lat, min_lon, max_lon);
-------------------------------------------------------------------------------

*/

select now(), 'create table way_coordinates';


create table way_coordinates as select node_in_way.way_id, min(lat) lat_min, max(lat) lat_max, min(lon) lon_min, max(lon) lon_max from node, node_in_way where node.id = node_in_way.node_id group by node_in_way.way_id;
select 'create index way_coordinates_ex:';

select now(), 'create index way_coordinates_ix';
create index way_coordinates_ix on way_coordinates (lat_min, lat_max, lon_min, lon_max);

select now(), 'indexes.sql end';
