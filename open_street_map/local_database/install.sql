/*  

   mysql -u root -p%ROOT_PASSWORD% -e "set @PW='%OSM_PASSWORD%';source install.sql;"

*/

create database osm 
       default character set 'utf8'
       default collate       'utf8_bin';


/* create user 'osm_user'@'localhost' identified by @PW */
create user 'osmuser'@'localhost';
use mysql;
update user set password=password(@PW) where user = 'osmuser' and host = 'localhost';
flush privileges;

grant all on osm.* to osmusr@localhost;

use osm;

create table node (
  id   integer primary key,
  lat  double not null,
  lon  double not null
);


/*  will be used to create the final table way, that also has the lat_min, lat_max and so on attributes */
create table way (
  id       integer primary key,
  building tinyint not null
);

create table relation (
  id integer primary key
);

create table node_in_way (
  node_id integer not null references node,
  way_id  integer not null references way,
  order_  integer not null
  --
/*primary key (node_id, way_id)*/
);


create table way_in_relation (
  way_id       integer not null references way,
  relation_id  integer not null references relation, 
  --
  role  varchar(100)     -- 'inner', 'outer', 'forward', 'backward'  ....?
);

create table node_in_relation (
  node_id      integer not null references node,
  relation_id  integer not null references relation, 
  --
  role  varchar(100)     -- 'stop_\d+', 'backward_stop_\d+', 'forward_stop_\d+'
);

create table tag (
  k            varchar(1000),
  v            varchar(1000),
  --
  node_id      integer null references node,
  way_id       integer null references way,
  relation_id  integer null references relation
);

