## playing with scanlines

Experimentation with pushing vectors into a simple, json parsable hitgrid, using modified AGG algorithms.

A step toward:

  https://github.com/mapbox/mbtiles-spec/blob/master/1.1/utfgrid.md

To test do:

   make;
   ./run

You should see something like:

  { "grid":
  [
  "                                                                ",
  "                                                                ",
  "                                                                ",
  "                                                                ",
  "                                                                ",
  "                                                                ",
  "                                                                ",
  "                                                                ",
  "                                                                ",
  "                                                                ",
  "                                                                ",
  "                                                                ",
  "                                                                ",
  "             bbbbbbbbbbbb    ccc                                ",
  "             bbbbbbbbbbbb   ccccc                               ",
  "             bbbbbbbbbbbb   ccccc                               ",
  "      aa     bbbbbbbbbbbb  ccccccc                              ",
  "      aaaa   bbbbbbbbbbbb  ccccccc                              ",
  "     aaaaaaa bbbbbbbbbbbb  ccccccc                              ",
  "     aaaaaaaabbbbbbbbbbbb cccccccc                              ",
  "     aaaaaaaabbbbbbbbbbbb ccccccccc                             ",
  "       aaaaaabbbbbbbbbbbb ccccccccc                             ",
  "         aaaabbbbbbbbbbbb ccccccccc                             ",
  "           aabbbbbbbbbbbb ccccccccc                             ",
  "             bbbbbbbbbbbb ccccccccc                             ",
  "               aaaaaaaaaacccccccccc                             ",
  "                 aaaaaaaacccccccccc                             ",
  "                   aaaaaacccccccccc                             ",
  "                     aaaacccccccccc                             ",
  "                       aacccccccccc                             ",
  "                         cccccccccc                             ",
  "                         cccccccccc                             ",
  "                         cccccccccc                             ",
  "                         cccccccccc                             ",
  "                         cccccccccc                             ",
  "                         cccccccccc                             ",
  "                          ccccccccc                             ",
  "                          ccccccccc                             ",
  "                          ccccccccc                             ",
  "                          ccccccccc                             ",
  "                          ccccccccc                             ",
  "                          cccccccc                              ",
  "                           ccccccc                              ",
  "                           ccccccc                              ",
  "                           cccccc                               ",
  "                            ccccc                               ",
  "                            ccccc                               ",
  "                             ccc                                ",
  "                                                                ",
  "                                                                ",
  "                                                  dddddddddddddd",
  "                                                  dddddddddddddd",
  "                                                  dddddddddddddd",
  "                                                  dddddddddddddd",
  "                                                  dddddddddddddd",
  "                                                  dddddddddddddd",
  "                                                  dddddddddddddd",
  "                                                  dddddddddddddd",
  "                                                  dddddddddddddd",
  "                                                  dddddddddddddd",
  "                                                  dddddddddddddd",
  "                                                  dddddddddddddd",
  "                                                  dddddddddddddd",
  "                                                  dddddddddddddd",
  ]
  }