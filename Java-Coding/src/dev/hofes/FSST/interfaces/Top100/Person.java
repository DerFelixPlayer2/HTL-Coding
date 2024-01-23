package dev.hofes.FSST.interfaces.Top100;

public record Person(String name, long money) {
    public String getName() {
        return name;
    }

    public long getMoney() {
        return money;
    }

    @Override
    public String toString() {
        return "Person{" +
                "name='" + name + '\'' +
                ", money=" + money +
                '}';
    }
}