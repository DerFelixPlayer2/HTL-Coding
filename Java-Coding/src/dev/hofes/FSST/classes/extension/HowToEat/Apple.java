package dev.hofes.FSST.classes.extension.HowToEat;

public class Apple extends Fruit implements Edible {

    public Apple(String color) {
        super(color);
    }

    @Override
    public String howToEat() {
        return "Apple: Make apple juice";
    }
}