/* Internet Programming 2015/2016
 * 
 * Assignment 1
 * Authors:   Baris Can Vural,    Floris Turkenburg
 * VUNetID:   bvl250,             ftg600
 */



public class mThreadSyn1 extends Thread {

    public void run() {
        for (int i=0; i<10; i++) {
            try {
                ConsoleSyn1.display("Bonjour monde\n");
            } catch (Exception e) {
                e.printStackTrace();
            }
        }
    }
}