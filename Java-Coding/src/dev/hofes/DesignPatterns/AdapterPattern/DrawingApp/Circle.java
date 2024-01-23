package dev.hofes.DesignPatterns.AdapterPattern.DrawingApp;

class Circle extends Shape {
    private final int r;


    Circle(int x, int y, int r) {
        super(x, y);
        this.r = r;
    }


    @Override
    public void draw() {
        Window.drawCircle(getX(), getY(), r);
    }
}