package dev.hofes.FSST.design_patterns.mvc.resistor;

import java.util.EventObject;

public class CurrentChangedEvent extends EventObject {

    private final int current;

    public CurrentChangedEvent(Object source, int current) {
        super(source);
        this.current = current;
    }

    public int getCurrent() {
        return current;
    }

}