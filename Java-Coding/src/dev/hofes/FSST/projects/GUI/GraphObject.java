package dev.hofes.FSST.projects.GUI;

import java.awt.*;

public abstract class GraphObject {
    private Color color;
    private Point location;

    GraphObject(Color color, Point location) {
        this.color = color;
        this.location = location;
    }

    public Color getColor() {
        return color;
    }

    public Point getLocation() {
        return location;
    }

    public void setLocation(Point location) {
        this.location = location;
    }

    public void setColor(Color color) {
        this.color = color;
    }

    public abstract void resize(double factor);

    public abstract void draw();

    @Override
    public String toString() {
        return "GraphObject(" + color + ", " + location + ")";
    }
}