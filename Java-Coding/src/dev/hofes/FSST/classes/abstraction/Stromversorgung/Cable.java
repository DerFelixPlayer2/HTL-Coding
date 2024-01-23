package dev.hofes.FSST.classes.abstraction.Stromversorgung;

public final class Cable extends Socket {
    private Device connection;

    public Cable(String name) {
        super(name);
    }

    @Override
    public int calcConsumption() {
        return connection == null ? 0 : connection.calcConsumption();
    }

    @Override
    public void plug(Device device) {
        connection = device;
    }

    @Override
    public void unplug(Device device) {
        connection = null;
    }

    @Override
    boolean hasFreePlug() {
        return connection == null;
    }

    @Override
    public String toString() {
        return name + " is connected to " + (connection == null ? "nothing" : connection.toString());
    }
}