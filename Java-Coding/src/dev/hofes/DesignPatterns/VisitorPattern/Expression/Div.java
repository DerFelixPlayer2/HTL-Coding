package dev.hofes.DesignPatterns.VisitorPattern.Expression;

class Div extends BinaryOperation {

    Div(Expr left, Expr right) {
        super(left, right);
    }

    @Override
    public <T> T accept(ExpressionVisitor<T> visitor) {
        return visitor.visit(this);
    }
}