import java.sql.*;
class ConnectionCreator {

  static Connection Do(String[] params) throws Exception {

    Class.forName ("oracle.jdbc.OracleDriver");

    String username = params[0];
    String password = params[1];     
    String hostname = params[2];
    String dbport   = params[3];
    String dbname   = params[4];

    Connection conn = DriverManager.getConnection( "jdbc:oracle:thin:@//" + hostname + ":" + dbport + "/" + dbname,
                                                     username,                                                    
                                                     password);


    return conn;
  } 

};
