#ifdef __GNUC__
#  define _int64 long long
#endif

#ifdef __cplusplus
extern "C" {
#endif

#include <oci.h>

struct  oci_connection {
  /* The environment handle defines a context in which all OCI functions are
     invoked. Each environment handle contains a memory cache, which allows for
     fast memory access. All memory allocation under the environment handle is
     done from this cache. Access to the cache is serialized if multiple
     threads try to allocate memory under the same environment handle. When
     multiple threads share a single environment handle, they may block on
     access to the cache. The environment handle is passed as the parent
     parameter to the OCIHandleAlloc() call to allocate all other handle types.
     Bind and define handles are allocated implicitly.
  */
  OCIEnv*       env;

  /* The error handle is passed as a parameter to most OCI calls. The error
     handle maintains information about errors that occur during an OCI
     operation. If an error occurs in a call, the error handle can be passed to
     OCIErrorGet() to obtain additional information about the error that
     occurred. Allocating the error handle is one of the first steps in an OCI
     application because most OCI calls require an error handle as one of its
     parameters. */
  OCIError*     err;

  OCIServer*    srv;
  OCISvcCtx*    svc;
  OCISession*   ses;
};

struct oci_description {
  text  col_name[31];
  ub2   col_type;
};

void checkerr(OCIError* err, sword status, char errbuf[512]);

void parse_connect_string (
   char* connect_str,  /* in   */
   text  username[31], /* out  */
   text  password[31], /* out  */
   text  dbname  [31]  /* out  */
);

int oci_describe(
           OCIStmt*            sh,
/*         char*               errmsg,*/
    struct oci_connection*     conn,
    struct oci_description*    descr,
           int                 pos);

int oci_connect(
          text            username[30],
          text            password[30],
          text            dbname  [30],
   struct oci_connection* connection,
   char   errmsg  [512]
);


int oci_parse_and_execute(
         char*           stmt,
         char            errmsg[512],
  struct oci_connection* conn
);
int oci_execute0(
           OCIStmt*        sh, 
           char*           errmsg, 
    struct oci_connection* conn);

OCIStmt* oci_parse(
         char*           stmt,
         char            errmsg[512],
  struct oci_connection* conn );


int oci_execute(
           OCIStmt*        sh, 
           char*           errmsg, 
    struct oci_connection* conn,
           int nof_binds, 
    ...);

int oci_fetch(
           OCIStmt*        sh,
           char*           errmsg,
    struct oci_connection* conn);

int oci_define(
           OCIStmt*        sh, 
           char*           errmsg, 
    struct oci_connection* conn,
           int             nof_defines, 
    ...);

int oci_commit(struct oci_connection* conn, char* errmsg);

#ifdef __cplusplus
}
#endif
