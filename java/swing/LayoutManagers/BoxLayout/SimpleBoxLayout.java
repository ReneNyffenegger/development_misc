import javax.swing.*;
import java .awt  .*;
 
public class SimpleBoxLayout extends JFrame {

       static int labelCounter = 0;
     
       void   addLabel() {

              JLabel newLabel = new JLabel("Counter: " + labelCounter ++ );

              getContentPane().add(newLabel);
       }
        
       SimpleBoxLayout() {

              super("Simple Box Layout");

              setLayout(new BoxLayout(getContentPane(), BoxLayout.Y_AXIS));

              for (int q=0 ; q<20; q++) { 
                   addLabel();
              }

              pack();

              setDefaultCloseOperation(EXIT_ON_CLOSE);
              setVisible(true);
       }
        
       public static void main(String[] args) {
              new SimpleBoxLayout();
       }
}
