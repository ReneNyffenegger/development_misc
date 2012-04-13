import javax.swing.*;
import java .awt  .*;
 
public class SimpleBorderLayout extends JFrame {
     
       void   addButton(String where) {

              JButton newButton = new JButton("I am " + where);

              getContentPane().add(newButton, where);
       }
        
       SimpleBorderLayout() {

              super("Simple Border Layout");


         //   BorderLayout is the default, so the
         //   following call is technically not necessary.
         //   But it doesn't hurt, for clarity's sake:
              setLayout(new BorderLayout());

              addButton(BorderLayout.PAGE_START);
              addButton(BorderLayout.CENTER    );
              addButton(BorderLayout.LINE_START);
              addButton(BorderLayout.PAGE_END  );
              addButton(BorderLayout.LINE_END  );

              pack();

              setDefaultCloseOperation(EXIT_ON_CLOSE);
              setVisible(true);
       }
        
       public static void main(String[] args) {
              new SimpleBorderLayout();
       }
}
