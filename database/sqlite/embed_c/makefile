CC_OPTS=-Wall

# The directory that contains the sqlite source
# files from http://www.sqlite.org/download.html:
DOWNLOAD_DIR=sqlite-amalgamation

INCLUDE=$(DOWNLOAD_DIR)

embed_sqlite.exe: embed_sqlite.o $(DOWNLOAD_DIR)/sqlite3.o
	gcc embed_sqlite.o $(DOWNLOAD_DIR)/sqlite3.o -o $@

embed_sqlite.o: embed_sqlite.c
	gcc $(CC_OPTS) -I$(INCLUDE) -c embed_sqlite.c -o$@

$(DOWNLOAD_DIR)/sqlite3.o: $(DOWNLOAD_DIR)/sqlite3.c
	gcc $(CC_OPTS) -I$(INCLUDE) -c $(DOWNLOAD_DIR)/sqlite3.c -o$@
