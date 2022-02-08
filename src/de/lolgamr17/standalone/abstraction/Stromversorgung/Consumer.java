package de.lolgamr17.standalone.abstraction.Stromversorgung;

abstract public class Consumer extends Device {
    private final int consumption;

    public Consumer(String name, int consumption) {
        super(name);
        this.consumption = consumption;
    }

    @Override
    public final int calcConsumption() {
        return consumption;
    }
}