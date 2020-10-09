import java.sql.*;

class MetaData {

      public static void main (String[] args) throws Exception {
    
             Connection conn = ConnectionCreator.Do(args);
          
             PreparedStatement stmt = conn.prepareStatement("select * from tq84_testy_testy");
             ResultSet         rs   = stmt.executeQuery    ();
             ResultSetMetaData meta = rs  .getMetaData     ();

             int nofColumns  = meta.getColumnCount();

             System.out.println("The table has " + nofColumns + " columns:");


             for (int actColumn = 1; actColumn <= nofColumns; actColumn++) {

             //   NOTE: the index are 1 based, not 0 based!
             //          Therefor, the for loop reads  for (... = 1; ... <= ...)
             //          instead of the more common    for (... = 0; ... <  ...)

                  System.out.println("  " +  actColumn  + ": " + 
                    
                    meta . getColumnName    (actColumn) + "\t" + 
                    meta . getColumnTypeName(actColumn)

                  );
             }
        
             stmt.close();
             conn.close();
      }
}
