import javax.swing.      *;
import java .awt  .      *;
import java .awt  .event.*;

public class SimpleMenuBar extends JFrame {

       class MenuListener implements ActionListener {
             public void actionPerformed(ActionEvent e) {
                    JOptionPane.showMessageDialog(null , e.getActionCommand());
             }
       };

       MenuListener menuListener;

       SimpleMenuBar() {
         
              super("Simple Menu Bar");

              menuListener = new MenuListener();

              createMenuBar(
                       menu("Fruits" ,  'f',
                                      item("Apple"  , 'A'),
                                      item("Pear"   , 'P')
                       ),
                       menu("Numbers", 'n',
                                      item("One"    , 'O'),
                                      item("Two"    , 'T'),
                                      item("Three"  , 'H'),
                                      item("Four"   , 'F')
                       )
              );


              setDefaultCloseOperation(EXIT_ON_CLOSE);
              pack();
              setVisible(true);
       }

       void   createMenuBar(JMenu... menues) {

              JMenuBar menuBar      = new JMenuBar();

              for (JMenu menu: menues) {
                   menuBar . add(menu);
              }

              setJMenuBar(menuBar);
       }

       JMenu  menu(String text, char mnemonic, JMenuItem... menuItems) {

              JMenu newMenu = new JMenu(text);
  
              newMenu.setMnemonic(mnemonic);
  
              for (JMenuItem menuItem: menuItems) {
                   newMenu.add(menuItem);
              }
  
              return newMenu;
       }


       JMenuItem item(String text, char accelerator) {

              JMenuItem menuItem = new JMenuItem(text);

              menuItem . setAccelerator(KeyStroke.getKeyStroke(accelerator, Event.CTRL_MASK));
              menuItem . addActionListener(menuListener);

              return menuItem;
       }

       public static void main(String args[]) {
              new SimpleMenuBar();
       }
}
