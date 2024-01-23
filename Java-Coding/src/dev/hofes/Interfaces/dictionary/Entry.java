package dev.hofes.Interfaces.dictionary;

public record Entry(String english, String german) {
    public String getEnglish() {
        return english;
    }

    public String getGerman() {
        return german;
    }
}