#include "adpoci.h"

#include <string.h>
#include <stdio.h>

static int oci_env_created = 0;

int oci_connect(
          text            username[31],
          text            password[31],
          text            dbname  [31],
   struct oci_connection* conn,
          char errmsg[512]
   ) {

  sword r;

  if (!oci_env_created) {
    r=OCIEnvCreate( &conn->env, 
          OCI_DEFAULT |
          OCI_THREADED
        //OCI_OBJECT
        //OCI_EVENTS
        //OCI_NO_UCB 
        //OCI_ENV_NO_MUTEX
        //OCI_NEW_LENGTH_SEMANTICS 
        , 0, 0, 0, 0, 0, 0); 

    if (r != OCI_SUCCESS) {
      strcpy((char*) errmsg, "Couldn't create environment (OCIEnvCreate");
      goto clean_up;
    }
    oci_env_created = 1;
  }

  OCIHandleAlloc(conn->env, (dvoid**)&conn->err, OCI_HTYPE_ERROR,   0, 0);
  OCIHandleAlloc(conn->env, (dvoid**)&conn->srv, OCI_HTYPE_SERVER,  0, 0);
  OCIHandleAlloc(conn->env, (dvoid**)&conn->svc, OCI_HTYPE_SVCCTX,  0, 0);
  OCIHandleAlloc(conn->env, (dvoid**)&conn->ses, OCI_HTYPE_SESSION, 0, 0);

//    r = OCILogon(conn->env, conn->err, &conn->svc, 
//        username, strlen((const char*) username),
//        password, strlen((const char*) password),
//        dbname  , strlen((const char*) dbname  ));


  r=OCIServerAttach(conn->srv, conn->err, (text*) dbname, strlen((const char*)dbname), (ub4) OCI_DEFAULT);
  if (r != OCI_SUCCESS) {
    checkerr(conn->err, r, errmsg);
    goto clean_up;
  }

  OCIAttrSet(conn->svc, OCI_HTYPE_SVCCTX, conn->srv, 0, OCI_ATTR_SERVER,  conn->err);

  OCIAttrSet(conn->ses, OCI_HTYPE_SESSION, username, strlen((const char*)username), OCI_ATTR_USERNAME, conn->err); 
  OCIAttrSet(conn->ses, OCI_HTYPE_SESSION, password, strlen((const char*)password), OCI_ATTR_PASSWORD, conn->err); 

  if ( (r=OCIAttrSet((dvoid *) conn->svc, (ub4) OCI_HTYPE_SVCCTX, (dvoid *) conn->ses, (ub4) 0, (ub4) OCI_ATTR_SESSION, conn->err)) ) {
    checkerr(conn->err, r,errmsg);
    goto clean_up;
  }

  r=OCISessionBegin (conn->svc, conn->err, conn->ses, OCI_CRED_RDBMS, OCI_DEFAULT);
  if (r != OCI_SUCCESS) {
    checkerr(conn->err, r,errmsg);
    goto clean_up;
  }

  return 1;

clean_up:

  //strcpy(errmsg,(const char*) errbuf);
  return 0;
}
  

void checkerr(OCIError* err, sword status, char errbuf[512]) {
  sb4 errcode;

  switch (status) {
  case OCI_SUCCESS:
    strcpy(errbuf, "No error");
    break;
  case OCI_SUCCESS_WITH_INFO:
    strcpy(errbuf, "OCI_SUCCESS_WITH_INFO");
    break;
  case OCI_NEED_DATA:
    strcpy(errbuf, "OCI_NEED_DATA");
    break;
  case OCI_NO_DATA:
    strcpy(errbuf, "OCI_NO_DATA");
    break;
  case OCI_ERROR:
    OCIErrorGet (err, (ub4) 1, (text*) NULL, &errcode, (text*) errbuf, (ub4) 512 , (ub4) OCI_HTYPE_ERROR);
    break;
  case OCI_INVALID_HANDLE:
    strcpy(errbuf, "OCI_INVALID_HANDLE");
    break;
  case OCI_STILL_EXECUTING:
    strcpy(errbuf, "OCI_STILL_EXECUTING");
    break;
  case OCI_CONTINUE:
    strcpy(errbuf, "OCI_CONTINUE");
    break;
  default:
    strcpy(errbuf, "Unknown error");
    break;
  }
}

void parse_connect_string(
   char* connect_str,  /* in   */
   text  username[31], /* out  */
   text  password[31], /* out  */
   text  dbname  [31]  /* out  */
) {

  username[0] = 0;
  password[0] = 0;
  dbname  [0] = 0;

  text* to=username;

  while (*connect_str) {
    if (*connect_str == '/') {
      *to=0;
      to=password;
      connect_str++;
      continue;
    }
    if (*connect_str == '@') {
      *to=0;
      to=dbname;
      connect_str++;
      continue;
    }
    *to=*connect_str;
    to++;
    connect_str++;
  }
  *to=0;
}

int oci_parse_and_execute(
         char*           stmt,
         char            errmsg[512],
  struct oci_connection* conn
) {
  OCIStmt       *sh;
  sword r;

  if ((r=OCIHandleAlloc((dvoid *) conn->env, (dvoid **) &sh, (ub4) OCI_HTYPE_STMT, (size_t) 0, (dvoid **) 0))) {
    checkerr(conn->err, r, errmsg);
    return 0;
  }

  if ((r=OCIStmtPrepare(sh, conn->err, (text*) stmt, (ub4) strlen(stmt), (ub4) OCI_NTV_SYNTAX, (ub4) OCI_DEFAULT))) {
    checkerr(conn->err, r, errmsg);
    OCIHandleFree((dvoid *) sh, (ub4) OCI_HTYPE_STMT);
    return 0;
  }
  if ((r=OCIStmtExecute(conn->svc, sh, conn->err, (ub4) 1, (ub4) 0, (CONST OCISnapshot *) 0, (OCISnapshot *) 0, (ub4) OCI_DEFAULT))) {
    checkerr(conn->err, r, errmsg);
    OCIHandleFree((dvoid *) sh, (ub4) OCI_HTYPE_STMT);
    return 0;
  }

  OCIHandleFree((dvoid *) sh, (ub4) OCI_HTYPE_STMT);
  return 1;
}

OCIStmt* oci_parse(
         char*           stmt,
         char            errmsg[512],
  struct oci_connection* conn ) {

  OCIStmt* sh;
  sword r;

  if ( (r=OCIHandleAlloc((dvoid*) conn->env, (dvoid **) &sh, (ub4) OCI_HTYPE_STMT, (size_t) 0, (dvoid **) 0)) ) {
    checkerr(conn->err, r, errmsg);
    return 0;
  }
  if ((r=OCIStmtPrepare(sh, conn->err, (text*)(void*)stmt, (ub4) strlen((char *) stmt), (ub4) OCI_NTV_SYNTAX, (ub4) OCI_DEFAULT))) {
    checkerr(conn->err, r, errmsg);
    OCIHandleFree((dvoid*) sh, (ub4) OCI_HTYPE_STMT);
    return 0;
  }

  return sh;
}

/*

VARCHAR2                                      char[n]                                             SQLT_CHR
NUMBER                                        unsigned char[21]                                   SQLT_NUM
8-bit                                         signed INTEGER 3 signed char                        SQLT_INT
16-bit                                        signed INTEGER 3 signed short, signed int           SQLT_INT
32-bit                                        signed INTEGER 3 signed int, signed long            SQLT_INT
FLOAT                                         float, double                                       SQLT_FLT
Null-terminated STRING                        char[n+1]                                           SQLT_STR
VARNUM                                        char[22]                                            SQLT_VNU
LONG                                          char[n]                                             SQLT_LNG
VARCHAR                                       char[n+sizeof(short integer)]                       SQLT_VCS
DATE                                          char[7]                                             SQLT_DAT
VARRAW                                        unsigned char[n+sizeof(short integer)]              SQLT_VBI
RAW                                           unsigned char[n]                                    SQLT_BIN
LONG RAW                                      unsigned char[n]                                    SQLT_LBI
UNSIGNED INT                                  unsigned                                            SQLT_UIN
LONG VARCHAR                                  char[n+sizeof(integer)]                             SQLT_LVC
LONG VARRAW                                   unsigned char[n+sizeof(integer)]                    SQLT_LVB
CHAR                                          char[n]                                             SQLT_AFC
CHARZ                                         char[n+1]                                           SQLT_AVC
ROWID descriptor                              OCIRowid *                                          SQLT_RDD
NAMED DATA TYPE                               struct                                              SQLT_NTY
REF                                           OCIRef                                              SQLT_REF
Character LOB descriptor                      OCILobLocator (see note 2)                          SQLT_CLOB
Binary LOB descriptor                         OCILobLocator (see note 2)                          SQLT_BLOB
Binary FILE descriptor                        OCILobLocator                                       SQLT_FILE
OCI string type                               OCIString                                           SQLT_VST (see note 1)
OCI date type                                 OCIDate *                                           SQLT_ODT (see note 1)
ANSI DATE descriptor                          OCIDateTime *                                       SQLT_DATE
TIMESTAMP descriptor                          OCIDateTime *                                       SQLT_TIMESTAMP
TIMESTAMP WITH TIME ZONE descriptor           OCIDateTime *                                       SQLT_TIMESTAMP_TZ
INTERVAL YEAR TO MONTH descriptor             OCIInterval *                                       SQLT_INTERVAL_YM
INTERVAL DAY TO SECOND descriptor             OCIInterval *                                       SQLT_INTERVAL_DS
TIMESTAMP WITH LOCAL TIME ZONE descriptor     OCIDateTime *                                       SQLT_TIMESTAMP_LTZ

(1) For more information on the use of these datatypes, refer to Chapter 11, "Object-Relational Datatypes". 

(2) In applications using datatype mappings generated by OTT, CLOBs may be mapped as OCIClobLocator, and BLOBs may be mapped as 
    OCIBlobLocator. For more information, refer to Chapter 14, "The Object Type Translator (OTT)".
 
*/

int oci_define(
           OCIStmt*        sh, 
           char*           errmsg, 
    struct oci_connection* conn,
           int             nof_defines, 
    ...) {

  OCIDefine *defnp = (OCIDefine *) 0;
  sword      r;
  va_list    defines;
  dvoid*     value_ptr;
  int        sz;
  int        pos;
  ub2        dt_type;

  va_start(defines, nof_defines);
  for (pos=0;pos<nof_defines; pos++) {

    dt_type   = va_arg(defines, int);

    switch (dt_type) {
      case SQLT_INT: 
//      printf("SQLT_INT\n");
        value_ptr=va_arg(defines, dvoid*);
        sz       = sizeof(int); 
        break;
      case SQLT_FLT:  
//      printf("SQLT_FLT\n");
        value_ptr = va_arg(defines, dvoid*);
        sz        = sizeof(double); 
        break;
      case SQLT_CHR:
      case SQLT_STR:
//      printf("SQLT_STR\n");
        value_ptr = va_arg(defines, dvoid*);
        sz        = va_arg(defines, int); // or should this be long?
        break;
      case SQLT_ODT:
//      printf("SQLT_ODT\n");
        value_ptr = va_arg(defines, dvoid*);
        sz        = sizeof(OCIDate);
        break;
      default:
        //"THIS MUST NOT HAPPEN";
        strcpy(errmsg, "adp_oci_error 0001, datatype not yet implemented");
        return 0;
    }

    if ( (r=OCIDefineByPos(
        sh, 
        &defnp, 
        conn->err, 
        pos+1, 
        value_ptr,
        sz,
        dt_type, 
       (dvoid *) 0,  // indp
       (ub2   *) 0,  // rlenp
       (ub2   *) 0,  // rcodep
       OCI_DEFAULT) )) {
         checkerr(conn->err, r, errmsg);
         return 0;
      }
  }
  return 1;
}


int oci_execute(
           OCIStmt*        sh, 
           char*           errmsg, 
    struct oci_connection* conn,
           int             nof_binds, 
    ...) {

  OCIBind       *bndhp = (OCIBind*) 0;
  sword r;
  int   sz;
  int   pos;

  va_list      binds;
  ub2          dt_type;
  dvoid       *value_ptr;
  int          i;
  double       d;

  va_start(binds, nof_binds);

  for (pos=0;pos<nof_binds;pos++) {

    dt_type   = va_arg(binds, int);

    switch (dt_type) {
      case SQLT_INT: 
        i        = va_arg(binds, int);
//      printf("SQLT_INT: %d\n", i);
        sz       = sizeof(int); 
        value_ptr= &i; 
        break;
      case SQLT_FLT:  
        d         = va_arg(binds, double);
//      printf("SQLT_FLT: %f\n", d);
        sz        = sizeof(double); 
        value_ptr = &d; 
        break;
      case SQLT_CHR:
        value_ptr = va_arg(binds, char*);
//      printf("SQLT_CHR: %s\n", (char*) value_ptr);
        sz        = strlen( (char*) value_ptr);
        break;
      case SQLT_ODT:
//      printf("SQLT_ODT\n");
        value_ptr = va_arg(binds, OCIDate*);
        sz        = sizeof(OCIDate);
        break;
    }

    if ((r=OCIBindByPos(sh, &bndhp, conn->err,
                      (ub4) pos+1,             // position
                      value_ptr,               // value pointer
                      sz,                      // size
                      dt_type,
                      (dvoid *) 0,             // indp
                      (ub2   *) 0,             // alenp
                      (ub2   *) 0,             // rcodep
                      (ub4    ) 0,             // maxarr_len
                      (ub4   *) 0,             // curelp
                      (ub4) OCI_DEFAULT))) {

       checkerr(conn->err, r, errmsg);
       return 0;
    }
  }

  if ((r=OCIStmtExecute(
        conn->svc, 
        sh, 
        conn->err, 
  //-------
  //    (ub4) 1,  // iters
        (ub4) 0,  // iters
  //-------
        (ub4) 0, (CONST OCISnapshot *) 0, (OCISnapshot *) 0, (ub4) OCI_DEFAULT))) {
    checkerr(conn->err, r, errmsg);
    OCIHandleFree((dvoid*) sh, (ub4) OCI_HTYPE_STMT);
    return 0;
  }
  return 1;
}

/*
   Todo: Getting the number of columns in the query :
  OCIAttrGet(stmhp, OCI_HTYPE_STMT, &numcols, 0, OCI_ATTR_PARAM_COUNT, errh);
*/

int oci_execute0(
           OCIStmt*        sh, 
           char*           errmsg, 
    struct oci_connection* conn) {
  sword r;
  if ((r=OCIStmtExecute(
        conn->svc, 
        sh, 
        conn->err, 
        (ub4) 0,  // iters
        (ub4) 0, (CONST OCISnapshot *) 0, (OCISnapshot *) 0, (ub4) OCI_DEFAULT))) {
    checkerr(conn->err, r, errmsg);
    OCIHandleFree((dvoid*) sh, (ub4) OCI_HTYPE_STMT);
    return 0;
  }
  return 1;
}

int oci_fetch(
           OCIStmt*        sh,
           char*           errmsg,
    struct oci_connection* conn) {

  sb4 r;

  r = OCIStmtFetch(
        sh, 
        conn->err, 
        (ub4) 1, 
        (ub4) OCI_FETCH_NEXT,
        (ub4) OCI_DEFAULT);

  if (r == OCI_SUCCESS) {
    return 1;
  }
  else if (r == OCI_SUCCESS_WITH_INFO) {
    return 1;
  }
  else {
    if (r != OCI_NO_DATA) {
      checkerr(conn->err, r, errmsg);
      return 0;
    }
    return 0;
  }
}

// Metalink note 125057.1
int oci_describe(
           OCIStmt*            sh,
/*         char*               errmsg, */
    struct oci_connection*     conn,
    struct oci_description*    descr,
           int                 pos) {


  text*     colName;
  OCIParam* param = 0;
  ub4       len;

  sb4 status;

  status = OCIParamGet(sh, OCI_HTYPE_STMT, conn->err,  (void**)&param, (ub4) pos);

  if (status == OCI_SUCCESS) {
    len = sizeof(sb2);
    OCIAttrGet((dvoid*)param, (ub4) OCI_DTYPE_PARAM, (dvoid*) &(descr->col_type), &len, (ub4) OCI_ATTR_DATA_TYPE, conn->err);
    len = sizeof(sb4);
    OCIAttrGet((dvoid*)param, (ub4) OCI_DTYPE_PARAM, (dvoid**)&colName          , &len, (ub4) OCI_ATTR_NAME     , conn->err);
    //printf("len: %d\n",len);
    //descr->col_name[len]=0;
    memcpy(descr->col_name, colName, len);
    descr->col_name[len]=0;
    return 1;
  }
  else {
    return 0;
  }
}

int oci_commit(struct oci_connection* conn, char* errmsg) {
  sb4 r;
  if ((r=OCITransCommit(conn->svc, conn->err, 0))) {
    checkerr(conn->err, r, errmsg);
    return 0;
  }
  return 1;
}

