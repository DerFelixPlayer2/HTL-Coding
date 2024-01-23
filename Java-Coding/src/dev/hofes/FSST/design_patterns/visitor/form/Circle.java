package dev.hofes.FSST.design_patterns.visitor.form;

public record Circle(double radius) implements Form {
    public double getRadius() {
        return radius;
    }

    public void accept(FormVisitor visitor) {
        visitor.visit(this);
    }
}