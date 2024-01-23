package dev.hofes.Arrays;

public class Rectangle {
    final int x, y;
    final int width, height;

    public Rectangle(int x, int y, int width, int height) {
        this.x = x;
        this.y = y;
        this.width = width;
        this.height = height;
    }

    public boolean isHit(int x, int y) {
        return (x >= this.x && x <= this.x + width) &&
                (y <= this.y + height && y >= this.y);
    }

    @Override
    public String toString() {
        return "Rectangle{" +
                "x=" + x +
                ", y=" + y +
                ", width=" + width +
                ", height=" + height +
                '}';
    }
}