import java.util.concurrent.Semaphore;

public class mThread extends Thread {

    Integer m1, m2;

    public mThread(Integer m1, Integer m2){
        this.m1 = m1;
        this.m2 = m2;
    }

    public void run(){
        try {
           for (int i=0; i<10; i++){
                synchronized(m2) {
                    m2.wait();
                    Console.display("cd\n");
                }
                synchronized (m1) {
                    m1.notify();
                }
            }
        } catch (Exception e){
            e.printStackTrace();
        }
    }
}
