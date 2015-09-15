import java.util.Random;
import java.util.concurrent.Semaphore;

public class syn1 {

    public static void main(String args[]) throws InterruptedException {

        Semaphore sharedSemaphore = new Semaphore(1);
        mThread myThread = new mThread(sharedSemaphore);
        myThread.start();

        for (int i = 0; i < 10; i++) {
            try {
                sharedSemaphore.acquire();
                Console.display("Hello world!");
                sharedSemaphore.release();
                Thread.sleep(new Random().nextInt(20));
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
        }
    }
}





