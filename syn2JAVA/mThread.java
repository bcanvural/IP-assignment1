
public class mThread extends Thread {

    public void run() {

        for (int i=0; i<10; i++){
            syn2.lock.lock();
            try{
                while(syn2.display_ab) {syn2.c.await();}
                Console.display("cd\n");
                syn2.display_ab = true;
                syn2.c.signal();
            } catch(Exception e){
                e.printStackTrace();
            } finally {
                syn2.lock.unlock();
            }
        }
    }
}
