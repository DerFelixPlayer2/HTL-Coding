package dev.hofes.FSST.design_patterns.composite.drawing_app;

import java.awt.*;

abstract class Shape {
    public void setX(int x) {
        this.x = x;
    }

    public void setY(int y) {
        this.y = y;
    }

    private int x;
    private int y;


    protected Shape(int x, int y) {
        this.x = x;
        this.y = y;
    }

    public int getY() {
        return y;
    }

    public int getX() {
        return x;
    }

    public abstract void draw(Color c);

    public void draw() {
        draw(Color.BLACK);
    }
}