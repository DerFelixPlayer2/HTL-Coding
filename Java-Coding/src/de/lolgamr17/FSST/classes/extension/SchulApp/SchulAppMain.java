package de.lolgamr17.FSST.classes.extension.SchulApp;

public class SchulAppMain {
    public static void main(String[] args) {
        Person person = new Person("Hans", "Becker");
        person.print();

        Student student = new Student("Sepp", "Meier");
        student.setId(12345);
        student.print();

        Lehrer lehrer = new Lehrer("Hans", "Müller");
        lehrer.print();

    }
}