import java.awt.image.BufferedImage;
import java.io.*;
import javax.imageio.ImageIO;

public class RunCannyEdgeDetector {

  public static void main(String[] pathToImageInAndOut) {
    
    BufferedImage     img;
    CannyEdgeDetector canny = new CannyEdgeDetector();

    try {
      img = ImageIO.read(new File(pathToImageInAndOut[0]));

      canny.setLowThreshold (0.5f);
      canny.setHighThreshold(1.0f);

      canny.setSourceImage(img);
      canny.process();
      BufferedImage imgWithEdges = canny.getEdgesImage();

      ImageIO.write(imgWithEdges, "png", new File(pathToImageInAndOut[1]));

    }
    catch (IOException e) {
      System.out.println(e);
    }
  }

}
