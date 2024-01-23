import dev.hofes.Testing.LinkedList;
import org.jetbrains.annotations.NotNull;
import org.junit.jupiter.api.Test;

import java.io.ByteArrayOutputStream;
import java.io.PrintStream;

import static org.junit.jupiter.api.Assertions.assertEquals;
import static org.junit.jupiter.api.Assertions.assertThrows;

class LinkedListTest {

    @Test
    void testAppend() {
        LinkedList linkedList = new LinkedList();

        linkedList.append(1);
        linkedList.append(2);
        linkedList.append(3);

        assertEquals("Linked List: 1 2 3 ", getListAsString(linkedList));
    }

    @Test
    void testEmptyList() {
        LinkedList linkedList = new LinkedList();

        assertEquals("Linked List: ", getListAsString(linkedList));
    }

    @Test
    void testAppendAndPrint() {
        LinkedList linkedList = new LinkedList();

        linkedList.append(1);
        linkedList.append(2);
        linkedList.append(3);

        assertEquals("Linked List: 1 2 3 ", getListAsString(linkedList));

        linkedList.append(4);
        linkedList.append(5);

        assertEquals("Linked List: 1 2 3 4 5 ", getListAsString(linkedList));
    }

    @Test
    void testAppendToEmptyList() {
        LinkedList linkedList = new LinkedList();

        linkedList.append(42);

        assertEquals("Linked List: 42 ", getListAsString(linkedList));
    }

    @Test
    void testAppendNegativeValues() {
        LinkedList linkedList = new LinkedList();

        linkedList.append(-1);
        linkedList.append(-5);
        linkedList.append(-10);

        assertEquals("Linked List: -1 -5 -10 ", getListAsString(linkedList));
    }

    @Test
    void testAppendZero() {
        LinkedList linkedList = new LinkedList();

        linkedList.append(0);

        assertEquals("Linked List: 0 ", getListAsString(linkedList));
    }

    @Test
    void testAppendAndPrintEmptyList() {
        LinkedList linkedList = new LinkedList();

        linkedList.printList();

        assertEquals("Linked List: ", getListAsString(linkedList));
    }

    @Test
    void testNullPrint() {
        LinkedList linkedList = new LinkedList();

        assertThrows(NullPointerException.class, linkedList::printList);
    }

    private @NotNull String getListAsString(@NotNull LinkedList linkedList) {
        ByteArrayOutputStream outContent = new ByteArrayOutputStream();
        System.setOut(new PrintStream(outContent));

        linkedList.printList();

        return outContent.toString().trim();
    }
}