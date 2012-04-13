import javax.swing.*;
import javax.swing.table.AbstractTableModel;
import java .util .Calendar;
import java .text .SimpleDateFormat;

public class DoesJTableCache extends JFrame {


       class  tableModel extends AbstractTableModel {

              public int getRowCount   () { return 1000000; }
              public int getColumnCount() { return       1; }

              SimpleDateFormat dateFormat;

              tableModel() {
                     dateFormat = new SimpleDateFormat("yyyy-MM-dd HH:mm:ss");
              }

              public Object getValueAt(int rowIndex, int columnIndex) {
                     return dateFormat.format(Calendar.getInstance().getTime());
              }

              public String getColumnName(int column) {
                     return "Time when getValueAt called";
              }

              public Class<?> getColumnClass(int columnIndex) {
                     return String.class.getClass();
              }
       }



       DoesJTableCache() {

              super("Test if a JTable caches the data");

              setSize (500, 500);

              JTable      table  = new JTable(new tableModel());
              JScrollPane scroll = new JScrollPane(table);

              table.setFillsViewportHeight(true);

              add(scroll);

              setDefaultCloseOperation(EXIT_ON_CLOSE);
              setVisible(true);

       }

       public static void main(String[]_) {
              new DoesJTableCache();
       }
}
