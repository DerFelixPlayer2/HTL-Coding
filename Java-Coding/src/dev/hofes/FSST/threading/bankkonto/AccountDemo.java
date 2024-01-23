package dev.hofes.FSST.threading.bankkonto;

public class AccountDemo {
    public static void main(String[] args) throws InterruptedException {
        Account a = new Account();
        Thread t1 = new Thread(new Einzahler(a));
        Thread t2 = new Thread(new Auszahler(a));
        Thread t3 = new Thread(new Einzahler(a));
        Thread t4 = new Thread(new Auszahler(a));
        t1.start();
        t2.start();
        t3.start();
        t4.start();

        t1.join();
        t2.join();
        t4.join();
        t3.join();

        System.out.println(a.getBalance());
    }
}