public class Console { //class representing shared resource which is the console
    public synchronized static void display(String str) {
        for (int i = 0; i < str.length(); i++) {
            System.out.print(str.charAt(i));
        }
    }
}