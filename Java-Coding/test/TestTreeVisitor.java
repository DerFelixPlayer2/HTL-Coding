import dev.hofes.FSST.design_patterns.visitor.tree.PrintVisitor;
import dev.hofes.FSST.design_patterns.visitor.tree.SumVisitor;
import dev.hofes.SEN.BinaryTrees.Tree;
import org.junit.jupiter.api.Test;

public class TestTreeVisitor {

    @Test
    public void testSumVisitor() {
        final Tree<Integer> tree = new Tree<>();

        tree.insert(5);
        tree.insert(3);
        tree.insert(7);
        tree.insert(2);
        tree.insert(6);
        tree.insert(-4);
        tree.insert(0);

        final SumVisitor visitor = new SumVisitor();
        tree.accept(visitor);
        assert visitor.getSum() == 19;
    }

    @Test
    public void testPrintVisitor() {
        final Tree<Integer> tree = new Tree<>();

        tree.insert(5);
        tree.insert(3);
        tree.insert(7);
        tree.insert(2);
        tree.insert(6);
        tree.insert(-4);
        tree.insert(0);

        final PrintVisitor<Integer> visitor = new PrintVisitor<>(0);
        tree.accept(visitor);
        assert visitor.getPrintedTree().equals("532-4076");

        final PrintVisitor<Integer> visitor2 = new PrintVisitor<>(1);
        tree.accept(visitor2);
        assert visitor2.getPrintedTree().equals("-4023567");

        final PrintVisitor<Integer> visitor3 = new PrintVisitor<>(2);
        tree.accept(visitor3);
        assert visitor3.getPrintedTree().equals("0-423675");
    }

}