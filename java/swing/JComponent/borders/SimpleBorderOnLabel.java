import javax.swing.*;
import java .awt  .Color;

public class SimpleBorderOnLabel extends JFrame {

  //          Use a JPanel to draw the labels on, in order to circumvent
  //          the Problem outlined in ../../LayoutManagers/Problem.java
       JPanel content;

       SimpleBorderOnLabel() {
              setSize(200, 500);

              content = new JPanel();

              addLabelWithBorderColor(Color.BLACK ,  3);
              addLabelWithBorderColor(Color.ORANGE,  1);
              addLabelWithBorderColor(Color.BLUE  , 10);

              getContentPane().add(content);

              setDefaultCloseOperation(EXIT_ON_CLOSE);
              setVisible(true);
       }

       public static void main(String args[]) {
              new SimpleBorderOnLabel();
       }

       void   addLabelWithBorderColor(Color color, int thickness) {

              JLabel label = new JLabel(color.toString());
              label.setBorder(BorderFactory.createLineBorder(color, thickness));

              content.add(label);
       }
}
