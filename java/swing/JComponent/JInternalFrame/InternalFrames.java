import javax.swing.JInternalFrame;
import javax.swing.JDesktopPane;
import javax.swing.JMenu;
import javax.swing.JMenuItem;
import javax.swing.JMenuBar;
import javax.swing.JFrame;
import javax.swing.KeyStroke;

import java.awt.event.*;
import java.awt.*;


class SubFrame extends JInternalFrame {
  //
  //   This is the 'SubFrame' which will be created a few times
  //
       static int openedCounter = 0;

       public SubFrame(boolean resizable, boolean closable, boolean maximizable, boolean iconifiable) {

              super("This is Sub-Frame " + (++openedCounter), 
                     resizable,
                     closable,
                     maximizable,
                     iconifiable);
   
              setSize(100, 80);
              setVisible(true);
   
              setLocation(20 + openedCounter * 10, 20 + openedCounter * 17);
       }
}

public class InternalFrames extends JFrame {

       InternalFrames() {
              super("Internal Frames");

              desktopPane = new JDesktopPane();
              setSize(400, 400);

              createSubFrames();
              setContentPane(desktopPane);


              setDefaultCloseOperation(EXIT_ON_CLOSE);
              setVisible(true);
       }

       void   createSubFrames() {

              for (int i=0 ; i<16; i++) {
                   SubFrame subFrame = new SubFrame((i&1)>0, (i&2)>0, (i&4)>0, (i&8)>0);
                   desktopPane.add(subFrame);
              }

       }

       public static void main(String args[]) {
              new InternalFrames();
       }

   //  The 'desktop' onto which the SubFrame's will be placed.
       JDesktopPane desktopPane;

   //  ----------------------------------------------------------------------------

}


//public class InternalFrameDemo extends JFrame
//                               implements ActionListener {
//    JDesktopPane desktop;
//
//    public InternalFrameDemo() {
//
//
//        //Set up the GUI.
//        desktop = new JDesktopPane(); //a specialized layered pane
//        createFrame(); //create first "window"
//        setContentPane(desktop);
//        setJMenuBar(createMenuBar());
//
//        //Make dragging a little faster but perhaps uglier.
//        desktop.setDragMode(JDesktopPane.OUTLINE_DRAG_MODE);
//    }
//
//    protected JMenuBar createMenuBar() {
//        JMenuBar menuBar = new JMenuBar();
//
//        //Set up the lone menu.
//        JMenu menu = new JMenu("Document");
//        menu.setMnemonic(KeyEvent.VK_D);
//        menuBar.add(menu);
//
//        //Set up the first menu item.
//        JMenuItem menuItem = new JMenuItem("New");
//        menuItem.setMnemonic(KeyEvent.VK_N);
//        menuItem.setAccelerator(KeyStroke.getKeyStroke(
//                KeyEvent.VK_N, ActionEvent.ALT_MASK));
//        menuItem.setActionCommand("new");
//        menuItem.addActionListener(this);
//        menu.add(menuItem);
//
//        //Set up the second menu item.
//        menuItem = new JMenuItem("Quit");
//        menuItem.setMnemonic(KeyEvent.VK_Q);
//        menuItem.setAccelerator(KeyStroke.getKeyStroke(
//                KeyEvent.VK_Q, ActionEvent.ALT_MASK));
//        menuItem.setActionCommand("quit");
//        menuItem.addActionListener(this);
//        menu.add(menuItem);
//
//        return menuBar;
//    }
//
//    //React to menu selections.
//    public void actionPerformed(ActionEvent e) {
//        if ("new".equals(e.getActionCommand())) { //new
//            createFrame();
//        } else { //quit
//            quit();
//        }
//    }
//
//    //Create a new internal frame.
//    protected void createFrame() {
//        SubFrame frame = new SubFrame();
//        frame.setVisible(true); //necessary as of 1.3
//        desktop.add(frame);
//        try {
//            frame.setSelected(true);
//        } catch (java.beans.PropertyVetoException e) {}
//    }
//
//    //Quit the application.
//    protected void quit() {
//        System.exit(0);
//    }
//
//    /**
//     * Create the GUI and show it.  For thread safety,
//     * this method should be invoked from the
//     * event-dispatching thread.
//     */
//    private static void createAndShowGUI() {
//        //Make sure we have nice window decorations.
//        JFrame.setDefaultLookAndFeelDecorated(true);
//
//        //Create and set up the window.
//        InternalFrameDemo frame = new InternalFrameDemo();
//        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
//
//        //Display the window.
//        frame.setVisible(true);
//    }
//
//    public static void main(String[] args) {
//        //Schedule a job for the event-dispatching thread:
//        //creating and showing this application's GUI.
//        javax.swing.SwingUtilities.invokeLater(new Runnable() {
//            public void run() {
//                createAndShowGUI();
//            }
//        });
//    }
//}
