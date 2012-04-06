class TheThread implements Runnable {

      public void run() {
      //
      //     Called when the "main class" starts
      //    "this" thread by 'new Thread(new TheThread...'
      //
             while (true) {
                    try {
                         enterLoop();
                    } 
                    catch(InterruptedException e) {
                         // Start over
      }      }      }


      public void enterLoop() throws InterruptedException {
      //
      //     Repeatedly print increasing counter and 
      //     wait 5 seconds.
      //  
      //     If 'waitForEnter' calls 'theThread.interrupt()',
      //     this thread will be immediatly stopped (even if 
      //     sleeping) and an 'InterruptedException' will
      //     be thrown. This 'InterruptedException'
      //     will be caught by the "forever loop" in this
      //     class' run() method.
      //
             int    counter = 0;

             while (true) {
                    System.out.println(counter);
                    counter ++;
                    Thread.sleep(5000);
}     }      }


public class InterruptSleepingThread {

       static Thread theThread;

       public static void main (String[] _) throws Exception{
       //   
       //     Create a thread and then go into the 'waitForEnter' Loop
       //

              theThread = new Thread(new TheThread(), "The Thread");
              theThread.start();
              waitForEnter();
       }

       static public void waitForEnter() throws Exception {

              while (true) {
              //
              //     Wait for the user to press enter.
              //
                     System.in.read();
                     theThread.interrupt();

}      }      }
