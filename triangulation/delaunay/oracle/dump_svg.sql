alter session set nls_numeric_characters = ".,";
@spool triangulation.svg
begin

  dbms_output.put_line('<?xml version="1.0" encoding="UTF-8" standalone="no"?>');
  dbms_output.put_line('<svg>');
  dbms_output.put_line('  <g>');

  for paths in (

      with edges as (
       
           select point_1 p1, point_2 p2 from dt_triangle union
           select point_2 p1, point_3 p2 from dt_triangle union
           select point_1 p1, point_3 p2 from dt_triangle

      ),
      edges_ as (

           select distinct
                  case when p1 < p2 then p1 else p2 end p1,
                  case when p1 < p2 then p2 else p1 end p2
            from  edges

      )
      select
        point_1.x x1, point_1.y y1,
        point_2.x x2, point_2.y y2
      from
        dt_point point_1,
        dt_point point_2,
        edges_
      where
        edges_.p1 = point_1.id and
        edges_.p2 = point_2.id

  ) loop

    dbms_output.put_line('<path style="stroke:#000000;stroke-width:1px;stroke-linecap:square;stroke-linejoin:miter;stroke-opacity:1"' ||
                           ' d="M ' || paths.x1 || ',' || paths.y1 || ' ' || paths.x2 || ',' || paths.y2 || '" />');

  end loop;

  dbms_output.put_line('  </g>');
  dbms_output.put_line('</svg>');

end;
/
spool off
