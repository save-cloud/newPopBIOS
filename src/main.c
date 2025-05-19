#include <pspiofilemgr.h>
#include <pspkernel.h>
#include <pspsdk.h>

/* Used for the SceModule2 struct. */
#include <string.h>
#include <systemctrl.h>

#define ROM "ms0:/PSX-BIOS.ROM"

/* PopBIOS, Kernel(0x1000), ver.0.1 */
PSP_MODULE_INFO("NewPopBIOS", 0x1000, 0, 1);

u32 scex = 0x45454353;

u32 popKernelPatchSCEIString(void) {
  int t = 0;

  while (1) {
    /* SCEE trademark string to addr 0x0988AE44 */
    _sw(scex, 0x0988AE44);

    sceKernelDelayThread((1 * 1000 * 1000) / 2);
  }
  return 0;
}

/* like these function names ;) */
u32 popKernelFindBIOSInMemory(unsigned char *modname) {
  u32 ret = -1;

  /* here we find the pops module */
  SceModule *mod = sceKernelFindModuleByName(modname);

  if (mod == NULL)
    return ret;

  int i;

  for (i = 0; i < mod->text_size; i++) {
    /* the CEX- string only found in the psx bios */
    if (memcmp((void *)mod->text_addr + i, "CEX-", 4) == 0) {
      /* and the bios starts 300 bytes before the string */
      ret = (mod->text_addr + i) - 300;
      break;
    }
  }

  /* else return -1 */
  return ret;
}

int popThread(SceSize argc, void *argp) {
  /* without the psp would crash. */
  sceKernelDelayThread(4 * 1000 * 1000);

  SceIoStat stat;
  sceIoGetstat(ROM, &stat);

  if (stat.st_size > 0x80000)
    sceKernelExitDeleteThread(-1);

  /* opening the psx bios */
  SceUID fd = sceIoOpen(ROM, PSP_O_RDONLY, 0777);

  if (fd < 0)
    sceKernelExitDeleteThread(-1);

  /* here we find the addr of the bios from the ram */
  u32 bios_addr = popKernelFindBIOSInMemory("pops");

  if (bios_addr < 0)
    sceKernelExitDeleteThread(-1);

  /* finally, "patching" the bios */
  sceIoRead(fd, (void *)bios_addr, stat.st_size);
  sceIoClose(fd);

  /* patch SCEI trademark */
  popKernelPatchSCEIString();

  /* and killing the thread *never reached* */
  sceKernelExitDeleteThread(0);

  return 0;
}

int module_start(SceSize argc, void *argp) {
  /* creating a new thread */
  SceUID thid =
      sceKernelCreateThread("pop_thread", popThread, 0x18, 0x10000, 0, NULL);
  if (thid >= 0)
    sceKernelStartThread(thid, 0, 0);

  return 0;
}
