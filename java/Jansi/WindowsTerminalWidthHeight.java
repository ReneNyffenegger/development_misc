//
//
//  javac -cp   jansi-1.8.jar  WindowsTerminalWidthHeight.java
//
//  java  -cp .;jansi-1.8.jar  WindowsTerminalWidthHeight
//
//


import static org.fusesource.jansi.internal.Kernel32.GetConsoleScreenBufferInfo;
import static org.fusesource.jansi.internal.Kernel32.GetStdHandle;
import static org.fusesource.jansi.internal.Kernel32.STD_OUTPUT_HANDLE;

import org.fusesource.jansi.internal.Kernel32.CONSOLE_SCREEN_BUFFER_INFO;
import org.fusesource.jansi.AnsiConsole;


public class WindowsTerminalWidthHeight {

  public static void main(String[] _) {

         long                       console_ = GetStdHandle(STD_OUTPUT_HANDLE);
         CONSOLE_SCREEN_BUFFER_INFO screen_  = new CONSOLE_SCREEN_BUFFER_INFO();

		     if (GetConsoleScreenBufferInfo(console_, screen_) == 0 ) {

             System.out.println("something went the other way, maybe even the wrong way.");
             return;
         }

         System.out.println   (                                                  );
         System.out.println   ("  .window.top:       " + screen_.window.top      );
         System.out.println   ("  .window.bottom:    " + screen_.window.bottom   );
         System.out.println   ("  .window.height():  " + screen_.window.height() );
         System.out.println   ("  .window.width ():  " + screen_.window.width () );
         System.out.println   ("  .size.x:           " + screen_.size.x          );
         System.out.println   ("  .size.y:           " + screen_.size.y          );
         System.out.println   ("  .cursorPosition.y: " + screen_.cursorPosition.y);
         System.out.println   ("  .cursorPosition.x: " + screen_.cursorPosition.x);
         System.out.println   (                                                  );

  }

}
