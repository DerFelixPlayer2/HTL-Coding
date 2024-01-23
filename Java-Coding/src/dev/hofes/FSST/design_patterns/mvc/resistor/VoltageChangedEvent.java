package dev.hofes.FSST.design_patterns.mvc.resistor;

import java.util.EventObject;

public class VoltageChangedEvent extends EventObject {

    private final int voltage;

    public VoltageChangedEvent(Object source, int voltage) {
        super(source);
        this.voltage = voltage;
    }

    public int getVoltage() {
        return voltage;
    }

}