package dev.hofes.Exceptions;

public class Stack {
    private final int[] stack;
    private int top;

    public Stack(int size) {
        stack = new int[size];
        top = -1;
    }

    public void push(int value) throws StackOverflowException {
        if (top == stack.length - 1) {
            throw new StackOverflowException();
        }

        stack[++top] = value;
    }

    public int pop() throws StackUnderflowException {
        if (top == -1) {
            throw new StackUnderflowException();
        }

        return stack[top--];
    }

    public int size() {
        return top + 1;
    }

    public static class StackOverflowException extends Exception {
        public StackOverflowException() {
            super("Stack is full");
        }
    }

    public static class StackUnderflowException extends Exception {
        public StackUnderflowException() {
            super("Stack is empty");
        }
    }
}