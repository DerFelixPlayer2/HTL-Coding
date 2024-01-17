package de.lolgamr17.FSST.design_patterns.visitor.form;

class CalculateAreaVisitor implements FormVisitor {
    public void visit(Circle circle) {
        double area = Math.PI * circle.getRadius() * circle.getRadius();
        System.out.println("Area of the circle: " + area);
    }

    public void visit(Rectangle rectangle) {
        double area = rectangle.getWidth() * rectangle.getHeight();
        System.out.println("Area of the rectangle: " + area);
    }

    public void visit(Triangle triangle) {
        double s = (triangle.getSide1() + triangle.getSide2() + triangle.getSide3()) / 2;
        double area = Math.sqrt(s * (s - triangle.getSide1()) * (s - triangle.getSide2()) * (s - triangle.getSide3()));
        System.out.println("Area of the triangle: " + area);
    }
}