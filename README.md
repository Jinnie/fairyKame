# Kame (FatKame)

Hi!

This is a fork of the miniKame, I'll use it to extend the functionality of my adaptation to the body of the robot.

# Goals:

- Offer a robot body which fits a 2s lipo, cheaper servos, a 6A BEC, a ultrasonic sensor, and that has an access chute for the battery 
- Have the functions separated into Controller-Processor-Executor
- Have a WebController which serves a simple page and gets called by ajax calls from this webpage for the robot actions
- Use the ultrasonic sensor for very simple "Spatzenhirn" autonomous mode where the bot avoids bumping into stuff

For details on the bot, please take a look at the [splendid original miniKame](https://github.com/bqlabs/miniKame).

# Setup guide:

- Set wifi id and password in webconnector.cpp
- Calibrate your robot by setting trim height (for robot height) and trim spread (legs angle) in leg-2dof.cpp. Or set to (0, 0) and then position the servos.
- Explore basic command options at minicame.cpp. Create your own combinations of gaits, phases, directions.
- Explore the gaits in mind/gaits. Create your own.
- Pull requests for gaits are more than welcome. Any other contributions too.

# More Info and Pictures

Please visit
http://www.thingiverse.com/thing:1483635

# License

Relative of [miniKame](https://github.com/bqlabs/miniKame) and [Kame](https://github.com/bqlabs/kame)

<p align="center">
<img src="doc/images/by-sa.png" width="200" align = "center">
</p>

# Other

Total chillout-hobby project
