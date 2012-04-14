import javax.swing.*;

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
}
