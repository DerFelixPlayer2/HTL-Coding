package de.lolgamr17.FSST.projects.AutoPartProject;

public class Part {
    long id;
    String description;
    int amount;

    public Part(long id, String description, int amount) {
        this.id = id;
        this.description = description;
        this.amount = amount;
    }

    public int descLength() {
        return description.length();
    }
}