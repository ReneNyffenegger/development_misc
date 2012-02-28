@rem wieder rein tun. @set OSMDIR=c:\osm
@rem wieder rein tun. 
@rem wieder rein tun. @wget -O %OSMDIR%\switzerland.osm.bz2 http://download1.geofabrik.de/osm/europe/switzerland.osm.bz2 
@rem wieder rein tun. @bzip2 -d %OSMDIR%\switzerland.osm.bz2
@rem wieder rein tun. 
@rem wieder rein tun. @perl ..\local_database\populate\splitOSMFile.pl %OSMDIR%\switzerland.osm > files_loaded.txt
@rem wieder rein tun. 



@REM   create the database
@REM   -------------------
@REM   Be sure to have ROOT_PASSWORD and OSM_PASSWORD set!
@REM

mysql -u root -p%ROOT_PASSWORD% -e "set @PW='%OSM_PASSWORD%';source ../local_database/install.sql;"


@REM   populate the database
@REM   ---------------------
@REM

@for /f %%i in (files_loaded.txt) do perl ..\local_database\populate\OSM_2_db.pl %%i



@REM   create the indexes
@REM   ------------------
@REM
mysql -u osmuser -p%OSM_PASSWORD% -e "source ../local_database/indexes.sql;"
