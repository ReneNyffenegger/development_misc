import javax.swing.      *;
import java .awt  .      *;
import java .awt  .event.*;

public class MenuBar01 extends JFrame {

       class MenuListener implements ActionListener {
             public void actionPerformed(ActionEvent e) {
                    JOptionPane.showMessageDialog(null , e.getActionCommand());
             }
       };

       MenuListener menuListener;

       void   createMenuBar(Object... o) {

              menuListener = new MenuListener(); 
              JMenuBar   menuBar      = new JMenuBar ();
              JMenu      menu         = new JMenu    ("To stay or to go?");
              JMenuItem  menuItemGo   = new JMenuItem("Go");
              JMenuItem  menuItemStay = new JMenuItem("Stay");


              menuItemGo  .addActionListener(menuListener);
              menuItemStay.addActionListener(menuListener);

              menu.add(menuItemGo);
              menu.add(menuItemStay);

              menuBar.add(menu);

              setJMenuBar(menuBar);
       }

       MenuBar01() {
              super("Hi!");

              createMenuBar();

              setDefaultCloseOperation(EXIT_ON_CLOSE);
              pack();
              setVisible(true);
       }

       public static void main(String args[]) {
              new MenuBar01();
       }
}
