package dev.hofes.FSST.design_patterns.mvc.resistor;

import java.util.EventListener;

public interface Listener extends EventListener {

    void onVoltageChanged(VoltageChangedEvent e);

    void onCurrentChanged(CurrentChangedEvent e);

    void onModeChanged(ModeChangedEvent e);

}