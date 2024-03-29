package dev.hofes.DesignPatterns.AdapterPattern.DrawingApp;

class Rectangle extends Shape {
    private final int w, h;

    Rectangle(int x, int y, int w, int h) {
        super(x, y);
        this.w = w;
        this.h = h;
    }


    @Override
    public void draw() {
        Window.drawRectangle(getX(), getY(), w, h);
    }
}