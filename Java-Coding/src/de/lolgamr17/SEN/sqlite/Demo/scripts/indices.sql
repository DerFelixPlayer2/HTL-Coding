CREATE UNIQUE INDEX "CDId" ON "CD" ("CDId");
CREATE UNIQUE INDEX "KId" ON "Kuenstler" ("KId");
CREATE UNIQUE INDEX "TrackId" ON "Song" ("CDId", "Track");
CREATE INDEX "ErscheinungsjahrIdx" ON "CD" ("Erscheinungsjahr");
