import java.util.Random;

public class syn1 {

    public static void main(String args[]) throws InterruptedException {

        mThread myThread = new mThread();
        myThread.start();

        for (int i = 0; i < 10; i++) {
            try {
                Console.display("Hello world!");
                Thread.sleep(new Random().nextInt(20));
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
        }
    }
}