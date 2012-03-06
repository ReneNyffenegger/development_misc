import java.lang.*;

import java.io.OutputStream;
import java.io.InputStream;
import java.io.File;
import java.io.FileOutputStream;

import java.net.Socket;

public class FileSender {
  // host and port of receiver
  private static final int    port = 4711;
  private static final String host = "localhost";

  public static void main(String[] args) {
    try {
      Socket       socket = new Socket(host, port);
      OutputStream os     = socket.getOutputStream();
  
      int cnt_files = args.length;
  
      // How many files?
      ByteStream.toStream(os, cnt_files);
  
      for (int cur_file=0; cur_file<cnt_files; cur_file++) {
        ByteStream.toStream(os, args[cur_file]);
        ByteStream.toStream(os, new File(args[cur_file]));
      }
    }
    catch (Exception ex) {
      ex.printStackTrace();
    }
  }
}
