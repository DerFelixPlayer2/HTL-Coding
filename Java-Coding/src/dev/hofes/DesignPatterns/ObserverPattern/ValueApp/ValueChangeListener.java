package dev.hofes.DesignPatterns.ObserverPattern.ValueApp;

import java.util.EventListener;

public interface ValueChangeListener extends EventListener {
    void valueChanged(ValueChangeEvent evt);
}