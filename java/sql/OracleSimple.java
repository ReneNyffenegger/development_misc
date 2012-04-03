//
//        javac OracleSimple.java
//
//        set JDBCJAR=%ORACLE_HOME%\jdbc\lib\ojdbc5.jar
//
//        java -cp ".;%JDBCJAR%"  OracleSimple  rene  rene  localhost 1521 ORA11R2
//
//
// ------------------------------------
import java.sql.*;
class OracleSimple {

  public static void main (String[] args) throws Exception {

     if (args.length < 4) {
         System.out.println("Expected parrameters:");
         System.out.println("  username  password  hostname  dbport  dbname");
         return;
     }

     Class.forName ("oracle.jdbc.OracleDriver");

     String username = args[0];
     String password = args[1];
     String hostname = args[2];
     String dbport   = args[3];
     String dbname   = args[4];
  
     Connection conn = DriverManager.getConnection( "jdbc:oracle:thin:@//" + hostname + ":" + dbport + "/" + dbname, 
                                                    username,
                                                    password );
  
     Statement stmt = conn.createStatement();
  
//   stmt.setFetchSize(1);
  
     ResultSet rset = stmt.executeQuery("select table_name from user_tables");
  
     while (rset.next())
       System.out.println (rset.getString(1)); 
    }
}
