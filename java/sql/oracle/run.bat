set JDBCJAR=%ORACLE_HOME%\jdbc\lib\ojdbc8.jar

set ORAUSER=rene
set ORAPW=rene
set DBSERVER=localhost
set DBPORT=1521
set DBNAME=ora18

java -cp ".;%JDBCJAR%" CreateTable  %ORAUSER%  %ORAPW%  %DBSERVER%  %DBPORT%  %DBNAME%
java -cp ".;%JDBCJAR%" InsertTable  %ORAUSER%  %ORAPW%  %DBSERVER%  %DBPORT%  %DBNAME%
java -cp ".;%JDBCJAR%" SelectTable  %ORAUSER%  %ORAPW%  %DBSERVER%  %DBPORT%  %DBNAME%
java -cp ".;%JDBCJAR%"    MetaData  %ORAUSER%  %ORAPW%  %DBSERVER%  %DBPORT%  %DBNAME%
java -cp ".;%JDBCJAR%"   DropTable  %ORAUSER%  %ORAPW%  %DBSERVER%  %DBPORT%  %DBNAME%
