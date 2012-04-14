//
//     This example is basically the same as GeneratedHTML.java but with
//     hyperlink capabilities.
//

import javax.swing.JEditorPane;
import javax.swing.JFrame;
import javax.swing.event.HyperlinkListener;
import javax.swing.event.HyperlinkEvent;

class LinkClicked implements HyperlinkListener {

      public void hyperlinkUpdate(HyperlinkEvent event) {

         //  This is the method that will be invoked when
         //  a hyperlink is clicked.

             if (event.getEventType() == HyperlinkEvent.EventType.ACTIVATED) {

                 HtmlLinks.lastUrl = event.getDescription(); 
                 try {HtmlLinks.DrawContent(); } catch (Exception e) { }
             }
      }
}

class HtmlLinks {

      private static JEditorPane htmlPane;
      private static JFrame      window;

      static  String lastUrl  = "None";


      private static String generateHTML() throws Exception {

              StringBuffer htmlTxt = new StringBuffer();

              htmlTxt . append ("<html>                                    ");
              htmlTxt . append (" <head>                                   ");
              htmlTxt . append ("  <title>Generated HTML</title>           ");
              htmlTxt . append (" </head>                                  ");
              htmlTxt . append (" <body>                                   ");
              htmlTxt . append ("  Press <a href='link_1'>One</a><br>      ");
              htmlTxt . append ("  or <a href='link_2'>Two</a><br>         ");
              htmlTxt . append ("  or <a href='link_3'>Three</a>!<p>       ");
              htmlTxt . append ("  Last URL clicked: <b>" + lastUrl + "</b>");
              htmlTxt . append (" </body>                                  ");

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
              htmlPane . setEditable   (false);
      }

      static  void DrawContent() throws Exception {

         //   DrawContent is initially called on application
         //   startup (method main) and also by LinkClicked
         //   when a hyperlink is clicked.
              htmlPane . setText (generateHTML());
      }

      public  static void main(String[]_) throws Exception {

              InitWindow     ();
              InitHtmlPane   ();

              window . getContentPane() . add( htmlPane );
              window . setVisible (true);

         //   Create an instance of LinkClicked which implements the
         //   HyperlinkListener interface:
              LinkClicked linkClicked = new LinkClicked();

         //   Cause LinkClicked.hyperlinkUpdate to be invoked
         //   if a hyperlink is clicked:
              htmlPane . addHyperlinkListener(linkClicked);

              DrawContent();
      }
}
