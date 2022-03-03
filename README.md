# Kame (FairyKame)

Hi!

FairyKame is a fork of the great [fatKame](https://github.com/Blomdoft/fatKame) project, which adds a nice layer of code organization on top of the magnificent [miniKame](https://github.com/JavierIH/miniKame) robot. I am forking it with the idea to rework the code even more, in a way that will allow for very easy modification of the current gaits and moves and creation of new ones. I want to try building a community around it, so I am opening the Issues section for all to comment, request features, report bugs. There I will be adding my ideas as feature request issues. Any contribution, as new issues, or code, especially with new gaits and robot moves are more than welcome.
If you have any questions, please post them to the Issues for now. If needed, I'll open the Github Discussions later.
I will also be dropping fatKame's sonic sensor support and auto mode for now, they belong better there, and as I'll be adding a lot of new code, I need to reduce the scope a little bit.

# Goals

## Direct Goals:
- Make it easy for everyone, with even little coding skill, to create new gaits and moves.
- Foster a positive community around the Kame family of robots.

## Stretch Goals:
- Improve on the control app.
- Improve the control app even more. Try to create Android/iOS app (in React Native) which controls the robot over BT.
- Experiment in creating lighter, smaller body.
- Abstract the control board - make it possible to alternatively use ESP32 and even explore building for Raspberry Pi.

# Setup guide:

- Set wifi id and password in webconnector.cpp
- If needed, finely calibrate your robot by setting trim height (for robot height) and trim spread (legs angle) in leg-2dof.cpp.
- You can build/deploy in PlatformIO, or in the Arduino dev environment (not tested, but should work, feedback is welcome if you try it)

# Contribution guide:

There is no small contribution. Anything counts - a question, vague idea, anything. Post your thoughts as Issues and we'll get in discussion about them.

- Explore basic command options at minicame.cpp. Create your own combinations of gaits, phases, directions.
- Explore the gaits in mind/gaits. Create your own.
- Suggest your own modifications on the robot body, or share ideas.
- Be patient. Opensource contribution takes time and dialog.
- If you have ideas that are diverging from ours, or we're not accepting yours, fork and go! Respect the License.

# More Info and Pictures

For details on the bot, please take a look at the [splendid original miniKame](https://github.com/JavierIH/miniKame).

Please visit fatKame's Thingiverse page:
http://www.thingiverse.com/thing:1483635

# License

Relative of [fatKame](https://github.com/Blomdoft/fatKame), [miniKame](https://github.com/JavierIH/miniKame) and [Kame](https://github.com/JavierIH/kame)

<p align="center">
<img src="doc/images/by-sa.png" width="200" align = "center">
</p>

# Other

Total chillout-hobby project
