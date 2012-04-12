import javax.swing.*;
import javax.swing.table.AbstractTableModel;

public class SimpleAbstractTableModel extends JFrame {


       class  AbstractTableModel_ extends AbstractTableModel {

              public int getRowCount   () { return 4; }
              public int getColumnCount() { return 3; }

              public Object getValueAt(int rowIndex, int columnIndex) {
                     return (rowIndex+1) * (columnIndex+2);
              }

              public String getColumnName(int column) {
                     return "Col " + column;
              }

              public Class<?> getColumnClass(int columnIndex) {
                     return int.class.getClass();
              }
       }



       SimpleAbstractTableModel() {

              super("Simple AbstractTableModel example");

              setSize (500, 500);

              JTable table = new JTable(new AbstractTableModel_());
              table.setFillsViewportHeight(true);
              add(table);

              setDefaultCloseOperation(EXIT_ON_CLOSE);
              setVisible(true);

       }

       public static void main(String[]_) {
              new SimpleAbstractTableModel();
       }

}
