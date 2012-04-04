read_pipe.exe: read_pipe.o ../adpoci.o
	gcc read_pipe.o ../adpoci.o -o read_pipe.exe $(ORACLE_HOME)/bin/oci.dll

read_pipe.o: read_pipe.c ../adpoci.h
	gcc -Wall -I.. -I$(ORACLE_HOME)/oci/include -c read_pipe.c -o read_pipe.o
