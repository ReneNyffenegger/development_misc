import java.lang.*;

import java.io.File;
import java.io.InputStream;
import java.io.FileInputStream;
import java.net.Socket;
import java.net.ServerSocket;

public class FileReceiver implements Runnable {

  private static final int port = 4711;

  private Socket socket;

  public static void main(String[] _) {
    try {
      ServerSocket listener = new ServerSocket(port);

      while (true) {
        FileReceiver file_rec = new FileReceiver();
        file_rec.socket = listener.accept();  

        new Thread(file_rec).start();
      }
    }
    catch (java.lang.Exception ex) {
      ex.printStackTrace(System.out);
    }
  }

  public void run() {
    try {
      InputStream in = socket.getInputStream();
  
      int nof_files = ByteStream.toInt(in);
  
      for (int cur_file=0;cur_file < nof_files; cur_file++) {
        String file_name = ByteStream.toString(in);
  
        File file=new File(file_name);
  
        ByteStream.toFile(in, file);
      }
    }
    catch (java.lang.Exception ex) {
      ex.printStackTrace(System.out);
    }
  }
}
