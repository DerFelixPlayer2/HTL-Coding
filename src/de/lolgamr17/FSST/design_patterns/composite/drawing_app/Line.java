package de.lolgamr17.FSST.design_patterns.composite.drawing_app;

import java.awt.*;

public class Line {

    private final int x1, x2, y1, y2;

    public Line(int x1, int y1, int x2, int y2) {
        this.x1 = x1;
        this.x2 = x2;
        this.y1 = y1;
        this.y2 = y2;
    }

    public void showFancyLine() {
        Window.drawLine(x1, y1, x2, y2, Color.BLUE);
    }
}