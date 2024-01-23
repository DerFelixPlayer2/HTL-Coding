package dev.hofes.FSST.classes.extension.Tickets;

public abstract class Ticket {
    public int number;

    public Ticket(int number) {
        this.number = number;
    }

    public abstract int getPrice();

    public void print() {
        System.out.println("Number: " + number + ", " + "Price: $" + getPrice());
    }
}