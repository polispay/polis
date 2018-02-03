Mac OS X Build Instructions and Notes
====================================
<<<<<<< HEAD
This guide will show you how to build polisd (headless client) for OSX.

Notes
-----

* Tested on OS X 10.7 through 10.11 on 64-bit Intel processors only.

* All of the commands should be executed in a Terminal application. The
built-in one is located in `/Applications/Utilities`.
=======
The commands in this guide should be executed in a Terminal application.
The built-in one is located in `/Applications/Utilities/Terminal.app`.
>>>>>>> pr/6

Preparation
-----------
Install the OS X command line tools:

`xcode-select --install`

When the popup appears, click `Install`.

Then install [Homebrew](https://brew.sh).

Dependencies
----------------------

    brew install automake berkeley-db4 libtool boost --c++11 miniupnpc openssl pkg-config protobuf qt libevent

If you want to build the disk image with `make deploy` (.dmg / optional), you need RSVG

    brew install librsvg

NOTE: Building with Qt4 is still supported, however, doing so could result in a broken UI. Therefore, building with Qt5 is recommended.

<<<<<<< HEAD
### Building polis Core
=======
Build Dash Core
------------------------
>>>>>>> pr/6

1. Clone the Dash Core source code and cd into `dash`

<<<<<<< HEAD
        git clone https://github.com/polispay/polis.git
        cd polis

2.  Build polis Core:
    This will configure and build the headless polis binaries as well as the gui (if Qt is found).
    You can disable the gui build by passing `--without-gui` to configure.
=======
        git clone https://github.com/dashpay/dash
        cd dash

2.  Build Dash Core:

    Configure and build the headless dash binaries as well as the GUI (if Qt is found).

    You can disable the GUI build by passing `--without-gui` to configure.
>>>>>>> pr/6

        ./autogen.sh
        ./configure
        make

3.  It is recommended to build and run the unit tests:

        make check

<<<<<<< HEAD
4.  (Optional) You can also install polisd to your path:
=======
4.  You can also create a .dmg that contains the .app bundle (optional):
>>>>>>> pr/6

        make deploy

Running
-------

<<<<<<< HEAD
1. Make sure you installed everything through Homebrew mentioned above
2. Do a proper ./configure --enable-debug
3. In Qt Creator do "New Project" -> Import Project -> Import Existing Project
4. Enter "polis-qt" as project name, enter src/qt as location
5. Leave the file selection as it is
6. Confirm the "summary page"
7. In the "Projects" tab select "Manage Kits..."
8. Select the default "Desktop" kit and select "Clang (x86 64bit in /usr/bin)" as compiler
9. Select LLDB as debugger (you might need to set the path to your installation)
10. Start debugging with Qt Creator

Creating a release build
------------------------
You can ignore this section if you are building `polisd` for your own use.

polisd/polis-cli binaries are not included in the polis-Qt.app bundle.

If you are building `polisd` or `polis Core` for others, your build machine should be set up
as follows for maximum compatibility:
=======
Dash Core is now available at `./src/dashd`

Before running, it's recommended you create an RPC configuration file.

    echo -e "rpcuser=dashrpc\nrpcpassword=$(xxd -l 16 -p /dev/urandom)" > "/Users/${USER}/Library/Application Support/DashCore/dash.conf"

    chmod 600 "/Users/${USER}/Library/Application Support/DashCore/dash.conf"
>>>>>>> pr/6

The first time you run dashd, it will start downloading the blockchain. This process could take several hours.

You can monitor the download process by looking at the debug.log file:

<<<<<<< HEAD
Once dependencies are compiled, see [doc/release-process.md](release-process.md) for how the polis Core
bundle is packaged and signed to create the .dmg disk image that is distributed.
=======
    tail -f $HOME/Library/Application\ Support/DashCore/debug.log
>>>>>>> pr/6

Other commands:
-------

<<<<<<< HEAD
It's now available at `./polisd`, provided that you are still in the `src`
directory. We have to first create the RPC configuration file, though.

Run `./polisd` to get the filename where it should be put, or just try these
commands:

    echo -e "rpcuser=polisrpc\nrpcpassword=$(xxd -l 16 -p /dev/urandom)" > "/Users/${USER}/Library/Application Support/polisCore/polis.conf"
    chmod 600 "/Users/${USER}/Library/Application Support/polisCore/polis.conf"
=======
    ./src/dashd -daemon # Starts the dash daemon.
    ./src/dash-cli --help # Outputs a list of command-line options.
    ./src/dash-cli help # Outputs a list of RPC commands when the daemon is running.

Using Qt Creator as IDE
------------------------
You can use Qt Creator as an IDE, for dash development.
Download and install the community edition of [Qt Creator](https://www.qt.io/download/).
Uncheck everything except Qt Creator during the installation process.
>>>>>>> pr/6

1. Make sure you installed everything through Homebrew mentioned above
2. Do a proper ./configure --enable-debug
3. In Qt Creator do "New Project" -> Import Project -> Import Existing Project
4. Enter "dash-qt" as project name, enter src/qt as location
5. Leave the file selection as it is
6. Confirm the "summary page"
7. In the "Projects" tab select "Manage Kits..."
8. Select the default "Desktop" kit and select "Clang (x86 64bit in /usr/bin)" as compiler
9. Select LLDB as debugger (you might need to set the path to your installation)
10. Start debugging with Qt Creator

<<<<<<< HEAD
    tail -f $HOME/Library/Application\ Support/polisCore/debug.log
=======
Notes
-----
>>>>>>> pr/6

* Tested on OS X 10.8 through 10.12 on 64-bit Intel processors only.

<<<<<<< HEAD
    ./polisd -daemon # to start the polis daemon.
    ./polis-cli --help  # for a list of command-line options.
    ./polis-cli help    # When the daemon is running, to get a list of RPC commands
=======
* Building with downloaded Qt binaries is not officially supported. See the notes in [#7714](https://github.com/bitcoin/bitcoin/issues/7714)
>>>>>>> pr/6
