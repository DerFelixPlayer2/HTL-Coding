package dev.hofes.Classes.Abstraction.Stromversorgung;

public final class PowerStrip extends Socket {
    private final int n;
    private int i;
    private final Device[] connections;

    public PowerStrip(String name, int n) {
        super(name);
        this.n = n;
        this.i = 0;
        this.connections = new Device[n];
    }

    @Override
    public int calcConsumption() {
        int consumption = 0;
        for (int j = 0; j < i; j++) {
            consumption += connections[j].calcConsumption();
        }
        return consumption;
    }

    @Override
    public void plug(Device device) {
        if (hasFreePlug()) {
            connections[i++] = device;
        }
    }

    @Override
    public void unplug(Device device) {
        if (i > 0) {
            for (int j = 0; j < i; j++) {
                if (connections[j] == device) {
                    if (i - 1 - j >= 0) {
                        System.arraycopy(connections, j + 1, connections, j, i - 1);
                    }

                    i--;
                }
            }
        }
    }

    @Override
    boolean hasFreePlug() {
        return i < n;
    }

    @Override
    public String toString() {
        StringBuilder sb = new StringBuilder(name + "\n" + name);
        sb.append(" is connected to ");

        for (int j = 0; j < i; j++) {
            sb.append(connections[j].toString());
            if (j < i - 1) {
                sb.append(", ");
            }
        }

        return sb.append("\n").toString();
    }
}