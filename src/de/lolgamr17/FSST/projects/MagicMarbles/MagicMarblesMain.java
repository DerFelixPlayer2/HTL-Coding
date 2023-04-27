package de.lolgamr17.FSST.projects.MagicMarbles;

import de.lolgamr17.FSST.projects.MagicMarbles.gui.GUI;
import de.lolgamr17.FSST.projects.MagicMarbles.model.*;
import de.lolgamr17.FSST.projects.MagicMarbles.mvc.MMModel;

import java.awt.event.ActionEvent;

public class MagicMarblesMain {

    private static MMModel model;
    private static GUI gui;
    private static MMGame field;

    public static void main(String[] args) {
        model = new MMModel();
        field = new MMGameImpl(10, 10, model);
        gui = new GUI(model);

        model.updateField(field);
    }

    public static void onMarblePressed(int row, int col) {
        try {
//            System.out.println("Marble pressed at " + row + ", " + col);
            field.select(row, col);
        } catch (MMException e) {
            System.out.printf(e.getMessage());
        }
    }

    public static void onNewGame(ActionEvent ignored) {
        field = new MMGameImpl(10, 10, model);
        model.updateField(field);
    }
}