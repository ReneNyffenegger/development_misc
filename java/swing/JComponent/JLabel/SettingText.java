import javax.swing.JFrame;
import javax.swing.JLabel;

public class SettingText extends JFrame {

       public static void main(String args[]) {
              new SettingText();
       }


       class  TextSettingThread implements Runnable {

              private JLabel label;

              TextSettingThread(JLabel label_) {
                     label = label_;
              }

              public void run() {

                     try {
                     
                     int counter = 0;

                     while (true) {

                            label.setText(Integer.toString(counter));

                            counter++;

                            Thread.sleep(1000);
                     }

                     } catch (InterruptedException _) {}
              }
       }
   
       SettingText() {
              
              JLabel label = new JLabel();
              add   (label);
      
              this.setSize(100, 100);
              this.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
              this.setVisible(true);

              Thread thread = new Thread(new TextSettingThread(label));
              thread.start();
       }
}
