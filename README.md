# MemKernel
MemKernel is a Kernel Driver for Android.
Created by [Jiang-Night](https://github.com/Jiang-Night/Kernel_driver_hack), modified according to my personal need.
This driver Reads, Writes physical memory of target process (effectively bypassing anticheats).

## Integration
3 ways you can integrate this driver to your kernel source (for compilation) using setup script:
* __Y__ : To build the source as part of the kernel. (statically build within kernel).
```
curl -LSs "https://raw.githubusercontent.com/aiichi/MemKernel/main/kernel/setup.sh" | bash -s Y
```
* __M__ : To build lkm (loadable kernel module). after adding this driver and building the kernel again, the lkm might be shipped within kernel (remember it).
```
curl -LSs "https://raw.githubusercontent.com/aiichi/MemKernel/main/kernel/setup.sh" | bash -s M
```
* __M-OUT__ : People who don't want to integrate this driver to their kernel source can use this option. this tells the setup script that the driver will be build out-of-tree as module. (Note: upstream linux discourages support for building out-of-tree modules: [Read-Article](https://source.android.com/docs/core/architecture/kernel/kernel-code#out-of-tree-modules))
```
curl -LSs "https://raw.githubusercontent.com/aiichi/MemKernel/main/kernel/setup.sh" | bash -s M-OUT
```

**TIP** : By default the setup script generates random name for the driver (/dev/*randomname*), this is to bypass existency check done via [*access(2)*](https://man7.org/linux/man-pages/man2/access.2.html) syscall. but you can override this behaviour by providing 2nd argument to the setup script like this:

```curl -LSs "https://raw.githubusercontent.com/aiichi/MemKernel/main/kernel/setup.sh" | bash -s M myname```

## Compilation
Totally depends on the kernel source you're building (gki & non-gki). I leave this part upto you.

## How It Works
On a higher level:

This driver code (be it lkm or inbuilt within kernel) creates a [character](https://linux-kernel-labs.github.io/refs/heads/master/labs/device_drivers.html) device driver in dev folder (/dev/drivername). A userspace app with root permission can talk to this driver (file) via [*ioctl(2)*](https://man7.org/linux/man-pages/man2/ioctl.2.html) syscall. the kernel part (driver) reads or writes the target memory behalf on userspace app and forward read data to userspace app to use.

## Problems
* This driver currently don't have synchronisation mechanism to handle multiple users or multiple threads of single user.
* No validation layer exists, so any root users can use this driver (if they know the name and purpose of the driver). it's a critical security risk, **You have been warned: use it at your own risk**.
