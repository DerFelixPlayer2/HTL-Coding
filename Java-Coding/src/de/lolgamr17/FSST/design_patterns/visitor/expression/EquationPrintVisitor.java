package de.lolgamr17.FSST.design_patterns.visitor.expression;

class EquationPrintVisitor implements ExpressionVisitor<String> {

    @Override
    public String visit(Add add) {
        return "(" + add.getLeft().accept(this) + " + " + add.getRight().accept(this) + ")";
    }

    @Override
    public String visit(Sub sub) {
        return "(" + sub.getLeft().accept(this) + " - " + sub.getRight().accept(this) + ")";
    }

    @Override
    public String visit(Div div) {
        return "(" + div.getLeft().accept(this) + " / " + div.getRight().accept(this) + ")";
    }

    @Override
    public String visit(Mul mul) {
        return "(" + mul.getLeft().accept(this) + " * " + mul.getRight().accept(this) + ")";
    }

    @Override
    public String visit(Literal literal) {
        return String.valueOf(literal.getValue());
    }
}