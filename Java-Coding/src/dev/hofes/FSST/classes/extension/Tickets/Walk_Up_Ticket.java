package dev.hofes.FSST.classes.extension.Tickets;

public class Walk_Up_Ticket extends Ticket {
    public Walk_Up_Ticket(int number) {
        super(number);
    }

    public int getPrice() {
        return 50;
    }
}