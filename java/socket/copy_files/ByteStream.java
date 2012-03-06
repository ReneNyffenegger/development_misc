import java.io.InputStream;
import java.io.OutputStream;
import java.io.File;
import java.io.FileOutputStream;
import java.io.FileInputStream;

public class ByteStream {
  private static byte[] toByteArray(int in_int) {
    byte a[] = new byte[4];
    for (int i=0; i < 4; i++) {

      int  b_int = (in_int >> (i*8) ) & 255;
      byte b = (byte) ( b_int );
 
      a[i] = b;
     }
    return a;
  }

  private static int toInt(byte[] byte_array_4) {
    int ret = 0;  
    for (int i=0; i<4; i++) {
      int b = (int) byte_array_4[i];
      if (i<3 && b<0) {
        b=256+b;
      }
      ret += b << (i*8);
    }
    return ret;
  }

  public static int toInt(InputStream in) throws java.io.IOException {
    byte[] byte_array_4 = new byte[4];

    byte_array_4[0] = (byte) in.read();
    byte_array_4[1] = (byte) in.read();
    byte_array_4[2] = (byte) in.read();
    byte_array_4[3] = (byte) in.read();

    return toInt(byte_array_4);
  }

  public static String toString(InputStream ins) throws java.io.IOException {
    int len = toInt(ins);
    return toString(ins, len);
  }

  private static String toString(InputStream ins, int len) throws java.io.IOException {
    String ret=new String();
    for (int i=0; i<len;i++) {
      ret+=(char) ins.read();
    }
    return ret;
  }
  
  public static void toStream(OutputStream os, int i) throws java.io.IOException {
    byte [] byte_array_4 = toByteArray(i);
    os.write(byte_array_4);
  }

  public static void toStream(OutputStream os, String s) throws java.io.IOException {
    int len_s = s.length();
    toStream(os, len_s);
    for (int i=0;i<len_s;i++) {
      os.write((byte) s.charAt(i));
    }
    os.flush();
  }

  private static byte[] toByteArray(InputStream ins, int an_int) throws 
    java.io.IOException,  
    Exception{

    byte[] ret = new byte[an_int];

    int offset  = 0;
    int numRead = 0;
    int outstanding = an_int;

    while (
       (offset < an_int)
         &&
      (  (numRead = ins.read(ret, offset, outstanding)) > 0 )
    ) {
      offset     += numRead;
      outstanding = an_int - offset;
    }
    if (offset < ret.length) {
      throw new Exception("Could not completely read from stream, numRead="+numRead+", ret.length="+ret.length); // ???
    }
    return ret;
  }

  private static void toFile(InputStream ins, FileOutputStream fos, int len, int buf_size) throws 
        java.io.FileNotFoundException, 
        java.io.IOException {

    byte[] buffer = new byte[buf_size];

    int       len_read=0;
    int total_len_read=0;

    while ( total_len_read + buf_size <= len) {
      len_read = ins.read(buffer);
      total_len_read += len_read;
      fos.write(buffer, 0, len_read);
    }

    if (total_len_read < len) {
      toFile(ins, fos, len-total_len_read, buf_size/2);
    }
  }

  private static void toFile(InputStream ins, File file, int len) throws 
        java.io.FileNotFoundException, 
        java.io.IOException {

    FileOutputStream fos=new FileOutputStream(file);

    toFile(ins, fos, len, 1024);
  }

  public static void toFile(InputStream ins, File file) throws 
        java.io.FileNotFoundException, 
        java.io.IOException {

    int len = toInt(ins);
    toFile(ins, file, len);
  }

  public static void toStream(OutputStream os, File file) 
      throws java.io.FileNotFoundException,
             java.io.IOException{

    toStream(os, (int) file.length());

    byte b[]=new byte[1024];
    InputStream is = new FileInputStream(file);
    int numRead=0;

    while ( ( numRead=is.read(b)) > 0) {
      os.write(b, 0, numRead);
    }
    os.flush();
  }
}
