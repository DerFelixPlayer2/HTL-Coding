package de.lolgamr17.strings;

import java.util.Arrays;

public class SatzUndWort {
    private final String word;
    private final String sentence;

    public SatzUndWort(String sentence, String word) {
        this.word = word;
        this.sentence = sentence;
    }

    public int count() {
        return sentence.split(word).length - 1;
    }

    public String remove() {
        return sentence.replace(word, "");
    }

    public String getSentence() {
        return sentence;
    }
}