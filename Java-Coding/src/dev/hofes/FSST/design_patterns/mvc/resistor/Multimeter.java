package dev.hofes.FSST.design_patterns.mvc.resistor;

public class Multimeter {

    private Mode mode;
    private final Controller controller;
    private final Listener listener;

    private int voltage;
    private int current;

    public Multimeter(Controller controller, Mode _mode) {
        this.mode = _mode;
        this.controller = controller;

        this.listener = new Listener() {
            @Override
            public void onVoltageChanged(VoltageChangedEvent e) {
                if (mode == Mode.VOLTAGE) {
                    System.out.println("Voltage changed to " + e.getVoltage() + "V");
                    voltage = e.getVoltage();
                }
            }

            @Override
            public void onCurrentChanged(CurrentChangedEvent e) {
                if (mode == Mode.CURRENT) {
                    System.out.println("Current changed to " + e.getCurrent() + "A");
                    current = e.getCurrent();
                }
            }

            @Override
            public void onModeChanged(ModeChangedEvent e) {
                mode = e.getMode();
                if (e.getMode() == Mode.VOLTAGE) {
                    System.out.println("Voltage is: " + voltage + "V");
                } else {
                    System.out.println("Current is: " + current + "A");
                }
            }
        };
    }

}