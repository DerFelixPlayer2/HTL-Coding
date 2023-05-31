package de.lolgamr17.FSST.projects.MagicMarbles;

import de.lolgamr17.FSST.projects.MagicMarbles.gui.GUI;
import de.lolgamr17.FSST.projects.MagicMarbles.model.*;
import de.lolgamr17.FSST.projects.MagicMarbles.mvc.MMModel;

public class MagicMarblesMain {

    private static MMModel model;
    private static GUI gui;
    private static MMGame field;
    private static final int rows = 10;
    private static final int cols = 10;

    public static void main(String[] args) {
        model = new MMModel();
        gui = new GUI(model, cols, rows);
        field = new MMGameImpl(cols, rows, model);
    }
}