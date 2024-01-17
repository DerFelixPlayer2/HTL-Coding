package de.lolgamr17.FSST.design_patterns.visitor.form;

class Triangle implements Form {
    private final double side1;
    private final double side2;
    private final double side3;

    public Triangle(double a, double b, double c) {
        this.side1 = a;
        this.side2 = b;
        this.side3 = c;
    }

    public double getSide1() {
        return side1;
    }

    public double getSide2() {
        return side2;
    }

    public double getSide3() {
        return side3;
    }

    public void accept(FormVisitor visitor) {
        visitor.visit(this);
    }
}