package de.lolgamr17.FSST.design_patterns.mvc.resistor;

import java.io.IOException;

public class ResistorApp {
    public static void main(String[] args) throws IOException {
        Controller controller = new Controller();
        Multimeter multimeter = switch (System.in.read()) {
            case 'v' -> new Multimeter(controller, Mode.VOLTAGE);
            case 'c' -> new Multimeter(controller, Mode.CURRENT);
            default -> throw new IllegalArgumentException("Invalid mode");
        };
        Modell modell = new Modell(controller);
    }
}