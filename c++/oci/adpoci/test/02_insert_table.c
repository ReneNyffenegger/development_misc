#include "adpoci.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char* argv[]) {
         char err_msg   [512];

  struct oci_connection conn;
         int            i;
         double         d;
         char*          c;
         OCIStmt*       sh; 
         OCIDate        aug_28th_1970_22h23m44s;
         OCIDate        feb_01th_2003_04h05m06s;

  if (argc < 2) {
    printf("usage %s username/password[@dbname]\n", argv[0]);
    exit (-1);
  }

  text  username[30];
  text  password[30];
  text  dbname  [30];

  parse_connect_string(argv[1],username, password, dbname);

  if (!oci_connect(username, password, dbname,&conn, err_msg)) {
    printf(err_msg);
    goto clean_up;
  }
  
  if (! (sh=oci_parse("insert into oci_test_table (number_, number_5_3, varchar2_100, date_) values (:1, :2, :3, :4)", err_msg, &conn))) {
    printf("could not oci_parse: %s\n", err_msg);
    goto clean_up;
  }

  OCIDateSetTime(&aug_28th_1970_22h23m44s,   22, 23, 44);
  OCIDateSetDate(&aug_28th_1970_22h23m44s, 1970,  8, 28);

  if (!oci_execute(sh, err_msg, &conn, 4, 
       SQLT_INT,  1  , 
       SQLT_FLT,  4.8, 
       SQLT_CHR,  "first",
       SQLT_ODT,  &aug_28th_1970_22h23m44s
       )) {

    printf("could not oci_execute (1): %s\n", err_msg);
    goto clean_up;

  }
  i = 10;
  d = 24.44;
  c = (char*)malloc(50);
  strcpy(c, "second");

  OCIDateSetTime(&feb_01th_2003_04h05m06s,    4,  5,  6);
  OCIDateSetDate(&feb_01th_2003_04h05m06s, 2003,  2,  1);

  if (!oci_execute(sh, err_msg, &conn, 4, 
     SQLT_INT, i, 
     SQLT_FLT, d, 
     SQLT_CHR, c,
     SQLT_ODT, &feb_01th_2003_04h05m06s)) {
    printf("could not oci_execute (2): %s\n", err_msg);
    goto clean_up;
  }
  free(c);

  oci_parse_and_execute("commit",err_msg,&conn);

clean_up:

  OCITerminate(OCI_DEFAULT);

  return 0;
}

