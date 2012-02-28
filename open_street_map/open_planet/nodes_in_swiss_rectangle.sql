/*

  Switzerland has the following four extreme points:

    o Northernmost point:   LAT  47.8082639
                            lon   8.5678972

    o Southernmost point:   LAT  45.8180306
                            lon   9.0164833

    o Westernmost  point:   lat  46.1322417
                            LON   5.9563028

    o Easternmost  point:   lat  46.612778
                            LON  10.491944


  The following query counts the number of nodes in the switzerland.osm
  file east, west, north and south as well as within these points:

*/
select sum(case when lat >  47.8082639                      and lon <  5.9563028                      then 1 else 0 end) north_west,
       sum(case when lat <= 47.8082639 and lat > 45.8180306 and lon <  5.9563028                      then 1 else 0 end) west,
       sum(case when                       lat < 45.8180306 and lon <  5.9563028                      then 1 else 0 end) south_west,
       /* -- */
       sum(case when lat >  47.8082639                      and lon >= 5.9563028 and lon <= 10.491944 then 1 else 0 end) north,
       sum(case when lat <= 47.8082639 and lat > 45.8180306 and lon >= 5.9563028 and lon <= 10.491944 then 1 else 0 end) center,
       sum(case when                       lat < 45.8180306 and lon >= 5.9563028 and lon <= 10.491944 then 1 else 0 end) south,
       /* -- */
       sum(case when lat >  47.8082639                      and                      lon >  10.491944 then 1 else 0 end) north_east,
       sum(case when lat <= 47.8082639 and lat > 45.8180306 and                      lon >  10.491944 then 1 else 0 end) east,
       sum(case when                       lat < 45.8180306 and                      lon >  10.491944 then 1 else 0 end) south_east
from 
       node;

