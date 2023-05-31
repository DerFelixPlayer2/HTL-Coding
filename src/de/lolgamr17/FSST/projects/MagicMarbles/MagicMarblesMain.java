package de.lolgamr17.FSST.projects.MagicMarbles;

import de.lolgamr17.FSST.projects.MagicMarbles.model.GUI;
import de.lolgamr17.FSST.projects.MagicMarbles.model.*;

public class MagicMarblesMain {

    private static GUI gui;
    private static MMGameImpl field;
    private static final int rows = 10;
    private static final int cols = 10;

    public static void main(String[] args) {
        field = new MMGameImpl(cols, rows);
        gui = new GUI(field, cols, rows);
    }
}