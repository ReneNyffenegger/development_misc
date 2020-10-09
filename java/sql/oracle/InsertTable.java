import java.sql.*;

class InsertTable {

  public static void main (String[] args) throws Exception {

     Connection conn = ConnectionCreator.Do(args);
  
     PreparedStatement stmt = conn.prepareStatement("insert into tq84_testy_testy values(?,?,?)");

     stmt.setString     (1, "One");
     stmt.setInt        (2,    1 );
     stmt.setTimestamp  (3, Timestamp.valueOf("1970-08-28 00:00:00.0")); 
     stmt.execute();

     stmt.setString     (1, "Two");
     stmt.setDouble     (2,  2.2 );
     stmt.setTimestamp  (3, Timestamp.valueOf("2010-11-12 12:34:56.0"));
     stmt.execute();

     stmt.setString     (1, "Three");
     stmt.setDouble     (2,  3.3 );
     stmt.setTimestamp  (3,  null);
     stmt.execute();

     stmt.close();
     conn.close();
  }
}
