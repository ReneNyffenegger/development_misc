import java .awt  .      *;
import java .awt  .event.*;
import javax.swing.      *;
 
class LoginDialog extends JDialog {
 
      private JTextField     txtUsername;
      private JPasswordField txtPassword;

      void   AddInGrid(GridBagConstraints cons, int x, int y, int width, JPanel panel, JComponent component) {
             cons.gridx     = x;
             cons.gridy     = y;
             cons.gridwidth = width;

             panel.add(component, cons);
      }

      JPanel createNamePasswordPanel() {

         //  This is the panel that demonstrats the GridBagLayout.
         //
         //  It places for components into a grid (See -> AddInGrid below),
         //  thus forcing them to be aligned.

         //  The two labels:
             JLabel lblUserName;
             JLabel lblPassWord;

         //  The text fields are members of the class since they need to be
         //  accessible in the ActionListener.

             JPanel panel = new JPanel(new GridBagLayout());
             GridBagConstraints cs = new GridBagConstraints();
   
             cs.fill = GridBagConstraints.HORIZONTAL;
   
             lblUserName = new JLabel("Username: ");
             lblPassWord = new JLabel("Password: ");
   
             txtUsername = new JTextField    (20)  ;
             txtPassword = new JPasswordField(20)  ;

             AddInGrid(cs, 0, 0, 1, panel, lblUserName);
             AddInGrid(cs, 0, 1, 1, panel, lblPassWord);
             AddInGrid(cs, 1, 0, 2, panel, txtUsername);
             AddInGrid(cs, 1, 1, 2, panel, txtPassword);

             return panel;
      }

      JPanel createOkCancelPanel    () {

             JButton btnLogin;
             JButton btnCancel;

             JPanel panel = new JPanel();

             btnLogin  = new JButton("Login" );
             btnCancel = new JButton("Cancel");
   
         //  ------------     Action listener for login button          --------------------
         
             btnLogin.addActionListener(new ActionListener() {

                      public void actionPerformed(ActionEvent e) {
  
                         //  Display the entered username and password.
                         //  getPassword returns a char[] that has to
                         //  be converted into a String, hence the new String(thingy).

                             JOptionPane.showMessageDialog(LoginDialog.this,
                                      "Usename is "  + txtUsername.getText    () + "\n" +
                                      "Password is " + new String(txtPassword.getPassword()),
                                      "Login",
                                      JOptionPane.INFORMATION_MESSAGE);
                      }
             });

         //  ------------     Action listener for cancel button        --------------------
             btnCancel.addActionListener(new ActionListener() {
   
                 public void actionPerformed(ActionEvent e) {
                     dispose();
                 }
             });
         //
         //  --------------------------------------------------------------------------------

             panel.add(btnLogin);
             panel.add(btnCancel);
   
             return panel;
      }

      public LoginDialog(Frame parent) {

             super(parent, "Login", true);

             JPanel namePasswordPanel = createNamePasswordPanel();
             JPanel okCancelPanel     = createOkCancelPanel    ();
   
             getContentPane().add(namePasswordPanel, BorderLayout.CENTER  );
             getContentPane().add(okCancelPanel    , BorderLayout.PAGE_END);
   
             pack();
             setResizable(false);
             setLocationRelativeTo(parent);
      }
   
}
 
public class SimpleLoginDialog extends JFrame {

       SimpleLoginDialog() {
              super("Using GridBagLayout for a Login Dialog");
              
              setSize(400, 200);

              setDefaultCloseOperation(EXIT_ON_CLOSE);
              setVisible(true);

              LoginDialog loginDlg = new LoginDialog(this);
              loginDlg.setVisible(true);
       }

       public static void main(String[] args) {
              new SimpleLoginDialog();
        }
}
