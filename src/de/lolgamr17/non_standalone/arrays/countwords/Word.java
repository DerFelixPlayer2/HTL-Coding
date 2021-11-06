package de.lolgamr17.non_standalone.arrays.countwords;

public class Word {
    private final String word;
    private long count;

    public Word(String word) {
        this.word = word;
        this.count = 1;
    }

    public long getCount() {
        return count;
    }

    public void inc() {
        count++;
    }

    public String getWord() {
        return this.word;
    }
}