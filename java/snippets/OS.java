public class OS {

  static String getOSString() {

    String osName = System.getProperty("os.name");

    if      (osName.startsWith("Windows"))   { return "Windows" ;} 

    else if (osName.contains  ("SunOS"  ) || 
             osName.contains  ("Solaris"))   { return "Solaris" ;}

    else if (osName.contains  ("Mac"))       { return "Mac"     ;}

    else if (osName.contains  ("FreeBSD"))   { return "FreeBSD" ;}

    else if (osName.startsWith("Linux"))     { return "Linux"   ;}
    else                                     { return "Other"   ;}

  }

  public static void main(String[] argv) {
    System.out.println(getOSString());
  }

}
