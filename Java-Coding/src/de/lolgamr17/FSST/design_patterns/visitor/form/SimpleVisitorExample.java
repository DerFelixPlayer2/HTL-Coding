package de.lolgamr17.FSST.design_patterns.visitor.form;

public class SimpleVisitorExample {
    public static void main(String[] args) {
        Form[] forms = new Form[]{new Circle(5), new Rectangle(3, 4), new Triangle(3, 4, 5)};
        FormVisitor visitor = new CalculateAreaVisitor();
        for (Form form : forms) {
            form.accept(visitor);
        }
    }
}