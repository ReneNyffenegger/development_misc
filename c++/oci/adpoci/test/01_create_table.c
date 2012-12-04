#include <stdio.h>
#include <stdlib.h>

#include "adpoci.h"

int main(int argc, char* argv[]) {
         char err_msg   [512];

  struct oci_connection conn;

  if (argc < 2) {
    printf("usage %s username/password[@dbname]\n", argv[0]);
    exit (-1);
  }

  text  username[31];
  text  password[31];
  text  dbname  [31];

  parse_connect_string(argv[1],username, password, dbname);

  if (!oci_connect(username, password, dbname, &conn, err_msg)) {
    printf("Error with oci_connect: %s\n",err_msg);
    goto clean_up;
  }

  if (!oci_parse_and_execute("create table oci_test_table ( "
                             "  number_      number,        "
                             "  number_5_3   number(5,3),   "
                             "  varchar2_100 varchar2(100), "
                       //    "  blob_        blob,          "
                       //    "  clob_        clob,          "
                             "  date_        date)          ",
                             err_msg, &conn) ) {
    printf(err_msg);
    goto clean_up;
  }

  printf("A table named oci_test_table should now be created\n");

clean_up:

  OCITerminate(OCI_DEFAULT);

  return 0;
}

