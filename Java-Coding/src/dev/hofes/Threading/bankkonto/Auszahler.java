package dev.hofes.Threading.bankkonto;

public class Auszahler implements Runnable {
    private final Account account;

    public Auszahler(Account account) {
        this.account = account;
    }

    @Override
    public void run() {
        for (int i = 0; i < 10; i++) {
            account.withdraw(i);
        }
    }
}