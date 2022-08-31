package de.lolgamr17.classes;

import org.jetbrains.annotations.Contract;
import org.jetbrains.annotations.NotNull;

public class Time {
    int hours;
    int minutes;

    public Time(int hours, int minutes) {
        this.hours = hours;
        this.minutes = minutes;
    }

    public void add(@NotNull Time time) {
        this.hours += time.hours;
        this.minutes += time.minutes;
        if (this.minutes >= 60) {
            this.hours += this.minutes / 60;
            this.minutes = this.minutes % 60;
        }
    }

    public Time difference(@NotNull Time time) {
        int hours = this.hours - time.hours;
        int minutes = this.minutes - time.minutes;
        if (minutes < 0) {
            hours--;
            minutes += 60;
        }
        return new Time(hours, minutes);
    }

    @Contract(pure = true)
    public static int toMinutes(@NotNull Time time) {
        return time.hours * 60 + time.minutes;
    }

    @Contract(pure = true)
    public int toMinutes() {
        return this.hours * 60 + this.minutes;
    }
}