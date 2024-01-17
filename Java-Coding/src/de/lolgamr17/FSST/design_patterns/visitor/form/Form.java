package de.lolgamr17.FSST.design_patterns.visitor.form;

interface Form {
    void accept(FormVisitor visitor);
}