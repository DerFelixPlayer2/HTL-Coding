package de.lolgamr17.standalone.extension.HowToEat;

public class HowToEatMain {
    public static void main(String[] args) {
        Chicken chicken = new Chicken(50);
        System.out.println(chicken.howToEat());

        Apple apple = new Apple("red");
        System.out.println(apple.howToEat());

    }
}