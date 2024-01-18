package de.lolgamr17.FSST.design_patterns.composite.drawing_app;


import java.awt.*;
import java.util.ArrayList;

public class CompositeShape extends Shape {

    private final ArrayList<Shape> shapes = new ArrayList<>();

    protected CompositeShape(int x, int y) {
        super(x, y);
    }

    public void add(Shape s) {
        shapes.add(s);
    }

    public void remove(Shape s) {
        shapes.remove(s);
    }

    public void clearShapes() {
        shapes.clear();
    }

    @Override
    public void draw(Color c) {
        for (Shape s : shapes) s.draw(c);
    }
}