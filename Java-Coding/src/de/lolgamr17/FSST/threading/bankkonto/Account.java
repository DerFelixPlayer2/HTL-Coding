package de.lolgamr17.FSST.threading.bankkonto;

public class Account {
    private int balance;
    private final Object monitor = new Object();

    public Account() {
        this.balance = 0;
    }

    public void deposit(int x) {
        //!!
        synchronized (monitor) {
            balance = complexLogic(balance + x);
        }
        //!!
    }

    public void withdraw(int x) {
        //!!
        synchronized (monitor) {
            balance = complexLogic(balance - x);
        }
        //!!
    }

    public int getBalance() {
        return balance;
    }

    private int complexLogic(int b) {
        int delay = (int) (Math.random() * 1000);
        try {
            Thread.sleep(delay);
        } catch (Exception e) {
            return b;
        }
        return b;
    }
}