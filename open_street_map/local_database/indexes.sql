
-- TODO: Impact?
create index node_in_way_node_id_ix on node_in_way (node_id);
create index node_in_way_way_id_ix  on node_in_way (way_id );
create index tag_way_id_ix on tag (way_id);
create index node_lat_lon_ix on node (lat, lon);


--
-- TODO: Use way instead of "min_max" !   
--

 create table way_coordinates as select node_in_way.way_id, min(lat) lat_min, max(lat) lat_max, min(lon) lon_min, max(lon) lon_max from node, node_in_way where node.id = node_in_way.node_id group by node_in_way.way_id;
 
 create index way_coordinates_ix on way_coordinates (lat_min, lat_max, lon_min, lon_max);
-- select * from min_max where
--          max_lon > 8.54321               and 
--          min_lon < 8.54726               and 
--          max_lat > 47.36751              and 
--          min_lat < 47.37669              
