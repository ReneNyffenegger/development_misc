import javax.swing.*;

public class SimpleOptionPane extends JFrame {

       public static void main(String args[]) {
              new SimpleOptionPane();
       }
   
       SimpleOptionPane() {

              super("Top Level Window");

              setSize(300, 100);
              setDefaultCloseOperation(EXIT_ON_CLOSE);
              setVisible(true);

              JOptionPane.showMessageDialog(this, "Hello Ecosystem from JOptionPane");
       }
}
