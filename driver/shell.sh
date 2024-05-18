#!/bin/bash

# get directory of this script
pushd "$(dirname "$0")"
SCRIPT_DIR="$(pwd)"
popd

# create a temporary named pipe
PIPE=$(mktemp -u)
mkfifo $PIPE

cleanup() {
    rm -f $PIPE
}

# sigterm whole process group sigint/sigterm
trap "trap - SIGTERM && kill -- -$$" SIGINT SIGTERM EXIT
# cleanup tmp named pipe on exit
trap cleanup EXIT

# run usb controller in background
python3 $SCRIPT_DIR/usb-controller.py $PIPE &
# run interactive shell and send entire script to pipe
script --command "sh -i" -f $PIPE

