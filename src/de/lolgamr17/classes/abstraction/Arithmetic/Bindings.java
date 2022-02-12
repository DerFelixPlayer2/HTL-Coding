package de.lolgamr17.classes.abstraction.Arithmetic;

import java.util.HashMap;
import java.util.Map;

public class Bindings {
    private final Map<String, Integer> bindings = new HashMap<>(0);

    public void set(String s, int i) {
        bindings.put(s, i);
    }

    public int get(String s) throws RuntimeException {
        if (!bindings.containsKey(s)) throw new RuntimeException("Variable " + s + " not bound");
        return bindings.get(s);
    }
}