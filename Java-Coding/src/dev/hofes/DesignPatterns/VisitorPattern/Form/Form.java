package dev.hofes.DesignPatterns.VisitorPattern.Form;

interface Form {
    void accept(FormVisitor visitor);
}