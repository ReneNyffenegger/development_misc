import javax.swing.JFrame;
import javax.swing.JLabel;

public class Simplest extends JFrame {

       public static void main(String args[]) {
              new Simplest();
       }
   
       Simplest() {
              JLabel label = new JLabel("JLabel example");
      
              add(label); // pack(); not needed?
      
              this.setSize(100, 100);
              this.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
              this.setVisible(true);
       }
}
