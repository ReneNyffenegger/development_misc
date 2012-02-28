delete from dt_triangle;
delete from dt_point;

insert into dt_point (x,y,id) values (100, 100, 0);
insert into dt_point (x,y,id) values (190, 102, 1);
insert into dt_point (x,y,id) values (100, 195, 2);
insert into dt_point (x,y,id) values (188, 201, 3);
insert into dt_point (x,y,id) values (278, 204, 4);
insert into dt_point (x,y,id) values (358, 203, 5);
insert into dt_point (x,y,id) values ( 80, 222, 6);

exec delaunay_triangulation.triangulate;
@dump_svg
