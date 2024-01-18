package de.lolgamr17.FSST.interfaces.dictionary;

public record Entry(String english, String german) {
    public String getEnglish() {
        return english;
    }

    public String getGerman() {
        return german;
    }
}