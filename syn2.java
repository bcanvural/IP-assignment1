/* Internet Programming 2015/2016
 * 
 * Assignment 1
 * Authors:   Baris Can Vural,    Floris Turkenburg
 * VUNetID:   bvl250,             ftg600
 */



import java.util.concurrent.locks.Condition;
import java.util.concurrent.locks.Lock;
import java.util.concurrent.locks.ReentrantLock;

public class syn2 {

    public static Lock lock = new ReentrantLock();
    public static Condition c = lock.newCondition();
    public static boolean display_ab = true;

    public static void main(String args[]) {

        mThreadSyn2 myThread = new mThreadSyn2();
        myThread.start();

        for (int i=0; i<10; i++) {
            lock.lock();
            try {
                while (!display_ab) {
                    c.await();
                }
                ConsoleSyn2.display("ab");
                display_ab = false;
                c.signal();
            } catch (Exception e) {
                e.printStackTrace();
            } finally {
                lock.unlock();
            }
        }
    }
}


