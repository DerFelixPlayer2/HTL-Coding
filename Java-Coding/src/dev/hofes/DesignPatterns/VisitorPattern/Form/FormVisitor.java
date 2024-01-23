package dev.hofes.DesignPatterns.VisitorPattern.Form;

interface FormVisitor {
    void visit(Circle kreis);

    void visit(Rectangle rechteck);

    void visit(Triangle dreieck);
}