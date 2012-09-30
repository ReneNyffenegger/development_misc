#
#
#

library(RODBC)

con <- odbcConnect("ORA11R2", uid="rene", pwd="rene")

tables = sqlQuery(con, "select owner, table_name from dba_tables where owner not in ('SYS', 'SYSTEM')")

print(tables)

close(con)
