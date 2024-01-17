package de.lolgamr17.FSST.classes.extension.Tickets;

public class Advance_Ticket extends Ticket {
    protected int price;

    public Advance_Ticket(int number, int days) {
        super(number);

        if (days >= 10) {
            price = 30;
        } else {
            price = 40;
        }
    }

    public int getPrice() {
        return price;
    }

}