package de.lolgamr17.standalone.extension.Tickets;

public class TicketMain {
    public static void main(String[] args) {
        Ticket[] tickets = new Ticket[9];

        int i;
        for (i = 0; i < 3; i++) {
            tickets[i] = new Advance_Ticket(i, i * 6);
        }
        for (; i < 6; i++) {
            tickets[i] = new Student_Advance_Ticket(i, i * 2);
        }
        for (; i < 9; i++) {
            tickets[i] = new Walk_Up_Ticket(i);
        }

        for (i = 0; i < 9; i++) {
            tickets[i].print();
        }
    }
}