package dev.hofes.FSST.design_patterns.visitor.form;

interface Form {
    void accept(FormVisitor visitor);
}