import javax.swing.JEditorPane;
import javax.swing.JFrame;

class GeneratedHTML {

      private static JEditorPane htmlPane;
      private static JFrame      window;

      private static String generateHTML() throws Exception {

              StringBuffer htmlTxt = new StringBuffer();

              htmlTxt . append ("<html>                         ");
              htmlTxt . append (" <head>                        ");
              htmlTxt . append ("  <title>Generated HTML</title>");
              htmlTxt . append (" </head>                       ");
              htmlTxt . append (" <body>                        ");
              htmlTxt . append (" <b>This was generated!</b>    ");
              htmlTxt . append (" </body>                       ");

              return htmlTxt.toString();
      }


      private static void InitWindow()    {
              window = new JFrame("Display generated HTML");
              window . setSize(300, 300);
              window . setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
      }


      private static void InitHtmlPane() throws Exception {

              htmlPane = new JEditorPane();
              htmlPane . setContentType("text/html");
              htmlPane . setText       (generateHTML() );
              htmlPane . setEditable   (false);
      }

      public  static void main(String[]_) throws Exception {

              InitWindow     ();
              InitHtmlPane   ();

              window . getContentPane() . add( htmlPane );
              window . setVisible (true);

      }
}
