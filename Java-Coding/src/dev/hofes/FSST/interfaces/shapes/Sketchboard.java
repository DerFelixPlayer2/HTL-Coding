package dev.hofes.FSST.interfaces.shapes;

import java.util.Set;

public class Sketchboard {
    private final Set<Shape> shapes;

    public Sketchboard(Set<Shape> shapes) {
        this.shapes = shapes;
    }

    public void addShape(Shape shape) {
        shapes.add(shape);
    }

    public Shape getBiggest() {
        Shape biggest = null;
        for (Shape shape : shapes) {
            if (biggest == null || shape.getArea() > biggest.getArea()) {
                biggest = shape;
            }
        }
        return biggest;
    }

    public void printAll() {
        for (Shape shape : shapes) {
            System.out.println(shape.toString());
        }
    }
}