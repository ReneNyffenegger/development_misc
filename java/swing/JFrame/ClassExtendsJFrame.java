import javax.swing.JFrame;

public class ClassExtendsJFrame extends JFrame {

       public static void main(String args[]) {
              new ClassExtendsJFrame();
       }
   
       ClassExtendsJFrame() {
              super("JFrame's title");

              setSize(100, 100);
              setDefaultCloseOperation(EXIT_ON_CLOSE);
              setVisible(true);
       }
}
