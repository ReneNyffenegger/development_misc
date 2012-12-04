CPPFLAGS=-I.. -I$(ORACLE_HOME)/oci/include
CFLAGS=-Wall -Wextra
CC=gcc

%.exe:%.o ../adpoci.o
	gcc $(CFLAGS) $^ -o $@ $(ORACLE_HOME)/bin/oci.dll

all: 01_create_table.exe 02_insert_table.exe 03_select_table.exe 04_describe_table.exe read_pipe.exe
