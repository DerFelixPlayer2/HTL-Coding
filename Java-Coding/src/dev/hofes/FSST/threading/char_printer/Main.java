package dev.hofes.FSST.threading.char_printer;

public class Main {
    public static void main(String[] args) throws InterruptedException {
        Thread t1 = new CharPrinter('*');
        Thread t2 = new CharPrinter('x');
        t1.start();
        t2.start();

        Thread t3 = new Thread(new BetterCharPrinter('O'));
        t3.start();
        System.out.println("Done main");
    }
}