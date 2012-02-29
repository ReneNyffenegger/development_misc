/*

  This SQL Statement creates a table that plots
  the node density of the switzerland osm file.

  For example, if a bucket's length is to be 1/4 km 
 (so that a bucket represents 0.0625 km^2),
  we get the following numbers:

 

  Switzerland extends
    220 km from south to north  (45.8180306 - 47.8082639) and
    348 km from west to east    ( 5.9563028 - 10.491944 )

  With these figures, the 
    latitude-bucket height is (47.8082639-45.8180306) / 220 / 4 = 0.002261628750000 and the
    longitude-bucket width is (10.491944 - 5.9563028) / 348 / 4 = 0.003258362931034

  -------------------------

  The perl script 'plot_swiss_node_density.pl' iterates over the values created
  here and plots a density-image.

*/

use osm;

set @width_km     = 348;
set @height_km    = 220;
set @pixel_per_km =   4;

set @lat_bucket_height = (47.8082639-45.8180306) / @height_km / @pixel_per_km;
set @lon_bucket_width  = (10.491944 - 5.9563028) / @width_km  / @pixel_per_km;


create table swiss_node_density as
select
  count(*)                                         c,
  floor ((lon  -  5.9563028) / @lon_bucket_width ) x,
  floor ((lat  - 45.8082639) / @lat_bucket_height) y
from 
  node
where
  lat >= 45.8180306 and lat <= 47.8082639 and
  lon >=  5.9563028 and lon <= 10.491944
group by
  floor ((lon  -  5.9563028) / @lon_bucket_width ),
  floor ((lat  - 45.8082639) / @lat_bucket_height);
