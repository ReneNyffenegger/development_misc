import javax.swing.      *;
import java .awt  .event.*;

public class WindowEventReceiver extends JFrame {

       WindowEventReceiver() {
              setSize(100, 100);
              addWindowListener(new WindowAdapter_());
              setDefaultCloseOperation(EXIT_ON_CLOSE);
              setVisible(true);
       }

       public static void main(String args[]) {
              new WindowEventReceiver();
       }
      

       class WindowAdapter_ extends WindowAdapter {

         //  Receive the desired events:

             public void windowOpened       (WindowEvent e) { System.out.println("Window opened."       ); }
             public void windowActivated    (WindowEvent e) { System.out.println("Window activated."    ); }
             public void windowDeactivated  (WindowEvent e) { System.out.println("Window deactivated."  ); }
             public void windowLostFocus    (WindowEvent e) { System.out.println("Window lost focus."   ); }
             public void windowGainedFocus  (WindowEvent e) { System.out.println("Window gained focus." ); }
             public void windowIconified    (WindowEvent e) { System.out.println("Window iconified."    ); }
             public void windowDeiconified  (WindowEvent e) { System.out.println("Window deiconified."  ); }
             public void windowStateChanged (WindowEvent e) { System.out.println("Window state changed."); }
             public void windowClosing      (WindowEvent e) { System.out.println("Window closing."      ); }
             public void windowClosed       (WindowEvent e) { System.out.println("Window closing."      ); }
      }
}
