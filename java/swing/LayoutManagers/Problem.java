import javax.swing.*;

public class Problem extends JFrame {

       Problem() {
              setSize(200, 500);

           // Add five labels:

              addLabel("One"  );
              addLabel("Two"  );
              addLabel("Three");
              addLabel("Four" );
              addLabel("Five" );

           // The problem is: only the last one added is displayed.

              pack(); // Also try commenting 'pack()' out.

              setDefaultCloseOperation(EXIT_ON_CLOSE);
              setVisible(true);
       }

       public static void main(String args[]) {
              new Problem();
       }

       void   addLabel(String text) {

              JLabel label = new JLabel(text);
              getContentPane().add(label);
       }
}
