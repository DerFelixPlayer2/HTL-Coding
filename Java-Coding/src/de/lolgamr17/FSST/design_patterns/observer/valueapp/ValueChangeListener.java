package de.lolgamr17.FSST.design_patterns.observer.valueapp;

import java.util.EventListener;

public interface ValueChangeListener extends EventListener {
    void valueChanged(ValueChangeEvent evt);
}