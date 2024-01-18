package de.lolgamr17.FSST.threading;

public class WaitingRoom extends Thread {
    private final int maxChairs = 5;
    private int chairs = 0;

    public synchronized void enqueue() throws InterruptedException {
        while (chairs >= maxChairs) {
            wait();
        }
        chairs++;
        System.out.println("Patient entered waiting room. Chairs: " + chairs);
        notifyAll();
    }

    public synchronized void process() throws InterruptedException {
        while (chairs <= 0) {
            wait();
        }
        System.out.println("Patient is being processed.");
        chairs--;
        notifyAll();
    }

    @Override
    public void run() {
        while (true) {
            try {
                enqueue();
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
        }
    }
}