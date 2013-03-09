//
//     java OracleSimple {username} {password} jdbc:oracle:thin@//{SERVER}:{PORT}/{CONNECTION_IDENTIFIER}
//
import java.sql.*;

class OracleSimple {

      public static void main (String[] args) throws Exception {

             Class.forName ("oracle.jdbc.OracleDriver");
          
             Connection conn = DriverManager.getConnection(
                args[2] /* "jdbc:oracle:thin:@//localhost:1521/ORA_MANUALLY_CREATED" */,
                args[0] /* "rene"                                                    */, 
                args[1] /* "rene"                                                    */);
          
             Statement stmt = conn.createStatement();
          
             stmt.setFetchSize(1);
          
             ResultSet rset = stmt.executeQuery("select to_char(sysdate, 'dd.mm.yyyy hh24:mi:ss') s from dual");
          
             while (rset.next()) {
                    System.out.println (rset.getString(1)); 
}      }     }
