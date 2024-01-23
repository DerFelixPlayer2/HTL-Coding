package dev.hofes.Classes.Abstraction.Arithmetic;

public class Literal extends Expression {
    private final int value;

    public Literal(int value) {
        this.value = value;
    }

    public int getValue() {
        return value;
    }

    @Override
    public int evaluate(Bindings binding) {
        return value;
    }

    @Override
    public Expression reduce() {
        return this;
    }

    @Override
    public String toString() {
        return value + "";
    }
}