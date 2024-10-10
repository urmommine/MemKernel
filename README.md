# MemKernel
MemKernel is a kernel driver for Android. Originally created by [Jiang-Night](https://github.com/Jiang-Night/Kernel_driver_hack), it has been modified and fixed according to my personal needs. This driver reads and writes physical memory of the target process, effectively bypassing anti-cheats.

## Integration
2 ways you can integrate this driver to your kernel source (for compilation) using setup script:
* __Y__ : To build the driver as part of the kernel. (statically build within kernel).
```
curl -LSs "https://raw.githubusercontent.com/Poko-Apps/MemKernel/main/kernel/setup.sh" | bash -s Y
```
* __M__ : To build the driver as lkm (loadable kernel module).
```
curl -LSs "https://raw.githubusercontent.com/Poko-Apps/MemKernel/main/kernel/setup.sh" | bash -s M
```

**TIP** : By default the setup script generates random name for the driver (/dev/*randomname*) and as well as for the lkm (*randomname*_memk.ko), this is done to bypass existency check done via [*access(2)*](https://man7.org/linux/man-pages/man2/access.2.html) syscall. But you can override this behaviour by providing 2nd argument to the setup script like this:

```curl -LSs "https://raw.githubusercontent.com/Poko-Apps/MemKernel/main/kernel/setup.sh" | bash -s M myname```

## Compilation
Totally depends on the kernel source you're building (gki & non-gki). I leave this part upto you.

## How It Works
At a higher level:

This driver code (whether lkm or in-built within kernel) creates a [miscellaneous](https://www.kernel.org/doc/html/v4.14/driver-api/misc_devices.html) [character](https://linux-kernel-labs.github.io/refs/heads/master/labs/device_drivers.html) device driver in dev folder (/dev/drivername). A userspace app with root permission can talk to this driver (file) via [*ioctl(2)*](https://man7.org/linux/man-pages/man2/ioctl.2.html) syscall. The kernel part (driver) reads or writes the target memory behalf on userspace app and forward read data to userspace app to use.

## Limitations
* The read or write size is capped at 8192 bytes. This means that only 8192 bytes of data can be written or read at once.
* No validation layer exists, so any root users can use this driver (if they know the name and purpose of the driver). it's a critical security risk, **You have been warned: use it at your own risk**.

## Detection Vectors
Many common & uncommon techniques can be used to detect the presence of the device driver. in case if you're using lkm then module can also be detected.

  * Don't get confused, device driver and module(lkm) are two different things. whether it's loadable module or inbuilt within kernel our main goal is to create a device driver. the driver is just an interface which we'll use for communication from userspace.

But thankfully, many such detection vectors are already being bypassed if you're using a unique name for the driver (otherwise setup script generates random name anyways). This makes the project ideal for **personal use cases**, as the randomness occurs before compilation (in the setup script) rather than at runtime.

Additionally, I should mention that some older android and kernel versions allow access to certain critical files or folders that could expose the existence of the module or driver.

## Connect
Just in, you can join this [telegram group](https://t.me/memkernel) for discussing about possible detection vectors.

_[Don't Join For Kernel Compilation Purpose Otherwise You'll Be Banned]_
