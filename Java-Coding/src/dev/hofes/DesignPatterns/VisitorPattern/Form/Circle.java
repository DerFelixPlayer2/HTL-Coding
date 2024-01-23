package dev.hofes.DesignPatterns.VisitorPattern.Form;

public record Circle(double radius) implements Form {
    public double getRadius() {
        return radius;
    }

    public void accept(FormVisitor visitor) {
        visitor.visit(this);
    }
}