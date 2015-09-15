
public class syn2 {
    public static void main(String args[]){
        Integer m1 = new Integer(0);
        Integer m2 = new Integer(0);
        mThread myThread = new mThread(m1, m2);
        myThread.start();
        try {
            Thread.sleep(1000);
        } catch (InterruptedException e) {
            e.printStackTrace();
        }
        Console.display("ab");
        for (int i=0; i<10; i++){
            synchronized (m2) {
                m2.notify();
            }
            try {
                synchronized (m1) {
                    m1.wait();
                    Console.display("ab");
                }
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
        }
    }
}
