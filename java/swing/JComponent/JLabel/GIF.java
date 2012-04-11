import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.ImageIcon;
import javax.swing.Icon;

public class GIF extends JFrame {

       public static void main(String args[]) {
              new GIF();
       }
   
       GIF() {
              
              Icon   gif   = new ImageIcon("blue2yellow.gif");
              JLabel label = new JLabel   ( gif             );
      
              add(label);
      
              this.setSize(100, 100);
              this.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
              this.setVisible(true);
       }
}
