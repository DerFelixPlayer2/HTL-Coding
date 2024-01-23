package dev.hofes.FSST.design_patterns.mvc.resistor;

import java.util.EventObject;

public class ModeChangedEvent extends EventObject {

    private final Mode mode;

    public ModeChangedEvent(Object source, Mode mode) {
        super(source);
        this.mode = mode;
    }

    public Mode getMode() {
        return mode;
    }

}