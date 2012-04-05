//     javac    -cp    .;jansi-1.8.jar    getch.java
//     java     -cp    .;jansi-1.8.jar    getch
//
import org.fusesource.jansi.internal.WindowsSupport;


public class getch         {
public static void main    (
       String              [  
                           ] 
                           _
                           )
                           { int c = 0              ; while   ( c != 32 )
                           {     c = WindowsSupport . readByte(         ) // Calls _getch :-)
                           ;         System.out     . println (   c     )
                           ; 
                           }
                           }
                           }
