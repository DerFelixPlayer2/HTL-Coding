package de.lolgamr17.classes.abstraction.Stromversorgung;

public final class Computer extends Consumer {
    public Computer(String name, int consumption) {
        super(name, consumption);
    }

    @Override
    public String toString() {
        return name;
    }
}