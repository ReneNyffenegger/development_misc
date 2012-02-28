drop table   dt_edge;
drop table   dt_triangle;
drop table   dt_point;
drop package dt;

create table dt_point (
   x   number     not null,
   y   number     not null,
   id  number(10) primary key -- must start with 0 and increment by 1!
)
organization index;

create table dt_triangle (
  point_1 not null   references dt_point,
  point_2 not null   references dt_point,
  point_3 not null   references dt_point,
  index_  number(10) primary key
)
organization index;

create table dt_edge (
  point_1 not null references dt_point,
  point_2 not null references dt_point
);


@delaunay_triangulation.pks
@delaunay_triangulation.pkb
