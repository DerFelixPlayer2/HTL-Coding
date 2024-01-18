package de.lolgamr17.FSST.design_patterns.composite.drawing_app;

import java.awt.*;

class Rectangle extends Shape {
    private final int w, h;

    Rectangle(int x, int y, int w, int h) {
        super(x, y);
        this.w = w;
        this.h = h;
    }


    @Override
    public void draw(Color c) {
        Window.drawRectangle(getX(), getY(), w, h, c);
    }
}