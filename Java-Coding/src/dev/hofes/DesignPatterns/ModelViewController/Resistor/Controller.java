package dev.hofes.DesignPatterns.ModelViewController.Resistor;

import java.io.IOException;

public class Controller {

    private final int voltage;

    public Controller() throws IOException {
        System.out.println("Voltage for source: ");
        this.voltage = System.in.read();
    }

}