package dev.hofes.DesignPatterns.ModelViewController.Resistor;

import java.util.EventListener;

public interface Listener extends EventListener {

    void onVoltageChanged(VoltageChangedEvent e);

    void onCurrentChanged(CurrentChangedEvent e);

    void onModeChanged(ModeChangedEvent e);

}