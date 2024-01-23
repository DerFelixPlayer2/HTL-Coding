package dev.hofes.Classes.Inheritance.Tickets;

public class Walk_Up_Ticket extends Ticket {
    public Walk_Up_Ticket(int number) {
        super(number);
    }

    public int getPrice() {
        return 50;
    }
}