package dev.hofes.Classes;

import org.jetbrains.annotations.Contract;
import org.jetbrains.annotations.NotNull;

public class Clock {
    boolean using24hCycle = true;
    boolean am = true;
    int hours;
    int minutes;

    public Clock(int hours, int minutes) {
        this.hours = hours % 24;
        this.minutes = minutes % 60;
    }

    public Clock(int minutes) {
        this(minutes / 60, minutes % 60);
    }

    public Clock() {
        this(7, 50);
    }

    public void setTo12() {
        this.using24hCycle = false;

        this.am = this.hours < 12;
        if (this.hours > 12) {
            this.hours -= 12;
        }
    }

    public void setTo24() {
        this.using24hCycle = true;

        if (this.hours >= 12) {
            this.hours -= 12;
        }
    }

    @Contract(pure = true)
    public String toString() {
        if (this.using24hCycle) {
            return String.format("%02d:%02d %s", this.hours, this.minutes, this.am ? "AM" : "PM");
        }
        return String.format("%02d:%02d", hours, minutes);
    }

    public int advance(int minutes) {
        this.minutes += minutes;
        if (this.minutes >= 60) {
            this.hours += this.minutes / 60;
            this.minutes %= 60;

            if (this.using24hCycle && this.hours >= 24) {
                this.hours %= 24;
                return this.hours;
            } else if (!this.using24hCycle && this.hours >= 12) {
                do {
                    this.hours -= 12;
                    this.am = !this.am;
                } while (this.hours >= 12);
            }
        }
        return 0;
    }

    @Contract(pure = true)
    public int diff(@NotNull Clock other) {
        int h1, h2;
        if (this.using24hCycle) {
            h1 = this.hours;
        } else {
            if (this.am) {
                h1 = this.hours;
            } else {
                h1 = this.hours + 12;
            }
        }

        if (other.using24hCycle) {
            h2 = other.hours;
        } else {
            if (other.am) {
                h2 = other.hours;
            } else {
                h2 = other.hours + 12;
            }
        }

        int diff = h1 - h2;
        if (diff < 0) {
            diff += 24;
        }
        diff *= 60;
        diff += this.minutes - other.minutes;
        return diff;
    }

    @NotNull
    @Contract(pure = true)
    public Clock sum(@NotNull Clock other) {
        int h1, h2;
        if (this.using24hCycle) {
            h1 = this.hours;
        } else {
            if (this.am) {
                h1 = this.hours;
            } else {
                h1 = this.hours + 12;
            }
        }

        if (other.using24hCycle) {
            h2 = other.hours;
        } else {
            if (other.am) {
                h2 = other.hours;
            } else {
                h2 = other.hours + 12;
            }
        }

        int diff = h1 + h2;
        if (diff >= 24) {
            diff %= 24;
        }
        return new Clock(diff, this.minutes + other.minutes);
    }
}