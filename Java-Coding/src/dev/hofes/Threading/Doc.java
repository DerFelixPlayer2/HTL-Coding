package dev.hofes.Threading;

public class Doc extends Thread {
    private final WaitingRoom waitingRoom;
    private final int millis;

    public Doc(WaitingRoom waitingRoom, int millis) {
        this.waitingRoom = waitingRoom;
        this.millis = millis;
    }

    @Override
    public void run() {
        while (true) {
            try {
                sleep(millis);
                waitingRoom.process();
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
        }
    }
}