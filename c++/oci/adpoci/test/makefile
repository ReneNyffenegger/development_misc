CPPFLAGS=-I.. -I$(ORACLE_HOME)/oci/include
CFLAGS=-Wall -Wextra
CC=gcc


01_create_table.exe: 01_create_table.o ../adpoci.o
	gcc $^ -o $@ $(ORACLE_HOME)/bin/oci.dll

02_insert_table.exe: 02_insert_table.o ../adpoci.o
	gcc $^ -o $@ $(ORACLE_HOME)/bin/oci.dll

03_select_table.exe: 03_select_table.o ../adpoci.o
	gcc $^ -o $@ $(ORACLE_HOME)/bin/oci.dll

04_describe_table.exe: 04_describe_table.o ../adpoci.o
	gcc $^ -o $@ $(ORACLE_HOME)/bin/oci.dll

read_pipe.exe: read_pipe.o ../adpoci.o
	gcc $^ -o $@ $(ORACLE_HOME)/bin/oci.dll
