#!/bin/bash
RED="\033[31m"
MAGENTA="\033[35m"
GREEN="\033[32m"
YELLOW="\033[33m"
CYAN="\033[36m"
BLUE="\033[34m"
RESET="\033[0m"
YELLOW_BOLD="\033[1;33m"
BLEU_BOLD="\033[1;34m"

THRUSH_TARGET_EXE="42sh"
THRUSH_TARGET="/bin/thrush"
THRUSH_TARGET_DIRECTORY="thrushell"
THRUSH_SOURCE="https://github.com/Saverio976/fortytwo.sh.git"
THRUSH_SOURCE_INSTALL="https://raw.githubusercontent.com/Saverio976/fortytwo.sh/install.sh"
THRUSH_SOURCE_BASE_ASSETS="https://raw.githubusercontent.com/Saverio976/fortytwo.sh/main/assets/"
echo -n -e $BLEU_BOLD
echo "
............................................................
............................................................
............................................................
............................................................
............................................................
............................................................
............................................................
............................................................
................°°°°°°°...........................°°°°°°°°°°
.............°°**OOo**ooo*.......°°°°°°°°°°°°°°°°°°°°°°***°*
°°°°°°***°**o*°  *@@° °.°oo*°°°°°°°°°°°°°°°*****************
***************° .O@o°*#°*OO***********************ooooooooo
oo**************°  O@° O@°*OO******ooooooooooooooooooooooooo
ooooooooooooooooo*..#o.OO.°ooooooooooooooooooooooooooooooooo
oooooooooooooooooo..°*#O..*ooOoooooooooooooooooooooooooooooo
oooooooooooooooooo  °oO° °oooOoooooooooOooooooooOOOooooooooo
oooooOOooooooooooo . °  °°*ooooooooooooooooooooooOoooooooooo
oooooooooooooooooo.°°°°°*ooooooo*****oooooooOOOoooo**ooooooo
OOOOOOooooooooooo* °° .  °*Oo*o******oooooOOOOOoooo***ooOOOO
OOOOOOOOOOOOOOOOo° .*. .*°o**°°**oooooooooooOoooooooo**ooooo
OOOOOOOOOOOOOOOOo.°. .o°°°. °**oo*oooOOoooooooooooooooooo***
OOOOOOOOOOOOOOOO* °°* *°°.. °°oOOoooooooooooooooooooooooooo*
OOOOOOOOOOOOOOOOo  *°* °  o .o*OO#OOOoooooOOOOoooooooooooooo
OOOOOOOOOOOOOoooo  **  o. .*.*ooOOO#OOOoOOOOOOOooOOOOooooooO
OOOOoOOOOOOOOoooO°   O .o*  ** *OOO#OOOOOOOOOOoooooooooooooo
oOOOOOOOOOOOOOOoOo** °. *o°**o **#@#@OOOOOoooooooooooooooooo
*ooooooOOOOOOOOOOOo°. ° °°   °o..°O##@@#OOOOOOOOOOOOOooooOOO
ooOooooooooooooooOOo*° o *.o.°. °. °*#@@@###OoooOooooOooo*oo
###OOO#OOOoooooooooo*°°° °*.°  . °. .°oO##@@#oooo**oOOOo**oo
#@@##OOOOOOooooOOOOOo***..°..  °°o°*°...*oO@@@oooooooooooO##
####OOoooooooOOOOOOoooooo*...°°°°  °.**°o**o#@@O*ooooooOOOOO
OOOO#OOOo**oOOooOOoooOooooo**°°°°  .°***°*ooooO@O***oooooOOO
OOOOOOOooooooooOoooOoooooOo*oo*. .   *oooo****oO#OOo*°*oOOOO
oooOooooOOOooOooooooooOOooooo**o° .   *oooo****oO###O*°oOOOO
ooOOooooooooooooooooooOOoooOooooO° *   oo*oooOoOoOO#Oo°*ooo*
ooooooooooooooooooooooo**oooooooo°oOo  oooOOOOOooOOO#OO**ooo
oooooooooOoooooOOOoOoooooooOooOo.*oo* ooooo*oOOOOooO###o°oOO
ooooooOOooOooooooo*oOoooooooo**.°ooo..ooOoooOOoooooOOOOO°°*o
OOOoOoooooo*ooo*ooooooo**ooooo °OOo* oOooOOoOOOooOoOOoO#O***
ooooOoooooo**°*oooooooOOooo*o°.Oooo.°OoooOOoOOOooooOOoOOoooO
OooOOOooOoo°*ooo**oooOo*°   .°*oo#O O#OooOOOOOOOOoOOoooooooo
oOoooo*oooo**oOooooooo**°  .....*O*°O####@#OOOOOooOoooooOo°°
OOoOooo**o*ooOOooo**o*°..  ....°°oOoooo*ooooooooOo*oOOooooo*
OO***ooooOo*oooooOOoo°°°.  ....°*ooooo*°*o***ooooOoooOOOOOoo
#ooOOo*OOooo***oooOOooooo****oo**°*ooo**ooo**ooo*ooOoooOo°*o
OOoOOooooOooooooooooo****ooo*oooo****ooo**ooo*ooooOOooooooo*
Ooooooo*oOooo**oOOoooooo*o**ooooo**o*o*°***oooooo*******o*°°
o***oooo*o*o*°oOoOOo**oooo****ooooo***o***°°*ooooooOoo*°°°*o
**oooooooo**°*ooOOOoooooooo*ooooo***ooOOoo**oooooooOo°.°*oOO
oooooo***oo*oooooooooooooo*oooooo**oooooooooooOo*oo*°.°oOooo"
echo -e $RESET

echo "if you want to see the installation source: $THRUSH_SOURCE_INSTALL"
sleep 0.5

if ! command -v git &> /dev/null; then
    echo "You must have git to install Thru.sh"
    exit 1
fi

if ! command -v make &> /dev/null; then
    echo "You must have git to install Thru.sh"
    exit 1
fi

echo -n -e $BLEU_BOLD
echo -e "Welcome to the installation script of $CYAN Thrushell"
echo -n -e $RESET
sleep 0.2

cd /tmp
echo ""


echo "Installation of source code ..."
git clone $THRUSH_SOURCE $THRUSH_TARGET_DIRECTORY
cd $THRUSH_TARGET_DIRECTORY
echo "Installation of source code ended"
sleep 0.2

echo ""

echo "Compilation of binary ..."
make
echo "Compilation of binary ended"
sleep 0.2

echo ""

echo "Please enter sudo password: (the binary will be moved from $THRUSH_TARGET_EXE to $THRUSH_TARGET)"
sudo mv $THRUSH_TARGET_EXE $THRUSH_TARGET
echo "Binary moved to $THRUSH_TARGET"
sleep 0.1

sudo bash -c "echo $THRUSH_TARGET >> /etc/shells"

echo ""

echo -e "\nDo you want to make it your default shell [y/n]? "
read IS_DEFAULT
if [[ "$IS_DEFAULT" == "y" || "$IS_DEFAULT" == "Y" ]]; then
    echo "Do you confirm this choice [y/n]? "
    read IS_DEFAULT_CONFIRM
    if [[ "$IS_DEFAULT" == "y" || "$IS_DEFAULT" == "Y" ]]; then
        chsh -s $THRUSH_TARGET
        echo "Thrushell will be your next default shell after a reboot"
    else
        echo "you can make it your default shell with:"
        echo "chsh -s $THRUSH_TARGET"
    fi
else
    echo "you can make it your default shell with:"
    echo "chsh -s $THRUSH_TARGET"
fi

echo -e "$GREEN""Thanks for the installation of Thrushell $RESET"
sleep 0.2

echo "Do you want to customize it [y/n]?"
read CUSTOM_C
echo "" > $HOME/.thrushrc
if [[ "$CUSTOM_C" != "y" && "$CUSTOM_C" != "Y" ]]; then
    exit 0
fi

echo ""

if command -v curl &>/dev/null; then
    echo "First : Do you want Nicolas (n), Clément (c), or the Void (v) ?"
    read CHOICE_C
    if [[ "$CHOICE_C" == "n" ]]; then
        echo "curl -fsSL ${THRUSH_SOURCE_BASE_ASSETS}nico.txt" >> $HOME/.thrushrc
    elif [[ "$CHOICE_C" == "c" ]]; then
        echo "curl -fsSL ${THRUSH_SOURCE_BASE_ASSETS}clem.txt" >> $HOME/.thrushrc
    fi
fi

echo ""

echo "Do you want a custom message when you lanch this shell ?"
echo "(write nothing for no message)"
read CHOICE_C
if [[ "$CHOICE_C" != "" ]]; then
    echo "echo -e $CHOICE_C" >> $HOME/.thrushrc
fi

echo ""

echo "You can always customize the startup script"
echo "You just have to modify $HOME/.thrushrc file"
