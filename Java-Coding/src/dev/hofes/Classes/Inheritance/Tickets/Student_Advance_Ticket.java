package dev.hofes.Classes.Inheritance.Tickets;

public class Student_Advance_Ticket extends Advance_Ticket {
    public Student_Advance_Ticket(int number, int days) {
        super(number, days);

        price /= 2;
    }

    @Override
    public void print() {
        super.print();
        System.out.println("\t(ID Required)");
    }
}