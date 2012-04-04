import java.sql.*;
class DropTable {

  public static void main (String[] args) throws Exception {

     Connection conn = ConnectionCreator.Do(args);
  
     Statement stmt = conn.createStatement();
     stmt.executeUpdate("drop table tq84_testy_testy");

     stmt.close();
     conn.close();
  }
}
