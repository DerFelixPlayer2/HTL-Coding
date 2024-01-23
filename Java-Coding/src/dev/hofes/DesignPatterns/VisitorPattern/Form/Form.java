package dev.hofes.DesignPatterns.VisitorPattern.Form;

public interface Form {
    void accept(FormVisitor visitor);
}