#!/bin/bash

DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"

if [[ "${BASH_SOURCE[0]}" == "${0}" ]]; then
  $ERROR "ERROR: This setup command must be sourced!"
  exit
fi

if [ -n $SCRAM_ARCH ]; then
    echo "I don't think you setup CMSSW yet."
    echo "Please setup CMSSW first before running this script."
    return
fi

cd fastjet-*
./configure prefix=$PWD/../fastjet-install
make
make check
make install
cd ../
echo "Execute the following command to add 'fastjet-config' available under your PATH"
echo "export PATH=\$PWD/fastjet-install/bin:\$PATH"

#eof
