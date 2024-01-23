package dev.hofes.FSST.design_patterns.visitor.expression;

public class Expression {
    public static void main(String[] args) {
        Expr demo = new Add(new Literal(5), new Mul(new Add(new Literal(3), new Literal(4)), new Literal(9)));
        EquationPrintVisitor printer = new EquationPrintVisitor();
        EvaluationVisitor eval = new EvaluationVisitor();
        String result = demo.accept(printer);
        System.out.print(result);
        int value = demo.accept(eval);
        System.out.println(" = " + value);
    }
}