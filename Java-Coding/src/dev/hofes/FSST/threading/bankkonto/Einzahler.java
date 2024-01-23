package dev.hofes.FSST.threading.bankkonto;

public class Einzahler implements Runnable {
    private final Account account;

    public Einzahler(Account account) {
        this.account = account;
    }

    @Override
    public void run() {
        for (int i = 0; i < 10; i++) {
            account.deposit(i);
        }
    }
}