package de.lolgamr17.FSST.classes.extension.SchulApp;

public class Lehrer extends Person {
    private final String id;

    public Lehrer(String firstName, String lastName) {
        super(firstName, lastName);
        id = lastName.substring(0, 3) + firstName.charAt(0);
    }

    public String getId() {
        return id;
    }

    @Override
    public void print() {
        super.print();
        System.out.println("\t(ID: " + id + ")");
    }
}