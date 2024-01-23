package dev.hofes.DesignPatterns.FassadePattern.Music;

class MusikspielerFassade {
    private final Playlist playlist;
    private final Equalizer equalizer;
    private final Lautstaerkeregler volume;

    public MusikspielerFassade(Playlist playlist, Equalizer equalizer, Lautstaerkeregler volume) {
        this.playlist = playlist;
        this.equalizer = equalizer;
        this.volume = volume;
    }

    public void play() {
        playlist.play();
    }

    public void stop() {
        playlist.stop();
    }

    public void setRockMusicMode() {
        equalizer.setBass(50);
        equalizer.setTreble(60);
        volume.setVolume(100);
    }

    public void setClassicMusicMode() {
        equalizer.setBass(20);
        equalizer.setTreble(50);
        volume.setVolume(100);
    }
}