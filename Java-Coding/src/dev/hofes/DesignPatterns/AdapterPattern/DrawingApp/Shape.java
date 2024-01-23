package dev.hofes.DesignPatterns.AdapterPattern.DrawingApp;

abstract class Shape {
    private final int x;
    private final int y;


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

    public abstract void draw();
}