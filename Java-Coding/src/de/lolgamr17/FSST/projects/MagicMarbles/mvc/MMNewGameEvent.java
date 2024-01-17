package de.lolgamr17.FSST.projects.MagicMarbles.mvc;

import java.util.EventObject;

public class MMNewGameEvent extends EventObject {

    private final int rows, cols;

    public MMNewGameEvent(Object source, int rows, int cols) {
        super(source);
        this.rows = rows;
        this.cols = cols;
    }

    public int getRows() {
        return rows;
    }

    public int getCols() {
        return cols;
    }

}