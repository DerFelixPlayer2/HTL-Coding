package de.lolgamr17.FSST.design_patterns.visitor.form;

public class Rectangle implements Form {
    private double width;
    private double height;

    public Rectangle(double width, double height) {
        this.width = width;
        this.height = height;
    }

    public double getWidth() {
        return width;
    }

    public double getHeight() {
        return height;
    }

    public void accept(FormVisitor visitor) {
        visitor.visit(this);
    }
}