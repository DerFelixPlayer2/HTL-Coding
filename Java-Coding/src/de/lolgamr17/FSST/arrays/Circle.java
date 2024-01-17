package de.lolgamr17.FSST.arrays;

public class Circle {
    final int x, y;
    final int r;

    public Circle(int x, int y, int r) {
        this.x = x;
        this.y = y;
        this.r = r;
    }

    public boolean isHit(int x, int y) {
        int dx = Math.abs(this.x - x);
        int dy = Math.abs(this.y - y);
        return Math.sqrt((dx * dx) + (dy * dy)) <= this.r;
    }

    @Override
    public String toString() {
        return "Circle{" +
                "x=" + x +
                ", y=" + y +
                ", r=" + r +
                '}';
    }
}