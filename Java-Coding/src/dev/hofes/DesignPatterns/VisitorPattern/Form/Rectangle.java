package dev.hofes.DesignPatterns.VisitorPattern.Form;

public class Rectangle implements Form {
    private final double width;
    private final double height;

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