import javax.swing.JFrame;
import java .awt  .Toolkit;
import java .awt  .Dimension;

public class SetWindowBounds extends JFrame {

       final  static int indent = 100;

       public static void main(String args[]) {
              new SetWindowBounds();
       }
   
       SetWindowBounds() {

              Dimension screenSize = Toolkit.getDefaultToolkit().getScreenSize();

              setBounds(indent, indent, screenSize.width - indent*2, screenSize.height - indent*2);

              setDefaultCloseOperation(EXIT_ON_CLOSE);
              setVisible(true);
       }
}
