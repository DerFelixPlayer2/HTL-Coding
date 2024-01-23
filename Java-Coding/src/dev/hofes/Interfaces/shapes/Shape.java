package dev.hofes.Interfaces.shapes;

public abstract class Shape {
    protected final int x;
    protected final int y;

    protected Shape(int x, int y) {
        this.x = x;
        this.y = y;
    }

    public abstract int getArea();

    public abstract boolean equals(Object o);

    public abstract int hashCode();

    public abstract String toString();
}