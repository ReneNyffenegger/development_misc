import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.io.FileInputStream;

import javax.swing.*;
import javax.swing.table.*;
import java.awt.*;

import java.util.Vector;


public class  ScrollableTable {

       public static void main(String[]_) throws Exception {
             
              Vector<Vector<String>> tableData = readTXTFile("data.csv");

              Vector<String> header = new Vector<String>();

                             header.addElement("Col 1");
                             header.addElement("Col 2");
                             header.addElement("Col 3");
                             header.addElement("Col 4");


              JTable      table      = new JTable(tableData, header);
              JScrollPane scrollPane = new JScrollPane(table);
              JPanel      panel      = new JPanel(); 
              JFrame      frame      = new JFrame("Frame containing a JPanel");

//            table.setAutoResizeMode(JTable.AUTO_RESIZE_OFF);

              frame.setUndecorated(true); 
              frame.getRootPane().setWindowDecorationStyle(JRootPane.PLAIN_DIALOG);
              frame.setSize(500,250);
              frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);

              panel.add(scrollPane );
              frame.add(panel);

              frame.setVisible(true);
       }


       private static Vector<Vector<String>> readTXTFile(String csvFileName) throws Exception {

               BufferedReader stream = new BufferedReader(new InputStreamReader(new FileInputStream(csvFileName)));

               Vector<Vector<String>> csvData = new Vector<Vector<String>>();

               String line;
               while ((line = stream.readLine()) != null) {

                       csvData.add(new Vector<String>() );

                       String[] values = line.split(",");

                       for (int v=0; v<values.length; v++) {
                            csvData.get(csvData.size()-1).add(values[v]);
                       }
               }

               return csvData;
       }
}
