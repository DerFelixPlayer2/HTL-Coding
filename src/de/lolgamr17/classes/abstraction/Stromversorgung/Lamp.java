package de.lolgamr17.classes.abstraction.Stromversorgung;

public final class Lamp extends Consumer {
    public Lamp(String name, int consumption) {
        super(name, consumption);
    }

    @Override
    public String toString() {
        return name;
    }
}