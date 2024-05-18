import sys
import hid
from pyudev import Context, Monitor
from typing import Callable
from time import sleep


def _try_connect(deviceVid:int, devicePid:int,
                 callback:Callable[[hid.Device],bool], errCb:Callable[[Exception], bool], disconnCb:Callable[[Exception],bool]):
    connected = False
    try:
        with hid.Device(deviceVid, devicePid) as h:
            connected = True
            return callback(h)

    except hid.HIDException as e:
        if connected:
            if not disconnCb(e):
                return False

    except Exception as e:
        if not errCb(e):
            return False
    return True


# callback returns true for reconnect, false for disconnect
# will attempt reconnect on crash
def await_connection(deviceVid:int, devicePid:int,
                 callback:Callable[[hid.Device],bool], errCb:Callable[[Exception], bool], disconnCb:Callable[[Exception],bool]):
    # try to connect at startup
    res = _try_connect(deviceVid, devicePid, callback, errCb, disconnCb)
    if not res:
        return


    ctx = Context()
    ctx.list_devices(subsystem='usb')

    monitor = Monitor.from_netlink(ctx)
    monitor.filter_by(subsystem='usb')


    while True:
        for device in iter(monitor.poll, None):
            if device == None:
                continue

            if device.action == 'bind' and 'PRODUCT' in device and 'BUSNUM' in device:
                prod = device.get("PRODUCT")
                if not isinstance(prod, str):
                    continue
                x = prod.split("/")
                if len(x) < 2:
                    continue
                try:
                    vid = int(x[0], 16)
                    pid = int(x[1], 16)
                except:
                    continue

                if vid != deviceVid  or pid != devicePid:
                    continue

                res = _try_connect(deviceVid, devicePid, callback, errCb, disconnCb)
                if not res:
                    return

def device_runtime(h:hid.Device, pipeName: str):
    with open(pipeName, 'rb', buffering=0) as f:
        while True:
            x = f.read(1)
            h.write(x + b"\0") # 2 bytes must be send, second byte is thrown out by device
            sleep(0.01)

def errorCb(e:Exception):
    return False

def disconnectCb(_:Exception):
    return True


if __name__ == '__main__':
    # atmega16u2 usb info
    a16u2monitorVid = 0x2341
    a16u2monitorPid = 0x484C

    if len(sys.argv) < 2:
        raise Exception("Named Pipe Required, Please Run with shell.sh")
    pipe = sys.argv[1]

    await_connection(a16u2monitorVid, a16u2monitorPid, lambda h: device_runtime(h, pipe), errorCb, disconnectCb)


