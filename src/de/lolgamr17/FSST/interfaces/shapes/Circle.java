package de.lolgamr17.FSST.interfaces.shapes;

import java.util.Objects;

public class Circle extends Shape {
    protected final int radius;

    public Circle(int x, int y, int radius) {
        super(x, y);
        this.radius = radius;
    }

    public int getRadius() {
        return radius;
    }

    @Override
    public int getArea() {
        return (int) (Math.PI * radius * radius);
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;
        Circle circle = (Circle) o;
        return radius == circle.radius && x == circle.x && y == circle.y;
    }

    @Override
    public int hashCode() {
        return Objects.hash(radius, x, y);
    }

    @Override
    public String toString() {
        return "(" + x + "/" + y + ") - r: " + radius;
    }
}