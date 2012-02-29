#include <string.h>
#include <stdio.h>
#include "sqlite3.h"

sqlite3* db;

int first_row;

int select_callback(void *p_data, int num_fields, char **p_fields, char **p_col_names) {

  int field;
  int i;
  int *p_rn = (int*)p_data;

  if (first_row) {
    first_row = 0;

    // This is the first row, so we print
    // a header with 
    //  
    //   The column names ....
    for(field=0; field < num_fields; field++) {
      printf("  %20s", p_col_names[field]);
    }

    printf("\n");

    //  ... and underline these column names:
    for(field=0; field<num_fields; field++) {
      printf("  ");
      for (i=0; i<20; i++) {
        printf("=");
      }
    }
    printf("\n");
  }

  (*p_rn)++;

  for(i=0; i < num_fields; i++) {
    printf("  %20s", p_fields[i]);
  }

  printf("\n");
  return 0;
}

void select_stmt(const char* stmt) {
  char *errmsg;
  int   ret;
  int   nrecs = 0;

  first_row = 1;

  ret = sqlite3_exec(db, stmt, select_callback, &nrecs, &errmsg);

  if(ret!=SQLITE_OK) {
    printf("Error in select statement %s [%s].\n", stmt, errmsg);
  }
  else {
    printf("\n    %d records returned.\n", nrecs);
  }
}

void sql_stmt(const char* stmt) {
  char *errmsg;
  int   ret;

  ret = sqlite3_exec(db, stmt, 0, 0, &errmsg);

  if(ret != SQLITE_OK) {
    printf("Error in statement: %s [%s].\n", stmt, errmsg);
  }
}

void insert_countries() {
  sql_stmt("begin");
  sql_stmt("insert into countries values ('Afghanistan'                   ,  251826,   22664136)");
  sql_stmt("insert into countries values ('Albania'                       ,   11100,    3249136)");
  sql_stmt("insert into countries values ('Algeria'                       ,  919595,   29183032)");
  sql_stmt("insert into countries values ('Andorra'                       ,     175,      67509)");
  sql_stmt("insert into countries values ('Angola'                        ,  481354,   10342899)");
  sql_stmt("insert into countries values ('Argentina'                     , 1073400,   34672997)");
  sql_stmt("insert into countries values ('Armenia'                       ,   11506,    3463574)");
  sql_stmt("insert into countries values ('Australia'                     , 2966155,   18260863)");
  sql_stmt("insert into countries values ('Austria'                       ,   32377,    8013614)");
  sql_stmt("insert into countries values ('Azerbaijan'                    ,   33436,    7676953)");
  sql_stmt("insert into countries values ('Bahrain'                       ,     267,     590042)");
  sql_stmt("insert into countries values ('Bangladesh'                    ,   55598,  123062800)");
  sql_stmt("insert into countries values ('Barbados'                      ,     166,     257030)");
  sql_stmt("insert into countries values ('Belarus'                       ,   80155,   10415973)");
  sql_stmt("insert into countries values ('Belgium'                       ,   11783,   10131863)");
  sql_stmt("insert into countries values ('Belize'                        ,    8866,     219296)");
  sql_stmt("insert into countries values ('Benin'                         ,   43475,    5709529)");
  sql_stmt("insert into countries values ('Bhutan'                        ,   18200,    1822625)");
  sql_stmt("insert into countries values ('Bolivia'                       ,  424165,    7165257)");
  sql_stmt("insert into countries values ('Bosnia-Herzegovina'            ,   19741,    2656240)");
  sql_stmt("insert into countries values ('Botswana'                      ,  231800,    1477630)");
  sql_stmt("insert into countries values ('Brazil'                        , 3286488,  162661214)");
  sql_stmt("insert into countries values ('Brunei'                        ,    2226,     299939)");
  sql_stmt("insert into countries values ('Bulgaria'                      ,   42823,    8612757)");
  sql_stmt("insert into countries values ('Burkina Faso'                  ,  105869,   10623323)");
  sql_stmt("insert into countries values ('Burundi'                       ,   10745,    5943057)");
  sql_stmt("insert into countries values ('Cambodia'                      ,   69898,   10600000)");
  sql_stmt("insert into countries values ('Cameroon'                      ,  183569,   14261557)");
  sql_stmt("insert into countries values ('Canada'                        , 3849674,   29857369)");
  sql_stmt("insert into countries values ('Cape Verde'                    ,    1557,     449066)");
  sql_stmt("insert into countries values ('Central African Republic'      ,  240535,    3274426)");
  sql_stmt("insert into countries values ('Chad'                          ,  495755,    6976845)");
  sql_stmt("insert into countries values ('Chile'                         ,  292135,   14333258)");
  sql_stmt("insert into countries values ('China'                         , 3689631, 1210004956)");
  sql_stmt("insert into countries values ('Colombia'                      ,  440831,   36813161)");
  sql_stmt("insert into countries values ('Comoros'                       ,     863,     569237)");
  sql_stmt("insert into countries values ('Congo(Zaire)'                  ,  905446,   46498539)");
  sql_stmt("insert into countries values ('Congo Republic'                ,  132047,    2527841)");
  sql_stmt("insert into countries values ('Costa Rica'                    ,   19730,    3463083)");
  sql_stmt("insert into countries values ('Croatia'                       ,   21829,    5004112)");
  sql_stmt("insert into countries values ('Cuba'                          ,   42804,   11007446)");
  sql_stmt("insert into countries values ('Cyprus'                        ,    3593,     736636)");
  sql_stmt("insert into countries values ('Czech Republic'                ,   30613,   10321120)");
  sql_stmt("insert into countries values ('Denmark'                       ,   16638,    5210833)");
  sql_stmt("insert into countries values ('Djibouti'                      ,    8958,     427642)");
  sql_stmt("insert into countries values ('Dominica'                      ,     305,      82926)");
  sql_stmt("insert into countries values ('Dominican Republic'            ,   18704,    8088881)");
  sql_stmt("insert into countries values ('Ecuador'                       ,  109484,   11466291)");
  sql_stmt("insert into countries values ('Egypt'                         ,  386662,   65375107)");
  sql_stmt("insert into countries values ('El Salvador'                   ,    8124,    5828987)");
  sql_stmt("insert into countries values ('Equatorial Guinea'             ,   10831,     431282)");
  sql_stmt("insert into countries values ('Eritrea'                       ,   45300,    3909628)");
  sql_stmt("insert into countries values ('Estonia'                       ,   17413,    1459428)");
  sql_stmt("insert into countries values ('Ethiopia'                      ,  483123,   57171682)");
  sql_stmt("insert into countries values ('Fiji'                          ,    7078,     782381)");
  sql_stmt("insert into countries values ('Finland'                       ,  130559,    5100213)");
  sql_stmt("insert into countries values ('France'                        ,  211208,   58317450)");
  sql_stmt("insert into countries values ('Gabon'                         ,  103347,    1172798)");
  sql_stmt("insert into countries values ('Gambia'                        ,    4127,    1020178)");
  sql_stmt("insert into countries values ('Georgia'                       ,   26911,    5219810)");
  sql_stmt("insert into countries values ('Germany'                       ,  137882,   83536115)");
  sql_stmt("insert into countries values ('Ghana'                         ,   92098,   17698271)");
  sql_stmt("insert into countries values ('Greece'                        ,   50962,   10718518)");
  sql_stmt("insert into countries values ('Grenada'                       ,     133,      94961)");
  sql_stmt("insert into countries values ('Guatemala'                     ,   42042,   11177614)");
  sql_stmt("insert into countries values ('Guinea'                        ,   94926,    7411981)");
  sql_stmt("insert into countries values ('Guinea-Bissau'                 ,   13948,    1151330)");
  sql_stmt("insert into countries values ('Guyana'                        ,   83000,     712091)");
  sql_stmt("insert into countries values ('Haiti'                         ,   10714,    6731539)");
  sql_stmt("insert into countries values ('Honduras'                      ,   43277,    5605193)");
  sql_stmt("insert into countries values ('Hungary'                       ,   35920,   10002541)");
  sql_stmt("insert into countries values ('Iceland'                       ,   36769,     268369)");
  sql_stmt("insert into countries values ('India'                         , 1237062,  952107694)");
  sql_stmt("insert into countries values ('Indonesia'                     ,  742410,  206611600)");
  sql_stmt("insert into countries values ('Iran'                          ,  632457,   66094264)");
  sql_stmt("insert into countries values ('Iraq'                          ,  169235,   21422292)");
  sql_stmt("insert into countries values ('Ireland'                       ,   27137,    3562902)");
  sql_stmt("insert into countries values ('Israel'                        ,    8019,    5215022)");
  sql_stmt("insert into countries values ('Italy'                         ,  116234,   57460274)");
  sql_stmt("insert into countries values ('Ivory Coast'                   ,  124518,   14762445)");
  sql_stmt("insert into countries values ('Jamaica'                       ,    4244,    2593918)");
  sql_stmt("insert into countries values ('Japan'                         ,  145870,  125568504)");
  sql_stmt("insert into countries values ('Jordan'                        ,   35135,    4212152)");
  sql_stmt("insert into countries values ('Kazakhstan'                    , 1049156,   16916463)");
  sql_stmt("insert into countries values ('Kenya'                         ,  224961,   28176686)");
  sql_stmt("insert into countries values ('KoreaNorth'                    ,   46540,   23904124)");
  sql_stmt("insert into countries values ('KoreaSouth'                    ,   38230,   45482291)");
  sql_stmt("insert into countries values ('Kuwait'                        ,    6880,    1950047)");
  sql_stmt("insert into countries values ('Kyrgyzstan'                    ,   76641,    4529648)");
  sql_stmt("insert into countries values ('Laos'                          ,   91429,    4905772)");
  sql_stmt("insert into countries values ('Latvia'                        ,   24595,    2468982)");
  sql_stmt("insert into countries values ('Lebanon'                       ,    4015,    3776317)");
  sql_stmt("insert into countries values ('Lesotho'                       ,   11720,    1970781)");
  sql_stmt("insert into countries values ('Liberia'                       ,   38250,    2109789)");
  sql_stmt("insert into countries values ('Libya'                         ,  679362,    5445436)");
  sql_stmt("insert into countries values ('Liechtenstein'                 ,      62,      31011)");
  sql_stmt("insert into countries values ('Lithuania'                     ,   25174,    3718000)");
  sql_stmt("insert into countries values ('Luxembourg'                    ,     998,     406901)");
  sql_stmt("insert into countries values ('Macedonia'                     ,    9928,    2104035)");
  sql_stmt("insert into countries values ('Madagascar'                    ,  226658,   13670507)");
  sql_stmt("insert into countries values ('Malawi'                        ,   45747,    9542844)");
  sql_stmt("insert into countries values ('Malaysia'                      ,  129251,   19962893)");
  sql_stmt("insert into countries values ('Maldives'                      ,     115,     270758)");
  sql_stmt("insert into countries values ('Mali'                          ,  478767,    9653261)");
  sql_stmt("insert into countries values ('Malta'                         ,     122,     372314)");
  sql_stmt("insert into countries values ('Mauritania'                    ,  395956,    2336048)");
  sql_stmt("insert into countries values ('Mauritius'                     ,     788,    1139047)");
  sql_stmt("insert into countries values ('Mexico'                        ,  756066,   95772462)");
  sql_stmt("insert into countries values ('Micronesia'                    ,     271,     125377)");
  sql_stmt("insert into countries values ('Moldova'                       ,   13012,    4463847)");
  sql_stmt("insert into countries values ('Mongolia'                      ,  604829,    2496617)");
  sql_stmt("insert into countries values ('Morocco'                       ,  275114,   29779156)");
  sql_stmt("insert into countries values ('Mozambique'                    ,  308642,   17877927)");
  sql_stmt("insert into countries values ('Myanmar (Burma)'               ,  261228,   49975625)");
  sql_stmt("insert into countries values ('Namibia'                       ,  317818,    1677243)");
  sql_stmt("insert into countries values ('Nepal'                         ,   56827,   22094033)");
  sql_stmt("insert into countries values ('Netherlands'                   ,   16133,   15531940)");
  sql_stmt("insert into countries values ('New Zealand'                   ,  103519,    3547983)");
  sql_stmt("insert into countries values ('Nicaragua'                     ,   50054,    4272352)");
  sql_stmt("insert into countries values ('Niger'                         ,  489191,    9113001)");
  sql_stmt("insert into countries values ('Nigeria'                       ,  356669,  103912489)");
  sql_stmt("insert into countries values ('Norway'                        ,  125050,    4345941)");
  sql_stmt("insert into countries values ('Oman'                          ,   82030,    2186548)");
  sql_stmt("insert into countries values ('Pakistan'                      ,  310432,  129275660)");
  sql_stmt("insert into countries values ('Panama'                        ,   29157,    2655094)");
  sql_stmt("insert into countries values ('Papua New Guinea'              ,  178704,    4394537)");
  sql_stmt("insert into countries values ('Paraguay'                      ,  157048,    5504146)");
  sql_stmt("insert into countries values ('Peru'                          ,  496225,   24523408)");
  sql_stmt("insert into countries values ('Philippines'                   ,  115831,   74480848)");
  sql_stmt("insert into countries values ('Poland'                        ,  120728,   38642565)");
  sql_stmt("insert into countries values ('Portugal'                      ,   35516,    9865114)");
  sql_stmt("insert into countries values ('Qatar'                         ,    4416,     547761)");
  sql_stmt("insert into countries values ('Romania'                       ,   91699,   21657162)");
  sql_stmt("insert into countries values ('Russia'                        , 6592849,  148190419)");
  sql_stmt("insert into countries values ('Rwanda'                        ,   10169,    6853359)");
  sql_stmt("insert into countries values ('St. Kitts and Nevis'           ,     104,      41369)");
  sql_stmt("insert into countries values ('St. Lucia'                     ,     238,     157862)");
  sql_stmt("insert into countries values ('St. Vincent/Grenadines'        ,     150,     118344)");
  sql_stmt("insert into countries values ('S�o Tomé and Principe'         ,     372,     144128)");
  sql_stmt("insert into countries values ('Saudi Arabia '                 ,  830000,   19409058)");
  sql_stmt("insert into countries values ('Senegal'                       ,   75951,    9092749)");
  sql_stmt("insert into countries values ('Seychelles'                    ,     175,      77575)");
  sql_stmt("insert into countries values ('Sierra Leone'                  ,   27925,    4793121)");
  sql_stmt("insert into countries values ('Singapore'                     ,     246,    3396924)");
  sql_stmt("insert into countries values ('Slovakia'                      ,   18933,    5374362)");
  sql_stmt("insert into countries values ('Slovenia'                      ,    7819,    1951433)");
  sql_stmt("insert into countries values ('Solomon Islands'               ,   10954,     412902)");
  sql_stmt("insert into countries values ('Somalia'                       ,  246201,    9369151)");
  sql_stmt("insert into countries values ('South Africa'                  ,  433680,   41743459)");
  sql_stmt("insert into countries values ('Spain'                         ,  194885,   38853397)");
  sql_stmt("insert into countries values ('Sri Lanka'                     ,   24962,   18553074)");
  sql_stmt("insert into countries values ('Sudan'                         ,  967500,   31065229)");
  sql_stmt("insert into countries values ('Suriname'                      ,   63251,     436418)");
  sql_stmt("insert into countries values ('Swaziland'                     ,    6704,     998730)");
  sql_stmt("insert into countries values ('Sweden'                        ,  173732,    8861270)");
  sql_stmt("insert into countries values ('Switzerland'                   ,   15943,    7124745)");
  sql_stmt("insert into countries values ('Syria'                         ,   71498,   15608648)");
  sql_stmt("insert into countries values ('Taiwan'                        ,   13900,   21304000)");
  sql_stmt("insert into countries values ('Tajikistan'                    ,   55251,    5916373)");
  sql_stmt("insert into countries values ('Tanzania'                      ,  364900,   29058470)");
  sql_stmt("insert into countries values ('Thailand'                      ,  198115,   58851357)");
  sql_stmt("insert into countries values ('Togo'                          ,   21925,    4570530)");
  sql_stmt("insert into countries values ('Trinidad and Tobago'           ,    1980,    1272385)");
  sql_stmt("insert into countries values ('Tunisia'                       ,   63170,    9019687)");
  sql_stmt("insert into countries values ('Turkey'                        ,  300948,   62484478)");
  sql_stmt("insert into countries values ('Turkmenistan'                  ,  188456,    4149263)");
  sql_stmt("insert into countries values ('Uganda'                        ,   93104,   20158176)");
  sql_stmt("insert into countries values ('Ukraine'                       ,  233090,   50864009)");
  sql_stmt("insert into countries values ('United Arab Emirates'          ,   32278,    3057337)");
  sql_stmt("insert into countries values ('United Kingdom'                ,   94248,   58489975)");
  sql_stmt("insert into countries values ('United States'                 , 3787425,  265089998)");
  sql_stmt("insert into countries values ('Uruguay'                       ,   68500,    3238952)");
  sql_stmt("insert into countries values ('Uzbekistan'                    ,  172742,   23418381)");
  sql_stmt("insert into countries values ('Venezuela'                     ,  352145,   21983188)");
  sql_stmt("insert into countries values ('Vietnam'                       ,  128066,   73976973)");
  sql_stmt("insert into countries values ('Yemen'                         ,  205356,   13483178)");
  sql_stmt("insert into countries values ('Yugoslavia (Serbia-Montenegro)',   26913,   10611558)");
  sql_stmt("insert into countries values ('Zambia'                        ,  290586,    9159072)");
  sql_stmt("insert into countries values ('Zimbabwe'                      ,  150873,   11271314)");
  sql_stmt("commit");
}

int main() {
  sqlite3_open("./countries.db", &db);

  if(db == 0) {
    printf("Could not open database.");
    return 1;
  }

  sql_stmt("create table countries (country_name, size_sq_miles, population)");

  insert_countries();

  printf("\n\nSelecting the countries with the largest population:\n\n");
  select_stmt("select * from countries order by population desc limit 5");

  printf("\n\nSelecting the countries with the smallest population:\n\n");
  select_stmt("select * from countries order by population  asc limit 5");

  printf("\n\nSelecting the countries with the largest area:\n\n");
  select_stmt("select * from countries order by size_sq_miles desc limit 5");

  printf("\n\nSelecting the countries with the smallest area:\n\n");
  select_stmt("select * from countries order by size_sq_miles  asc limit 5");

  sqlite3_close(db);
  return 0;
}
