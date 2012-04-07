import javax.swing.JFrame;


public class Simplest {

       public static void main(String[]_) {

         //   Create a JFrame and display it

              JFrame frame = new JFrame("Simplest");

         //   If 'setSize' is ommited, the frame consists of
         //   a title bar and a small frame only.
              frame.setSize(300,300);

              frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
              frame.setVisible(true);
       }
}
