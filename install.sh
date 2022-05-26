#!/bin/bash

THRUSH_TARGET_EXE="42sh"
THRUSH_TARGET="/bin/thrush"
THRUSH_TARGET_DIRECTORY="thrushell"
THRUSH_SOURCE="https://github.com/Saverio976/fortytwo.sh.git"
THRUSH_SOURCE_INSTALL="https://raw.githubusercontent.com/Saverio976/fortytwo.sh/install.sh"

if [[ $EUID -ne 0 ]]; then
    echo "Installation must be run as root"
    echo "if you want to see the installation source: $THRUSH_SOURCE_INSTALL"
    exit 1
fi

if ! command -v git &> /dev/null; then
    echo "You must have git to install Thru.sh"
    exit 1
fi

if ! command -v make &> /dev/null; then
    echo "You must have git to install Thru.sh"
    exit 1
fi

cd /tmp

echo "Installation of source code ..."
git clone $THRUSH_SOURCE $THRUSH_TARGET_DIRECTORY
cd $THRUSH_TARGET_DIRECTORY
echo "Installation of source code ended"

echo "Compilation of binary ..."
make
echo "Compilation of binary ended"

sudo mv $THRUSH_TARGET_EXE $THRUSH_TARGET
echo "Binary moved to $THRUSH_TARGET"

sudo bash -c "echo $THRUSH_TARGET >> /etc/shells"

echo -e "\nDo you want to make it your default shell [y/n]? "
read IS_DEFAULT
if [[ "$IS_DEFAULT" == "y" || "$IS_DEFAULT" == "Y" ]]; then
    chsh -s $THRUSH_TARGET
    echo "Thrushell will be your next default shell after a reboot"
else
    echo "you can make it your default shell with:"
    echo "chsh -s $THRUSH_TARGET"
fi

echo "Thanks for the installation of Thrushell"
