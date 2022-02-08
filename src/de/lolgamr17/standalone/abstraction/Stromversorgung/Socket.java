package de.lolgamr17.standalone.abstraction.Stromversorgung;

public abstract class Socket extends Device {
    public Socket(String name) {
        super(name);
    }

    abstract public void plug(Device device);
    abstract public void unplug(Device device);
    abstract boolean hasFreePlug();
}