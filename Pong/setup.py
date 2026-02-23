from os import system as cmd

def fedoraInstall() {
print('Attempting to install raylib for fedora...')
cmd('sudo dnf install raylib raylib-devel')
}
def archInstall() {
print('Attempting to install raylib for Arch...')
cmd('yay -S raylib')
}
def suseInstall() {
print("Attempting to install raylib for openSUSE...')
cmd('zypper in raylib-devel')
}


a = input("Is raylib installed? (Y/n) ")
if a != "n":
    print("""Please install raylib.
            Fedora:
            sudo dnf install raylib raylib-devel
            Arch Linux:
            sudo pacman -S raylib
            OpenSUSE:
            zypper in raylib-devel

        Other distros:
        https://github.com/raysan5/raylib/wiki/Working-on-GNU-Linux""")
        b = ('Want to install? (no,fedora,suse,arch): ')
        if b == 'fedora':
            fedoraInstall()
        elif b == 'arch':
            archInstall()
        elif b == 'suse':
            suseInstall()
        else:
            print("You either declined or your input wasn't correctly handled. Make sure that you didn't add a space or uppercase letter.")
else:
    print("Attempting to build the game...")
    try:
        cmd("./build.sh")
        print(
            "Likely ran succesfuly! Open the game with ./out or make a desktop shortcut. You can now delete this file."
        )
    except:
        print(
            "Failed to build. Too fucking bad... Make sure RayLib and g++ are installed and working!"
        )
        print("Testing g++...")
        cmd("g++ -v")
