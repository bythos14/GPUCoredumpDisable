#include <stdint.h>
#include <taihen.h>

#include <psp2kern/kernel/modulemgr.h>

static SceUID inject_id[2];

void _start() __attribute__((weak, alias("module_start")));
int module_start(SceSize argc, const void *args)
{
  tai_module_info_t info;
  info.size = sizeof(tai_module_info_t);
  taiGetModuleInfoForKernel(KERNEL_PID, "SceGpuEs4", &info);

  uint16_t b_5 = 0xE003;
  uint16_t b_4 = 0xE004;

  inject_id[0] = taiInjectDataForKernel(KERNEL_PID,
                                        info.modid,
                                        0,
                                        0x97a6,
                                        &b_5,
                                        sizeof(b_5));
  inject_id[1] = taiInjectDataForKernel(KERNEL_PID,
                                        info.modid,
                                        0,
                                        0x9814,
                                        &b_4,
                                        sizeof(b_4));

  return SCE_KERNEL_START_SUCCESS;
}

int module_stop(SceSize argc, const void *args)
{
  taiInjectReleaseForKernel(inject_id[0]);
  taiInjectReleaseForKernel(inject_id[1]);

  return SCE_KERNEL_STOP_SUCCESS;
}
