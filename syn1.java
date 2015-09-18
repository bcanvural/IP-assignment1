/* Internet Programming 2015/2016
 * 
 * Assignment 1
 * Authors:   Baris Can Vural,    Floris Turkenburg
 * VUNetID:   bvl250,             ftg600
 */



public class syn1 {

    public static void main(String args[]) {

        mThreadSyn1 myThread = new mThreadSyn1();
        myThread.start();

        for (int i = 0; i < 10; i++) {
            ConsoleSyn1.display("Hello world\n");
        }
    }
}