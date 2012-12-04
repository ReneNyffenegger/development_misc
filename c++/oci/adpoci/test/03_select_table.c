#include <stdio.h>
#include <stdlib.h>

#include "adpoci.h"

int main(int argc, char* argv[]) {
         char           err_msg   [512];

  struct oci_connection conn;
         OCIStmt*       sh; 

  int         i_out;
  double      d_out;
  char*       c_out;
  OCIDate    dt_out;

  int        day, month, year, hour, minute, second;

  c_out = (char*) malloc(101);

  if (argc < 2) {
    printf("usage %s username/password[@dbname]\n", argv[0]);
    exit (-1);
  }

  text  username[31];
  text  password[31];
  text  dbname  [31];

  parse_connect_string(argv[1],username, password, dbname);

  if (! oci_connect(username, password, dbname,&conn, err_msg)) {
    printf(err_msg);
    goto clean_up;
  }

  if (! (sh=oci_parse("select number_, number_5_3,        varchar2_100, date_ from oci_test_table where "
                      "number_ > :1 or number_5_3 = :2 or varchar2_100 < :3", err_msg, &conn))) {
    printf(err_msg);
    goto clean_up;
  }
  if (! oci_define(sh, err_msg, &conn, 4, SQLT_INT, &i_out, SQLT_FLT, &d_out, SQLT_CHR, c_out, 100, SQLT_ODT, &dt_out)) {
    printf(err_msg);
    goto clean_up;
  } 
  if (! oci_execute(sh, err_msg, &conn, 3, SQLT_INT,  5, SQLT_FLT, 4.8, SQLT_CHR, "zzz")) {
    printf(err_msg);
    goto clean_up;
  }

  while (oci_fetch(sh, err_msg,&conn)) {
    OCIDateGetDate(&dt_out, &year, &month , &day   );
    OCIDateGetTime(&dt_out, &hour, &minute, &second);
    printf ("fetched %d %f %s  %02d.%02d.%04d %02d:%02d:%02d\n",i_out, d_out, c_out, day, month, year, hour, minute, second);
  }

clean_up:

  free (c_out);
  OCITerminate(OCI_DEFAULT);

  printf("\n");
  return 0;
}
