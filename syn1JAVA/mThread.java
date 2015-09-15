import java.util.Random;
import java.util.concurrent.Semaphore;

public class mThread extends Thread {

    Semaphore sharedSemaphore;
    public mThread(Semaphore sharedSemaphore){
        this.sharedSemaphore = sharedSemaphore;
    }

    public void run(){
        for (int i=0; i<10; i++){
            try {
                this.sharedSemaphore.acquire();
                Console.display("Bonjour monde!");
                this.sharedSemaphore.release();
                Thread.sleep(new Random().nextInt(20));
            } catch (Exception e){
                e.printStackTrace();
            }
        }
    }
}
