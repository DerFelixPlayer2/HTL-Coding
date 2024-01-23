package dev.hofes.DesignPatterns.ModelViewController.MagicMarbles;

import dev.hofes.DesignPatterns.ModelViewController.MagicMarbles.model.MMView;
import dev.hofes.DesignPatterns.ModelViewController.MagicMarbles.model.MMGameImpl;

public class MagicMarblesMain {

    private static MMView gui;
    private static MMGameImpl field;
    private static final int rows = 10;
    private static final int cols = 10;

    public static void main(String[] args) {
        field = new MMGameImpl(cols, rows);
        gui = new MMView(field, cols, rows);
    }
}