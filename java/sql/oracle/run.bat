set JDBCJAR=%ORACLE_HOME%\jdbc\lib\ojdbc5.jar

java -cp ".;%JDBCJAR%" CreateTable  %ORAUSER%  %ORAPW%  %DBSERVER%  %DBPORT%  %DBNAME%
java -cp ".;%JDBCJAR%" InsertTable  %ORAUSER%  %ORAPW%  %DBSERVER%  %DBPORT%  %DBNAME%
java -cp ".;%JDBCJAR%" SelectTable  %ORAUSER%  %ORAPW%  %DBSERVER%  %DBPORT%  %DBNAME%
java -cp ".;%JDBCJAR%"    MetaData  %ORAUSER%  %ORAPW%  %DBSERVER%  %DBPORT%  %DBNAME%
java -cp ".;%JDBCJAR%"   DropTable  %ORAUSER%  %ORAPW%  %DBSERVER%  %DBPORT%  %DBNAME%
