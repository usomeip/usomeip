# uSOMEIP -- micro SOMEIP

Those codes is mirrored from https://github.com/autoas/ssas-public, and this library is source open for SOMEIP study&research, but not free for any other commercial usage.

This is a light weight SOMEIP/SD software stack implemented according to AUTOSAR 4.4 specification. And this can be deployed on either resource constrained MCU or on rich os such as windows/linux/android/QNX, etc.

## build
```bash
scons --app=NetApp
scons --app=NetAppT

# for windows, if want to use lwip, better to build with FreeRTOS
set USE_LWIP=YES 
scons --app=NetApp --os=FreeRTOS
scons --app=NetAppT --os=FreeRTOS
```
