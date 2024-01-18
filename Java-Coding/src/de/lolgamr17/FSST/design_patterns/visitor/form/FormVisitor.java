package de.lolgamr17.FSST.design_patterns.visitor.form;

interface FormVisitor {
    void visit(Circle kreis);

    void visit(Rectangle rechteck);

    void visit(Triangle dreieck);
}