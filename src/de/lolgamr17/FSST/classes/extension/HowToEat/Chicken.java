package de.lolgamr17.FSST.classes.extension.HowToEat;

public class Chicken extends Animal implements Edible {
    public Chicken(int weight) {
        super(weight);
    }


    @Override
    public String howToEat() {
        return "Chicken: Fry it";
    }
}