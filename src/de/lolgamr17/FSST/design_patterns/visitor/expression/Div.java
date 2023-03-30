package de.lolgamr17.FSST.design_patterns.visitor.expression;

class Div extends BinaryOperation {

    Div(Expr left, Expr right) {
        super(left, right);
    }

    @Override
    public <T> T accept(ExpressionVisitor<T> visitor) {
        return visitor.visit(this);
    }
}