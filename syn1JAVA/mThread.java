import java.util.Random;

public class mThread extends Thread {

    public void run(){
        for (int i=0; i<10; i++){
            try {
                Console.display("Bonjour monde!");
                Thread.sleep(new Random().nextInt(20));
            } catch (Exception e){
                e.printStackTrace();
            }
        }
    }
}