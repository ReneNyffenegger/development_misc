#include "adpoci.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char* argv[]) {

         char           err_msg   [512];
         sword          r;
  struct oci_connection conn;
         OCIStmt*       sh; 

  if (argc < 3) {
    printf("usage %s username/password[@dbname] msg_name\n", argv[0]);
    exit (-1);
  }

  text  username[31];
  text  password[31];
  text  dbname  [31];

  int   s;
  char  item    [100];

  strcpy(item,
       "          "
       "          "
       "          "
       "          "
       "          "
       "          "
       "          "
       "          "
       "          ");

  char  stmt          [] = 
   "  declare                                    " 
   "    s    integer;                            "
   "    item varchar2(200);                      "
   "  begin                                      "
   "    item := '';                              "
   "    s := sys.dbms_pipe.receive_message(:1);  "
   "    if s = 0 then                            "
   "      dbms_pipe.unpack_message(item);        "
   "    end if;                                  "
   "    :2 := s;                                 "
   "    :3 := item;                              "
   "  end;                                       ";


  parse_connect_string(argv[1],username, password, dbname);

  if (!oci_connect(username, password, dbname,&conn, err_msg)) {
    printf(err_msg);
    goto clean_up;
  }

  if (! (sh=oci_parse(stmt, err_msg, &conn )))  {
    printf(err_msg);
    goto clean_up;
  }

  printf("Waiting for messages\n");
  for (;;) {
    if (! (r=oci_execute(sh, err_msg, &conn, 
           3,                 //  3  Bind variables used:
                              // ---------------------
           SQLT_CHR, argv[2], // :1  pipe_name
           SQLT_INT, &s,      // :2  return value of dbms_pipe.receive_message (s)
           SQLT_CHR, item)    // :3  the message received (item)
       )) {

       printf(err_msg);
       break;
    }

    if (s != 0) {
        printf("Abnormal pipe status: %d %s\n\r", s, item);
    }
    else {
        printf("%s\n", item);
    }
  }

clean_up:;
  return 0;
}
