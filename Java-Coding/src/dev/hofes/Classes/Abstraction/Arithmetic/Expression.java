package dev.hofes.Classes.Abstraction.Arithmetic;

public abstract class Expression {
    public abstract int evaluate(Bindings binding);

    public abstract Expression reduce();

    public abstract String toString();
}