create or replace package body delaunay_triangulation as

    procedure dbg(txt in varchar2) is
    begin
      $IF $$DBG $THEN
          dbms_output.put_line(txt);
      $ELSE
          null;
      $END
    end dbg;

    procedure check_dt_triangle (i in number) is

    --   Internal Function to check whether dt_triangle
    --   has gaps in its column "index_".
    --   This must not occur. Used while debugging and
    --   can be commented out.

         cnt  number;
         max_ number;
    begin
         select count(*), max(index_) + 1 into cnt, max_ from dt_triangle;
         if cnt != i then 
            raise_application_error(-20800, 'cnt: ' || ', i: ' || i);
         end if;
         if cnt != max_ then 
            raise_application_error(-20800, 'cnt: ' || ', max: ' || max_);
         end if;

         for i in 0 .. cnt -1 loop

             select count(*) into cnt from dt_triangle where index_ = i;

             if cnt != 1 then
               raise_application_error(-20800, 'cnt: ' || cnt);
             end if;

         end loop;

    end check_dt_triangle;

    function  inCircle(id_point in number, id_triangle in number) return boolean -- {

    --
    --        return true if point referenced by id_point lies inside the 
    --        circumcircle of the triangle referenced by id_triangle.
    --
    --        A point ON the edge of the circumcircle is considered 
    --        inside the circumcircle.
    --

    is
        
        epsilon    constant    number := 0.00000000000000001;

        point      dt_point    %rowtype;

        triangle   dt_triangle %rowtype;

        point_1    dt_point    %rowtype;
        point_2    dt_point    %rowtype;
        point_3    dt_point    %rowtype;


        m1         number;
        m2         number;
        mx1        number;
        mx2        number;
        my1        number;
        my2        number;
  
        --         Circumcircle center coordinates:
        xc         number;
        yc         number;


        dx         number;
        dy         number;
        rsqr       number;
        drsqr      number;


    begin
        select * into triangle from dt_triangle where index_ = id_triangle;

        select * into point_1 from dt_point where id = triangle.point_1;
        select * into point_2 from dt_point where id = triangle.point_2;
        select * into point_3 from dt_point where id = triangle.point_3;

        if abs(point_1.y - point_2.y) < epsilon and   -- {
           abs(point_2.y - point_3.y) < epsilon then

          -- incircum - F - Points are coincident.
          
          return false;

        end if; -- }

        select * into point from dt_point where id = id_point;

        if      abs(point_2.y - point_1.y) < epsilon then -- {

                m2  := -(point_3.x - point_2.x) / (point_3.y - point_2.y);
                mx2 :=  (point_2.x + point_3.x) / 2;
                my2 :=  (point_2.y + point_3.y) / 2;
                --
                xc  :=  (point_2.x + point_1.x) / 2;
                yc  :=   m2 * (xc-mx2) + my2;

        -- }
        elsif   abs(point_3.y - point_2.y) < epsilon then -- {

                m1  := -(point_2.x - point_1.x) / (point_2.y - point_1.y);
                mx1 :=  (point_1.x + point_2.x) / 2;
                my1 :=  (point_1.y + point_2.y) / 2;
                --
                xc  :=  (point_3.x + point_2.x) / 2;
                yc  :=   m1 * (xc-mx1) + my1;

        -- }
        else    -- {

                m1  := -(point_2.x - point_1.x) / (point_2.y - point_1.y);
                m2  := -(point_3.x - point_2.x) / (point_3.y - point_2.y);

                mx1 :=  (point_1.x + point_2.x) / 2;
                mx2 :=  (point_2.x + point_3.x) / 2;

                my1 :=  (point_1.y + point_2.y) / 2;
                my2 :=  (point_2.y + point_3.y) / 2;

                xc  :=  (m1*mx1 - m2*mx2 + my2-my1) / (m1-m2);
                yc  :=  m1 * (xc-mx1) + my1;

        end if;-- }


        dx    := point_2.x - xc;
        dy    := point_2.y - yc;

        rsqr  := dx*dx + dy*dy;

        dx    := point.x - xc;
        dy    := point.y - yc;

        drsqr := dx*dx + dy*dy;

        return drsqr <= rsqr;

    end inCircle; -- }

    procedure triangulate is 
    -- {
        i                number;
        j                number;
        nv               number;

        trimax           number;

        xmin             number;
        xmax             number;
        ymin             number;
        ymax             number;

        dx               number;
        dy               number;
        dmax             number;

        xmid             number;
        ymid             number;

        triangle_index   number := 0;

        edge_count       number;
    -- }
    begin

    --  See also http://www.codeguru.com/cpp/cpp/algorithms/general/article.php/c8901
    --
    --      add_vertex(vertex)
    --      {
    --         for (each triangle)
    --         {
    --            if (vertex is inside triangle's circumscribed circle)
    --            {
    --               store triangle's edges in edgebuffer
    --               remove triangle
    --            }
    --         }
    --         remove all double edges from edgebuffer,
    --            keeping only unique ones
    --         for (each edge in edgebuffer)
    --         {
    --            form a new triangle between edge and vertex
    --         }
    --      }
    --

        select count(*) into nv from dt_point;

        if nv < 3 then 
           return;
        end if;

        trimax := nv * 4;

        select min(x), max(x), min(y), max(y) 
         into  xmin  , xmax  , ymin  , ymax
         from  dt_point;

        dx := xmax - xmin;
        dy := ymax - ymin;

        if dx > dy then -- { assign dmax
           dmax := dx;
        else
           dmax := dy;
        end if;  -- }

        xmid := (xmax + xmin) / 2;
        ymid := (ymax + ymin) / 2;

       -- Set up the supertriangle	
       -- ------------------------
       -- This is a triangle which encompasses all the sample points.	
       -- The supertriangle coordinates are added to the end of the	
       -- vertex list. The supertriangle is the first triangle in	
       -- the triangle list.

       insert into dt_point (x, y, id) values (  xmid - 2*dmax ,  ymid -   dmax , nv  );
       insert into dt_point (x, y, id) values (  xmid          ,  ymid + 2*dmax , nv+1);
       insert into dt_point (x, y, id) values (  xmid + 2*dmax ,  ymid -   dmax , nv+2);



       dbg('new triangle ' || triangle_index || ' (' || nv || ',' || (nv+1) || ',' || (nv+2));
       insert into dt_triangle (point_1, point_2, point_3, index_) values (nv, nv+1, nv+2, triangle_index);
       triangle_index := triangle_index + 1;

--     check_dt_triangle(triangle_index);



       --  Include each point one at a time into the existing mesh:
       for i in 0 .. nv-1 loop -- {

           dbg('next point, i: ' || i);
           delete from dt_edge;

       --  Set up the edge buffer
       --  If the point (Vertex(i).x,Vertex(i).y) lies inside the 
       --  circumcircle then then the three edges of that triangle 
       --  are added to the edge buffer and the triangle is removed 
       --  from list.

           j := 0;

           loop  -- {
                 --   Iterate over each triangle and test, if
                 --   point (i) is within this triangle's 
                 --   circumscribed circle.

               exit when j >= triangle_index;

               dbg('  inCircle testing i: ' || i || ', j: ' || j);
               if inCircle(i, j) then -- {

               -- Yes, point(i) is within triangles(j) circumsribed
               -- circle

                dbg('  inCircle tested');

               -- The triangle(j)'s edges are stored in an "edge buffer",
               --(here implemented with table dt_edge) and ...

                
                  insert into dt_edge (point_1, point_2) 
                   with t as (select point_1, point_2, point_3 from dt_triangle where index_ = j)
                   select t.point_1, t.point_2 from t union all
                   select t.point_2, t.point_3 from t union all
                   select t.point_3, t.point_1 from t;

               --  ... the triangle is removed:

                   dbg('  delete triangle ' || j);
                   delete from dt_triangle where index_ = j;
                   triangle_index := triangle_index - 1;
                   update dt_triangle set index_ = index_ -1 where index_ > j;
                   check_dt_triangle(triangle_index);

                   j := j-1;

               end if; -- }

               j := j+1;
           end loop; -- }

           if i >= nv then
              raise_application_error(-20801, 'not expected');
              /* TODO... goto CONT; */
           end if;

           declare
              c number;
           begin
              select count(*) into c from dt_edge;
              dbg('  count of edge: ' || c);
           end;

           -- This is the tricky part! Remove all *duplicate edges*, that
           -- is, those that occur at least twice. Those must be completely
           -- removed, not only such that one of those remains!
           -- This is stipulated by "f.rowid <> e.rowid".
           delete from dt_edge e  where exists (
             select 1 from dt_edge f 
              where 
                ((f.point_1 = e.point_1 and f.point_2 = e.point_2) or
                 (f.point_1 = e.point_2 and f.point_2 = e.point_1))
                and
                 f.rowid <> e.rowid
           );


           -- Form new triangles for the current point
           -- Skipping over any tagged edges.
           -- All edges are arranged in clockwise order.

           for j in (select point_1, point_2 from dt_edge) loop -- {
            

               if triangle_index >= trimax then
               -- TODO: Can this case be expected at all?
                  dbms_output.put_line('Exceeded maximum edges!');
               end if;

               dbg('  new triangle ' || triangle_index || ' (' || j.point_1 || ',' || j.point_2 || ',' || i ||')');
               insert into dt_triangle (point_1, point_2, point_3, index_) values (j.point_1, j.point_2, i, triangle_index);
               triangle_index := triangle_index + 1;
               check_dt_triangle(triangle_index);

           end loop; -- }


/*
 
   TODO: Really used?

<<CONT>> null;
*/
       end loop; -- }


       -- Remove triangles with supertriangle vertices.
       -- These are triangles which have a vertex number greater than nv

       check_dt_triangle(triangle_index);

       delete from dt_edge;

    -- Remove (the 3 ?) supertriangle vertices
       delete from dt_triangle where 
              point_1 >= nv or
              point_2 >= nv or
              point_3 >= nv;


       delete from dt_point where id >= nv;


    end triangulate;

end delaunay_triangulation;
/
