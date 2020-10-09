import java.sql.*;

class SelectTable {

  public static void main (String[] args) throws Exception {

     Connection conn = ConnectionCreator.Do(args);
  
     PreparedStatement stmt = conn.prepareStatement("select col_vc, col_n, col_dt from tq84_testy_testy where col_n > ?");
     stmt.setDouble(1, 2.1);

     ResultSet rs = stmt.executeQuery();

     while (rs.next()) {
       System.out.println(rs.getString(1) + "\t" + rs.getDouble(2) + "\t" + rs.getDate(3));
     }

     stmt.close();
     conn.close();
  }
}
