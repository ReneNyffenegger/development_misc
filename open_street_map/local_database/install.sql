/*  

   mysql -u root -p%ROOT_PASSWORD% -e "set @PW='%OSM_PASSWORD%';source install.sql;"

*/

drop   database if exists osm;

delete from mysql.user where host = 'localhost' and user = 'osmuser';

create database osm 
       default character set 'utf8'
       default collate       'utf8_bin';


delete from mysql.user where host = 'localhost' and user = 'osmuser';
drop user osmuser@localhost;
flush privileges;

/*
   Maybe, this is just a limitation on mysql's part, maybe, I just
   don't get it, but it seems impossible to specify a newly
   created user's password with a variable like so:

     create user 'osm_user'@'localhost' identified by @PW 

   Therefore, the following route is taken to mimic the desired
   behaviour.

*/
create user osmuser@localhost;
use mysql;
update user set password=password(@PW) where user = 'osmuser' and host = 'localhost';
flush privileges;

grant all on osm.* to osmuser@localhost;

use osm;

create table node (
  id   integer primary key,
  lat  double not null,
  lon  double not null
);


create table way (
  id       integer primary key,
  building tinyint not null
  /* Unfortunately, it was too costly an operation to
     update the minima and maxima of the nodes pertaining
     to a way within the table (see also comment in
     ..\local_database\indexes.sql) . So, for the time
     being: commented out.
     ---------------------------
   , min_lat  double      null,
     max_lat  double      null,
     min_lon  double      null,
     max_lon  double      null
  */
);

create table relation (
  id       integer primary key
  /*  Unfortunately, it was too costly an operation to
      update the minima and maxima of the nodes pertaining
      to a relation within the table. So, for the time
      being: commented out.
      ---------------------------
    , min_lat  double      null,
      max_lat  double      null,
      min_lon  double      null,
      max_lon  double      null
  */
);

create table node_in_way (
  node_id integer not null references node,
  way_id  integer not null references way,
  order_  integer not null
  --
/*

   It turns out that (node_id, way_id) cannot be a primary key,
   as originally intended, because closed paths containt the
   node that acts as end-node and start-node twice.

   TODO: Maybe it makes sense to create a primary key (node_id, way_id, order_)

   TODO: Does mysql have something like index organized tables?
   
*/
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

