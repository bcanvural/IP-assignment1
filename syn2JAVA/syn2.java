import java.util.concurrent.locks.Condition;
import java.util.concurrent.locks.Lock;
import java.util.concurrent.locks.ReentrantLock;

public class syn2 {

    public static Lock lock = new ReentrantLock();
    public static Condition c = lock.newCondition();
    public static boolean display_ab = true;

    public static void main(String args[]) {

        mThread myThread = new mThread();
        myThread.start();

        for (int i=0; i<10; i++){
            lock.lock();
            try{
                while(!display_ab) {c.await();}
                Console.display("ab");
                display_ab = false;
                c.signal();
            } catch(Exception e){
                e.printStackTrace();
            } finally {
                lock.unlock();
            }
        }
    }
}


