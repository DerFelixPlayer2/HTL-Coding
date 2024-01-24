import dev.hofes.ComplexDatastructures.ComparableNode;
import dev.hofes.ComplexDatastructures.Trees.BinaryTree;
import org.junit.jupiter.api.Test;

import static org.junit.jupiter.api.Assertions.*;

public class TestTree {

    @Test
    public void testInsert() {
        final BinaryTree<Integer> tree = new BinaryTree<>();

        tree.insert(5);
        tree.insert(3);
        tree.insert(7);
        tree.insert(2);
        tree.insert(6);
        tree.insert(-4);
        tree.insert(0);

        final ComparableNode<Integer> root = tree.search(5);

        assert root != null;
        assert root.value == 5;
        assert root.left.value == 3;
        assert root.left.left.value == 2;
        assert root.right.value == 7;
        assert root.right.left.value == 6;
        assert root.left.left.left.value == -4;
        assert root.left.left.left.right.value == 0;

        assertThrows(IllegalArgumentException.class, () -> tree.insert(null));
    }

    @Test
    public void testRecursiveInsert() {
        final BinaryTree<Integer> tree = new BinaryTree<>();

        tree.insert_recursive(5);
        tree.insert_recursive(3);
        tree.insert_recursive(7);
        tree.insert_recursive(2);
        tree.insert_recursive(6);
        tree.insert_recursive(-4);
        tree.insert_recursive(0);

        final ComparableNode<Integer> root = tree.search(5);

        assert root != null;
        assert root.value == 5;
        assert root.left.value == 3;
        assert root.left.left.value == 2;
        assert root.right.value == 7;
        assert root.right.left.value == 6;
        assert root.left.left.left.value == -4;
        assert root.left.left.left.right.value == 0;

        assertThrows(IllegalArgumentException.class, () -> tree.insert_recursive(null));
    }

}