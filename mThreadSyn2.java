/* Internet Programming 2015/2016
 * 
 * Assignment 1
 * Authors:   Baris Can Vural,    Floris Turkenburg
 * VUNetID:   bvl250,             ftg600
 */



public class mThreadSyn2 extends Thread {

    public void run() {

        for (int i=0; i<10; i++) {
            syn2.lock.lock();
            try {
                while (syn2.display_ab) {
                    syn2.c.await();
                }
                ConsoleSyn2.display("cd\n");
                syn2.display_ab = true;
                syn2.c.signal();
            } catch (Exception e) {
                e.printStackTrace();
            } finally {
                syn2.lock.unlock();
            }
        }
    }
}
