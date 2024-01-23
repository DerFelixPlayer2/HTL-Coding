package dev.hofes.DesignPatterns.VisitorPattern.Expression;

class Literal implements Expr {
    private final int value;


    Literal(int value) {
        this.value = value;
    }

    public int getValue() {
        return value;
    }

    @Override
    public <T> T accept(ExpressionVisitor<T> visitor) {
        return visitor.visit(this);
    }
}