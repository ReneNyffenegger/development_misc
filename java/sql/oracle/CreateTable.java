import java.sql.*;
class CreateTable {

  public static void main (String[] args) throws Exception {

     Connection conn = ConnectionCreator.Do(args);
  
     Statement stmt = conn.createStatement();
     stmt.executeUpdate("create table tq84_testy_testy(col_vc varchar2(10), col_n number, col_dt date)");

     stmt.close();
     conn.close();
  }
}
