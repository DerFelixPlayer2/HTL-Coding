package de.lolgamr17.FSST.threading.char_printer;

public class CharPrinter extends Thread {
    private char signal;

    public CharPrinter(char signal) {
        this.signal = signal;
    }

    @Override
    public void run() {
        for (int i = 0; i < 20; i++) {
            System.out.print(signal);
            int delay = (int) (Math.random() * 1000);
            try {
                sleep(delay);
            } catch (Exception e) {
                return;
            }
        }
    }
}