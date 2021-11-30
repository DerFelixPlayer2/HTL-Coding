package de.lolgamr17.projects.AutoPartProject;

import java.util.Arrays;

public class Order {
    final Item[] items;

    public Order(Item[] items) {
        this.items = items;
    }

    public boolean isFulfillable() {
        for (Item item : items)
            if (!item.isFulfillable())
                return false;
        return true;
    }

    public void process() {
        for (Item item : items)
            item.process();
    }

    public static class Item {
        Part part;
        int amt;

        public Item(Part part, int amt) {
            this.part = part;
            this.amt = amt;
        }

        public boolean isFulfillable() {
            return part.amount >= amt;
        }

        public void process() {
            part.amount -= amt;
        }
    }
}