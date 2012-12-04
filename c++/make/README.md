The *implicit make rule* for compiling a C program is

    %.o:%.c
    	$(CC) $(CPPFLAGS) $(CFLAGS) -c -o $@ $<
