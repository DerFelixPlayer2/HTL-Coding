package dev.hofes.FSST.design_patterns.composite.drawing_app;

import java.awt.*;

class Circle extends Shape {
    private final int r;


    Circle(int x, int y, int r) {
        super(x, y);
        this.r = r;
    }


    @Override
    public void draw(Color c) {
        Window.drawCircle(getX(), getY(), r, c);
    }
}