package dev.hofes.DesignPatterns.CompositePattern.DrawingApp;


import java.awt.*;
import java.util.ArrayList;

public class CompositeShape extends dev.hofes.DesignPatterns.CompositePattern.DrawingApp.Shape {

    private final ArrayList<dev.hofes.DesignPatterns.CompositePattern.DrawingApp.Shape> shapes = new ArrayList<>();

    protected CompositeShape(int x, int y) {
        super(x, y);
    }

    public void add(dev.hofes.DesignPatterns.CompositePattern.DrawingApp.Shape s) {
        shapes.add(s);
    }

    public void remove(dev.hofes.DesignPatterns.CompositePattern.DrawingApp.Shape s) {
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