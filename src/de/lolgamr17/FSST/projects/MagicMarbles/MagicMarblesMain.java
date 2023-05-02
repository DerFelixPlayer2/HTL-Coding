package de.lolgamr17.FSST.projects.MagicMarbles;

import de.lolgamr17.FSST.projects.MagicMarbles.gui.GUI;
import de.lolgamr17.FSST.projects.MagicMarbles.model.*;
import de.lolgamr17.FSST.projects.MagicMarbles.mvc.MMModel;

public class MagicMarblesMain {

    private static MMModel model;
    private static GUI gui;
    private static MMGame field;
    private static int rows = 10;
    private static int cols = 10;

    public static void main(String[] args) {
        model = new MMModel();
        field = new MMGameImpl(cols, rows, model);
        gui = new GUI(model, cols, rows);

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

    public static void onNewGame(int rows, int cols) {
        if (rows != -1) {
            MagicMarblesMain.rows = rows;
        }
        if (cols != -1) {
            MagicMarblesMain.cols = cols;
        }

        model = new MMModel();
        field = new MMGameImpl(MagicMarblesMain.cols, MagicMarblesMain.rows, model);
        gui.close();
        gui = new GUI(model, MagicMarblesMain.cols, MagicMarblesMain.rows);
        model.updateField(field);
    }
}