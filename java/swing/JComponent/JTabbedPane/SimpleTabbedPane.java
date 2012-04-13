import javax.swing.*;
import java .awt  .*;
 
public class SimpleTabbedPane extends JFrame {
               
       void  addTab(String text, JTabbedPane tabPane) {

             JPanel panel  = new JPanel(false);
             JLabel label  = new JLabel("Label: " + text);

             label.setHorizontalAlignment(JLabel.CENTER);

             panel.setLayout(new GridLayout(1, 1));
             panel.add(label);

             tabPane.addTab("Tab " + text, panel);
       }
        
        
       SimpleTabbedPane() {
             super("Simple Tabbed Pane");

             JTabbedPane tabPane = new JTabbedPane();

         //  Make tabs scrollable
             tabPane.setTabLayoutPolicy(JTabbedPane.SCROLL_TAB_LAYOUT);

             addTab("foo", tabPane);
             addTab("bar", tabPane);
             addTab("baz", tabPane);

             for (int q=1 ; q < 20; q++) {
                  addTab(Integer.toString(q), tabPane);
             }

             JPanel pane = new JPanel(new GridLayout(1, 1));
             pane.add(tabPane);
              
             
             add(pane, BorderLayout.CENTER);
              
             pack();

             setDefaultCloseOperation(EXIT_ON_CLOSE);
             setSize(400,100);
             setVisible(true);
       }
        
       public static void main(String[] args) {
              new SimpleTabbedPane();
       }
}
