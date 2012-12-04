#include <stdio.h>
#include <stdlib.h>

#include "adpoci.h"

int main(int argc, char* argv[]) {
         char err_msg   [512];
         //sword          r;
  struct oci_connection conn;
         OCIStmt*       sh; 
         int            pos;
  struct oci_description    descr;

  //int numCol;

  if (argc < 2) {
    printf("usage %s username/password[@dbname]\n", argv[0]);
    exit (-1);
  }

  text  username[30];
  text  password[30];
  text  dbname  [30];

  parse_connect_string(argv[1],username, password, dbname);

  if (!oci_connect(username, password, dbname, &conn, err_msg)) {
    printf("Error with oci_connect: %s\n",err_msg);
    goto clean_up;
  }

  if (! (sh=oci_parse("select * from oci_test_table", err_msg, &conn))) {
    printf(err_msg);
    goto clean_up;
  }

  if (! oci_execute0(sh, err_msg, &conn)) {
    printf("after x\n");
    printf(err_msg);
    goto clean_up;
  }

  //OCIAttrGet(sh, OCI_HTYPE_STMT, &numCol, 0, OCI_ATTR_PARAM_COUNT, conn.err);
  //printf("Nof: %d\n", numCol);

  pos = 1;
  while (oci_describe(sh, /*err_msg,*/ &conn, &descr, pos)) {
    printf("%-30s %d:\n", descr.col_name, descr.col_type) ;
    pos++;
  }

clean_up:

  OCITerminate(OCI_DEFAULT);

  return 0;
}

