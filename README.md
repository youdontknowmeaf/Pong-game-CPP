# INSTALLATION

1. ``git clone https://github.com/youdontknowmeaf/Pong-game-CPP.git``
2. ``cd Pong-game-CPP/Pong``
3. ``python3 setup.py``
4. To launch the game you write ``./out`` and to recompile it you can:
- ``make`` or ``g++ main.cpp -o Pong -lraylib`` or ./build.sh (for main version)
- ``gcc lightweigh-pong.c -o Lightweigh-Pong -lraylib -lm`` (for lightweigh version)

# GOALS
- Recreating 1972 pong with QOL features
- Making a game so simple it can run on anything with raylib.
- Making a fun project that others can learn from by interacting with user friendly config.

# CHANGELOG
- **pre-v1**:
- First playable version
- **v1**:
- Created user friendly configuration
- Created python setup
- Created shell auto-compile
- Reset the pre-defined colors to RED + BLUE
- **v1.1**:
- Added additional features to configuration
- Improved the python script
- Improved shell auto-compile
- Improved the readibility of the configuration
- Rewrote the README.md 
- **v1.1.1**
- Added compile instructions for lightweigh pong
- Added lightweigh pong
- Minor cosmetic changes
- **v1.1.2**
- The game's speed is no longer dependend on FPS
- **v1.2**
- Created a Makefile build system for convinience
- Implemented Zen mode
- Implemented Random Ball Speed when it hits something
