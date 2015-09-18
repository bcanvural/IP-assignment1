/* Internet Programming 2015/2016
 * 
 * Assignment 1
 * Authors:   Baris Can Vural,    Floris Turkenburg
 * VUNetID:   bvl250,             ftg600
 */



public class ConsoleSyn2 { //class representing shared resource which is the console
    public static void display(String str) {
        for (int i = 0; i < str.length(); i++) {
            System.out.print(str.charAt(i));
        }
    }
}