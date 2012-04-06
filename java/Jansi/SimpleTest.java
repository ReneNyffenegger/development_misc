import org.fusesource.jansi.AnsiConsole;
import org.fusesource.jansi.Ansi.Color;

//
//  http://jansi.fusesource.org/download.html
//
//  javac -cp .;jansi-1.8.jar SimpleTest.java
//  java  -cp .;jansi-1.8.jar SimpleTest

public class SimpleTest {

  static final String esc = "\u001b";

  static final String ansi_CLS               = esc + "[2J";
  static final String ansi_HOME              = esc + "[H";
  static final String ansi_NORMAL            = esc + "[0m";

  // 30-37 are the 'codes' for the colors.
  //
  //  1 is ATTRIBUTE_INTENSITY_BOLD,
  // 22 is ATTRIBUTE_INTENSITY_NORMAL,
  //  4 is ATTRIBUTE_UNDERLINE           and
  // 24 is ATTRIBUTE_UNDERLINE_OFF
  //      (See https://raw.github.com/fusesource/jansi/master/jansi/src/main/java/org/fusesource/jansi/AnsiOutputStream.java)
  //
  //  WindowsAnsiOutputStream.java (https://raw.github.com/fusesource/jansi/master/jansi/src/main/java/org/fusesource/jansi/WindowsAnsiOutputStream.java)
  //  renders the 'Underline Codes' by setting or clearing the 'BACKGROUND_INTENSITY' Byte,
  //  and the 'Bold/Normal' Code by setting the 'FOREGROUND_INTENSITY' Byte.
  //

  static final String ansi_FG_BLACK_DULL     = esc + "[30;22m";
  static final String ansi_FG_RED_DULL       = esc + "[31;22m";
  static final String ansi_FG_GREEN_DULL     = esc + "[32;22m";
  static final String ansi_FG_YELLOW_DULL    = esc + "[33;22m";
  static final String ansi_FG_BLUE_DULL      = esc + "[34;22m";
  static final String ansi_FG_MAGENTA_DULL   = esc + "[35;22m";
  static final String ansi_FG_CYAN_DULL      = esc + "[36;22m";
  static final String ansi_FG_WHITE_DULL     = esc + "[37;22m";

  static final String ansi_BG_BLACK_DULL     = esc + "[40;24m";
  static final String ansi_BG_RED_DULL       = esc + "[41;24m";
  static final String ansi_BG_GREEN_DULL     = esc + "[42;24m";
  static final String ansi_BG_YELLOW_DULL    = esc + "[43;24m";
  static final String ansi_BG_BLUE_DULL      = esc + "[44;24m";
  static final String ansi_BG_MAGENTA_DULL   = esc + "[45;24m";
  static final String ansi_BG_CYAN_DULL      = esc + "[46;24m";
  static final String ansi_BG_WHITE_DULL     = esc + "[47;24m";

  static final String ansi_FG_BLACK_BRIGHT   = esc + "[30;1m";
  static final String ansi_FG_RED_BRIGHT     = esc + "[31;1m";
  static final String ansi_FG_GREEN_BRIGHT   = esc + "[32;1m";
  static final String ansi_FG_YELLOW_BRIGHT  = esc + "[33;1m";
  static final String ansi_FG_BLUE_BRIGHT    = esc + "[34;1m";
  static final String ansi_FG_MAGENTA_BRIGHT = esc + "[35;1m";
  static final String ansi_FG_CYAN_BRIGHT    = esc + "[36;1m";
  static final String ansi_FG_WHITE_BRIGHT   = esc + "[37;1m";

  static final String ansi_BG_BLACK_BRIGHT   = esc + "[40;4m";
  static final String ansi_BG_RED_BRIGHT     = esc + "[41;4m";
  static final String ansi_BG_GREEN_BRIGHT   = esc + "[42;4m";
  static final String ansi_BG_YELLOW_BRIGHT  = esc + "[43;4m";
  static final String ansi_BG_BLUE_BRIGHT    = esc + "[44;4m";
  static final String ansi_BG_MAGENTA_BRIGHT = esc + "[45;4m";
  static final String ansi_BG_CYAN_BRIGHT    = esc + "[46;4m";
  static final String ansi_BG_WHITE_BRIGHT   = esc + "[47;4m";

  static final String ansi_BLINK      = esc + "[5m";

  static final String ansi_REVERSE_ON = esc + "[7m";


  private static void moveTo(int x, int y, String s) {
    AnsiConsole.out.println(esc + "[" + y + ";" + x + "H" + s + ansi_NORMAL);
  }

  public static void main(String args[]){

    AnsiConsole.systemInstall();

    AnsiConsole.out.print(ansi_CLS + ansi_HOME);

    moveTo(20,10, ansi_BG_BLACK_DULL + ansi_FG_WHITE_BRIGHT + "Position 20/10");

    AnsiConsole.out.println(ansi_BG_RED_DULL + ansi_FG_YELLOW_BRIGHT + "Yellow on Red");

    AnsiConsole.out.println(ansi_BLINK + "Blink doesn't work.");

    AnsiConsole.out.println(ansi_BG_BLUE_BRIGHT + ansi_FG_WHITE_BRIGHT + ansi_REVERSE_ON + "Reverse White on Blue");

    moveTo(20,40, ansi_BG_RED_BRIGHT + "Bright red background");
    moveTo(20,41, ansi_BG_RED_DULL   + "  Dull red background");

    moveTo(20,43, ansi_BG_WHITE_DULL + ansi_FG_RED_BRIGHT + "Bright red foreground");
    moveTo(20,44, ansi_BG_WHITE_DULL + ansi_FG_RED_DULL   + "  Dull red foreground");

    AnsiConsole.out.println(ansi_BG_BLACK_DULL + ansi_FG_WHITE_BRIGHT + "ABCDEF");

  }
}
