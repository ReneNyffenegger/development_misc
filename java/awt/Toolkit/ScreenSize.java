import java .awt  .*;
import javax.swing.*;

public class ScreenSize {


       static void createFrame(int width, int height) {

       //     See https://raw.github.com/ReneNyffenegger/development_misc/master/java/swing/JFrame/Simplest.java
       
              JFrame frame = new JFrame("Simplest");

              frame.setSize(width, height);

              frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
              frame.setVisible(true);

       }

       public static void main(String args[]) {

              Toolkit   tk  = Toolkit.getDefaultToolkit();
              Dimension dim = tk.getScreenSize();

              createFrame(dim.width, dim.height);
       }
}
