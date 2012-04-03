import org.fusesource.jansi.AnsiConsole;
import org.fusesource.jansi.Ansi.Color;

//
//  http://jansi.fusesource.org/download.html
//
//  javac -cp .;jansi-1.8.jar SimpleTest.java
//  java  -cp .;jansi-1.8.jar SimpleTest

public class SimpleTest {

  static final String esc = "\u001b";

  static final String ansi_CLS        = esc + "[2J";
  static final String ansi_HOME       = esc + "[H";
  static final String ansi_NORMAL     = esc + "[0m";

  static final String ansi_FG_BLACK   = esc + "[30m";
  static final String ansi_FG_RED     = esc + "[31m";
  static final String ansi_FG_GREEN   = esc + "[32m";
  static final String ansi_FG_YELLOW  = esc + "[33m";
  static final String ansi_FG_BLUE    = esc + "[34m";
  static final String ansi_FG_MAGENTA = esc + "[35m";
  static final String ansi_FG_CYAN    = esc + "[36m";
  static final String ansi_FG_WHITE   = esc + "[37m";

  static final String ansi_BG_BLACK   = esc + "[40m";
  static final String ansi_BG_RED     = esc + "[41m";
  static final String ansi_BG_GREEN   = esc + "[42m";
  static final String ansi_BG_YELLOW  = esc + "[43m";
  static final String ansi_BG_BLUE    = esc + "[44m";
  static final String ansi_BG_MAGENTA = esc + "[45m";
  static final String ansi_BG_CYAN    = esc + "[46m";
  static final String ansi_BG_WHITE   = esc + "[47m";

  static final String ansi_BLINK      = esc + "[5m";

  static final String ansi_REVERSE_ON = esc + "[7m";


  private static void moveTo(int x, int y, String s) {
    AnsiConsole.out.println(esc + "[" + x + ";" + y + "H" + s + ansi_NORMAL);
  }

  public static void main(String args[]){

    AnsiConsole.systemInstall();

    AnsiConsole.out.print(ansi_CLS + ansi_HOME + ansi_NORMAL);
    moveTo(20,10, ansi_BG_BLACK + ansi_FG_WHITE + "Position 20/10");

    AnsiConsole.out.println(ansi_BG_RED + ansi_FG_YELLOW + "Yellow on Red");

    AnsiConsole.out.println(ansi_BLINK + "Blink doesn't work.");

    AnsiConsole.out.println(ansi_BG_BLUE + ansi_FG_WHITE + ansi_REVERSE_ON + "Reverse White on Blue");

  }
}
