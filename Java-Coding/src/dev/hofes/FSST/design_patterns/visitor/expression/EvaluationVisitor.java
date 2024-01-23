package dev.hofes.FSST.design_patterns.visitor.expression;

class EvaluationVisitor implements ExpressionVisitor<Integer> {

    @Override
    public Integer visit(Add add) {
        return add.getLeft().accept(this) + add.getRight().accept(this);
    }

    @Override
    public Integer visit(Sub sub) {
        return sub.getLeft().accept(this) - sub.getRight().accept(this);
    }

    @Override
    public Integer visit(Div div) {
        return div.getLeft().accept(this) / div.getRight().accept(this);
    }

    @Override
    public Integer visit(Mul mul) {
        return mul.getLeft().accept(this) * mul.getRight().accept(this);
    }

    @Override
    public Integer visit(Literal literal) {
        return literal.getValue();
    }
}