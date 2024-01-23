package dev.hofes.FSST.design_patterns.visitor.expression;

class Mul extends BinaryOperation {

    Mul(Expr left, Expr right) {
        super(left, right);
    }

    @Override
    public <T> T accept(ExpressionVisitor<T> visitor) {
        return visitor.visit(this);
    }
}