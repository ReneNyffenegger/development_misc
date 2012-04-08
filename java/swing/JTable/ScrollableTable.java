import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.io.FileInputStream;

import javax.swing.*;
import javax.swing.table.*;
import java.awt.*;

import java.util.Vector;


public class  ScrollableTable {

       public static void main(String[]_) throws Exception {
             
              Vector<Vector<String>> tableData = readCSVFile("data.csv");

              Vector<String> header = new Vector<String>();

                             header.addElement("Col 1");
                             header.addElement("Col 2");
                             header.addElement("Col 3");
                             header.addElement("Col 4");


         //   Create the 'JTable'. The following constructor makes
         //   every cell editable. If this is not desired, a
         //  'TableModel' must be implemented.
              JTable      table      = new JTable(tableData, header);

              JScrollPane scrollPane = new JScrollPane(table);

              JFrame      frame      = new JFrame("Frame containing a JPanel");

              frame.setUndecorated(true); 
              frame.getRootPane().setWindowDecorationStyle(JRootPane.PLAIN_DIALOG);
              frame.setSize(500,250);
              frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);

              frame.add(scrollPane);

              frame.setVisible(true);
       }


       private static Vector<Vector<String>> readCSVFile(String csvFileName) throws Exception {

         //    http://codereview.stackexchange.com/questions/10681/java-function-to-read-a-csv-file/10687#10687

               BufferedReader stream = new BufferedReader(new InputStreamReader(new FileInputStream(csvFileName)));

               Vector<Vector<String>> csvData = new Vector<Vector<String>>();

               String line;
               while ((line = stream.readLine()) != null) {

                       csvData.add(new Vector<String>() );

                       String[] splitted = line.split(",");

                       for (int v=0; v<splitted.length; v++) {
                            csvData.get(csvData.size()-1).add(values[v]);
                       }
               }

               stream.close();

               return csvData;
       }
}
