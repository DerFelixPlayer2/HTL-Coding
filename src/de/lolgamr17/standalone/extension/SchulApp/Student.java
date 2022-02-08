package de.lolgamr17.standalone.extension.SchulApp;

public class Student extends Person {
    private int id;

    public Student(String firstName, String lastName) {
        super(firstName, lastName);
    }

    public int getId() {
        return id;
    }

    public void setId(int id) {
        this.id = id;
    }

    @Override
    public void print() {
        super.print();
        System.out.println("\t(ID: " + id + ")");
    }
}