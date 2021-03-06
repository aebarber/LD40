# LD40

SpeedFishing - My project for Ludum Dare 40!

## Theme

The More You Have, The Worse It Is

## License

MIT (see LICENSE)

## Description

The player drives a boat out of a harbor on a fishing run. The goal is to
collect the maximum number of fish possible. There will be a time limit, and by
then end of the time, you must be back in port or your boat will be destroyed.

On the water, you will be able to pick up fish items, which will increase your
score, but also the weight of your boat. While the boat will not sink from sheer
weight alone, the higher your weight, the slower the boat will be to accelerate,
the slower it's top speed will be, and the slower it will be to turn and brake.

Because of these things, the increased load of fish on board the boat will make
it more difficult to safely avoid the variety of obstacles that you will
encounter while at sea, and the more difficult it may be to reach the harbor in
time to deliver your cargo at all.

The world will be procedurally generated, and there will be only one level. Thus
it is an arcade-style game tracking high scores based on the player's arrival
in the harbor.

A variety of different game modes MAY be implemented, providing different time
limits and a different mix of obstacles, but that will be on a "time-allowing"
basis. This may get implemented post-game-jam.

## Development

This time around, breaking with the tradition of developing my Ludum Dare games
as JavaScript web games using Phaser, I have opted to develop this one using
SFML in C++. This should give me a lot more flexibility at a lower level, but it
will undoubtedly present new challenges that I haven't had to face in past Ludum
Dare entries, especially in terms of compiling and distributing the game across
multiple platforms. While I have done some C++ game development in the past,
I have yet to publish a completed C++ game, and I have never worked with SFML
prior to starting this project, so that will present some challenge as well.
Here's to hoping everything goes well!

This year, my plan is to focus more heavily on rapid prototyping than ever
before in the past. In my last Ludum Dare (39), I focused far too heavily on
detailed design before programming anything usable to test my ideas and theories
on. As a result, I underestimated the complexity of key parts of my game design
and found them difficult to work around in the limited time frame available.
This time I'd like to give myself a chance to detect those design flaws before
overcommiting to the problematic concept at all.

The underlying game engine, at a layer of abstraction above SFML, is based on
the early code from my Territory game engine (and game), which I manually ported
to SFML from GLFW and then built improvements on top of that, since as of
writing, the Territory engine is far from complete. Many of these changes are
likely to get sent back upstream to improve Territory.

The game engine itself utilizes a pushdown automata game state system supporting
layer transparency individually for the render, update, and input code. The game
loop utilizes the original thread as the rendering/input loop, which prevents
segfaults in the rendering and event handling code, while update code is run in
a separate update thread, which has the potential to provide slightly higher
processing throughput on multi-core systems (although it does introduce a host
of nuisances that would make it generally not worth the effort in a simpler game
like this one, but since Territory already had the feature, I felt it was easier
to simply leave it in place). This multi-threading allows us to easily run a
fixed-time-step update loop, while also running a variable time-step rendering
loop.

To my fellow Ludum Dare participants, good luck, and I'm looking forward to
playing your games soon!
