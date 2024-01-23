package dev.hofes.FSST.classes.abstraction.Stromversorgung;

abstract public class Device {
    protected final String name;

    public Device(String name) {
        this.name = name;
    }

    abstract public int calcConsumption();

    @Override
    public String toString() {
        return name + "{Consumption=" + calcConsumption() + "}";
    }
}