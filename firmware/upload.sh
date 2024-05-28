# get directory of this script
pushd "$(dirname "$0")"
python3 ./fonts/process-font.py
arduino-cli compile --fqbn "HoodLoader2:avr:HoodLoader2atmega16u2" -u --programmer "arduinoasisp" -p /dev/ttyUSB0
popd

