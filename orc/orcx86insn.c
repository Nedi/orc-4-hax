
#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <orc/orc.h>
#include <orc/orccpuinsn.h>
#include <stdlib.h>
#include <stdio.h>


static const OrcSysOpcode orc_x86_opcodes[] = {
  { "punpcklbw", ORC_X86_INSN_TYPE_MMXM_MMX, 0, 0x660f60 },
  { "punpcklwd", ORC_X86_INSN_TYPE_MMXM_MMX, 0, 0x660f61 },
  { "punpckldq", ORC_X86_INSN_TYPE_MMXM_MMX, 0, 0x660f62 },
  { "packsswb", ORC_X86_INSN_TYPE_MMXM_MMX, 0, 0x660f63 },
  { "pcmpgtb", ORC_X86_INSN_TYPE_MMXM_MMX, 0, 0x660f64 },
  { "pcmpgtw", ORC_X86_INSN_TYPE_MMXM_MMX, 0, 0x660f65 },
  { "pcmpgtd", ORC_X86_INSN_TYPE_MMXM_MMX, 0, 0x660f66 },
  { "packuswb", ORC_X86_INSN_TYPE_MMXM_MMX, 0, 0x660f67 },
  { "punpckhbw", ORC_X86_INSN_TYPE_MMXM_MMX, 0, 0x660f68 },
  { "punpckhwd", ORC_X86_INSN_TYPE_MMXM_MMX, 0, 0x660f69 },
  { "punpckhdq", ORC_X86_INSN_TYPE_MMXM_MMX, 0, 0x660f6a },
  { "packssdw", ORC_X86_INSN_TYPE_MMXM_MMX, 0, 0x660f6b },
  { "punpcklqdq", ORC_X86_INSN_TYPE_MMXM_MMX, 0, 0x660f6c },
  { "punpckhqdq", ORC_X86_INSN_TYPE_MMXM_MMX, 0, 0x660f6d },
  { "movdqa", ORC_X86_INSN_TYPE_MMXM_MMX, 0, 0x660f6f },
  { "psraw", ORC_X86_INSN_TYPE_MMXM_MMX, 0, 0x660fe1 },
  { "psrlw", ORC_X86_INSN_TYPE_MMXM_MMX, 0, 0x660fd1 },
  { "psllw", ORC_X86_INSN_TYPE_MMXM_MMX, 0, 0x660ff1 },
  { "psrad", ORC_X86_INSN_TYPE_MMXM_MMX, 0, 0x660fe2 },
  { "psrld", ORC_X86_INSN_TYPE_MMXM_MMX, 0, 0x660fd2 },
  { "pslld", ORC_X86_INSN_TYPE_MMXM_MMX, 0, 0x660ff2 },
  { "psrlq", ORC_X86_INSN_TYPE_MMXM_MMX, 0, 0x660fd3 },
  { "psllq", ORC_X86_INSN_TYPE_MMXM_MMX, 0, 0x660ff3 },
  { "psrldq", ORC_X86_INSN_TYPE_MMXM_MMX, 0, 0x660f73 },
  { "pslldq", ORC_X86_INSN_TYPE_MMXM_MMX, 0, 0x660f73 },
  { "psrlq", ORC_X86_INSN_TYPE_MMXM_MMX, 0, 0x660fd3 },
  { "pcmpeqb", ORC_X86_INSN_TYPE_MMXM_MMX, 0, 0x660f74 },
  { "pcmpeqw", ORC_X86_INSN_TYPE_MMXM_MMX, 0, 0x660f75 },
  { "pcmpeqd", ORC_X86_INSN_TYPE_MMXM_MMX, 0, 0x660f76 },
  { "paddq", ORC_X86_INSN_TYPE_MMXM_MMX, 0, 0x660fd4 },
  { "pmullw", ORC_X86_INSN_TYPE_MMXM_MMX, 0, 0x660fd5 },
  { "psubusb", ORC_X86_INSN_TYPE_MMXM_MMX, 0, 0x660fd8 },
  { "psubusw", ORC_X86_INSN_TYPE_MMXM_MMX, 0, 0x660fd9 },
  { "pminub", ORC_X86_INSN_TYPE_MMXM_MMX, 0, 0x660fda },
  { "pand", ORC_X86_INSN_TYPE_MMXM_MMX, 0, 0x660fdb },
  { "paddusb", ORC_X86_INSN_TYPE_MMXM_MMX, 0, 0x660fdc },
  { "paddusw", ORC_X86_INSN_TYPE_MMXM_MMX, 0, 0x660fdd },
  { "pmaxub", ORC_X86_INSN_TYPE_MMXM_MMX, 0, 0x660fde },
  { "pandn", ORC_X86_INSN_TYPE_MMXM_MMX, 0, 0x660fdf },
  { "pavgb", ORC_X86_INSN_TYPE_MMXM_MMX, 0, 0x660fe0 },
  { "pavgw", ORC_X86_INSN_TYPE_MMXM_MMX, 0, 0x660fe3 },
  { "pmulhuw", ORC_X86_INSN_TYPE_MMXM_MMX, 0, 0x660fe4 },
  { "pmulhw", ORC_X86_INSN_TYPE_MMXM_MMX, 0, 0x660fe5 },
  { "psubsb", ORC_X86_INSN_TYPE_MMXM_MMX, 0, 0x660fe8 },
  { "psubsw", ORC_X86_INSN_TYPE_MMXM_MMX, 0, 0x660fe9 },
  { "pminsw", ORC_X86_INSN_TYPE_MMXM_MMX, 0, 0x660fea },
  { "por", ORC_X86_INSN_TYPE_MMXM_MMX, 0, 0x660feb },
  { "paddsb", ORC_X86_INSN_TYPE_MMXM_MMX, 0, 0x660fec },
  { "paddsw", ORC_X86_INSN_TYPE_MMXM_MMX, 0, 0x660fed },
  { "pmaxsw", ORC_X86_INSN_TYPE_MMXM_MMX, 0, 0x660fee },
  { "pxor", ORC_X86_INSN_TYPE_MMXM_MMX, 0, 0x660fef },
  { "pmuludq", ORC_X86_INSN_TYPE_MMXM_MMX, 0, 0x660ff4 },
  { "pmaddwd", ORC_X86_INSN_TYPE_MMXM_MMX, 0, 0x660ff5 },
  { "psadbw", ORC_X86_INSN_TYPE_MMXM_MMX, 0, 0x660ff6 },
  { "psubb", ORC_X86_INSN_TYPE_MMXM_MMX, 0, 0x660ff8 },
  { "psubw", ORC_X86_INSN_TYPE_MMXM_MMX, 0, 0x660ff9 },
  { "psubd", ORC_X86_INSN_TYPE_MMXM_MMX, 0, 0x660ffa },
  { "psubq", ORC_X86_INSN_TYPE_MMXM_MMX, 0, 0x660ffb },
  { "paddb", ORC_X86_INSN_TYPE_MMXM_MMX, 0, 0x660ffc },
  { "paddw", ORC_X86_INSN_TYPE_MMXM_MMX, 0, 0x660ffd },
  { "paddd", ORC_X86_INSN_TYPE_MMXM_MMX, 0, 0x660ffe },
  { "pshufb", ORC_X86_INSN_TYPE_MMXM_MMX, 0, 0x660f3800 },
  { "phaddw", ORC_X86_INSN_TYPE_MMXM_MMX, 0, 0x660f3801 },
  { "phaddd", ORC_X86_INSN_TYPE_MMXM_MMX, 0, 0x660f3802 },
  { "phaddsw", ORC_X86_INSN_TYPE_MMXM_MMX, 0, 0x660f3803 },
  { "pmaddubsw", ORC_X86_INSN_TYPE_MMXM_MMX, 0, 0x660f3804 },
  { "phsubw", ORC_X86_INSN_TYPE_MMXM_MMX, 0, 0x660f3805 },
  { "phsubd", ORC_X86_INSN_TYPE_MMXM_MMX, 0, 0x660f3806 },
  { "phsubsw", ORC_X86_INSN_TYPE_MMXM_MMX, 0, 0x660f3807 },
  { "psignb", ORC_X86_INSN_TYPE_MMXM_MMX, 0, 0x660f3808 },
  { "psignw", ORC_X86_INSN_TYPE_MMXM_MMX, 0, 0x660f3809 },
  { "psignd", ORC_X86_INSN_TYPE_MMXM_MMX, 0, 0x660f380a },
  { "pmulhrsw", ORC_X86_INSN_TYPE_MMXM_MMX, 0, 0x660f380b },
  { "pabsb", ORC_X86_INSN_TYPE_MMXM_MMX, 0, 0x660f381c },
  { "pabsw", ORC_X86_INSN_TYPE_MMXM_MMX, 0, 0x660f381d },
  { "pabsd", ORC_X86_INSN_TYPE_MMXM_MMX, 0, 0x660f381e },
  { "pmovsxbw", ORC_X86_INSN_TYPE_MMXM_MMX, 0, 0x660f3820 },
  { "pmovsxbd", ORC_X86_INSN_TYPE_MMXM_MMX, 0, 0x660f3821 },
  { "pmovsxbq", ORC_X86_INSN_TYPE_MMXM_MMX, 0, 0x660f3822 },
  { "pmovsxwd", ORC_X86_INSN_TYPE_MMXM_MMX, 0, 0x660f3823 },
  { "pmovsxwq", ORC_X86_INSN_TYPE_MMXM_MMX, 0, 0x660f3824 },
  { "pmovsxdq", ORC_X86_INSN_TYPE_MMXM_MMX, 0, 0x660f3825 },
  { "pmuldq", ORC_X86_INSN_TYPE_MMXM_MMX, 0, 0x660f3828 },
  { "pcmpeqq", ORC_X86_INSN_TYPE_MMXM_MMX, 0, 0x660f3829 },
  { "packusdw", ORC_X86_INSN_TYPE_MMXM_MMX, 0, 0x660f382b },
  { "pmovzxbw", ORC_X86_INSN_TYPE_MMXM_MMX, 0, 0x660f3830 },
  { "pmovzxbd", ORC_X86_INSN_TYPE_MMXM_MMX, 0, 0x660f3831 },
  { "pmovzxbq", ORC_X86_INSN_TYPE_MMXM_MMX, 0, 0x660f3832 },
  { "pmovzxwd", ORC_X86_INSN_TYPE_MMXM_MMX, 0, 0x660f3833 },
  { "pmovzxwq", ORC_X86_INSN_TYPE_MMXM_MMX, 0, 0x660f3834 },
  { "pmovzxdq", ORC_X86_INSN_TYPE_MMXM_MMX, 0, 0x660f3835 },
  { "pmulld", ORC_X86_INSN_TYPE_MMXM_MMX, 0, 0x660f3840 },
  { "phminposuw", ORC_X86_INSN_TYPE_MMXM_MMX, 0, 0x660f3841 },
  { "pminsb", ORC_X86_INSN_TYPE_MMXM_MMX, 0, 0x660f3838 },
  { "pminsd", ORC_X86_INSN_TYPE_MMXM_MMX, 0, 0x660f3839 },
  { "pminuw", ORC_X86_INSN_TYPE_MMXM_MMX, 0, 0x660f383a },
  { "pminud", ORC_X86_INSN_TYPE_MMXM_MMX, 0, 0x660f383b },
  { "pmaxsb", ORC_X86_INSN_TYPE_MMXM_MMX, 0, 0x660f383c },
  { "pmaxsd", ORC_X86_INSN_TYPE_MMXM_MMX, 0, 0x660f383d },
  { "pmaxuw", ORC_X86_INSN_TYPE_MMXM_MMX, 0, 0x660f383e },
  { "pmaxud", ORC_X86_INSN_TYPE_MMXM_MMX, 0, 0x660f383f },
  { "pcmpgtq", ORC_X86_INSN_TYPE_MMXM_MMX, 0, 0x660f3837 },
  { "addps", ORC_X86_INSN_TYPE_MMXM_MMX, 0, 0x0f58 },
  { "subps", ORC_X86_INSN_TYPE_MMXM_MMX, 0, 0x0f5c },
  { "mulps", ORC_X86_INSN_TYPE_MMXM_MMX, 0, 0x0f59 },
  { "divps", ORC_X86_INSN_TYPE_MMXM_MMX, 0, 0x0f5e },
  { "sqrtps", ORC_X86_INSN_TYPE_MMXM_MMX, 0, 0x0f51 },
  { "addpd", ORC_X86_INSN_TYPE_MMXM_MMX, 0, 0x660f58 },
  { "subpd", ORC_X86_INSN_TYPE_MMXM_MMX, 0, 0x660f5c },
  { "mulpd", ORC_X86_INSN_TYPE_MMXM_MMX, 0, 0x660f59 },
  { "divpd", ORC_X86_INSN_TYPE_MMXM_MMX, 0, 0x660f5e },
  { "sqrtpd", ORC_X86_INSN_TYPE_MMXM_MMX, 0, 0x660f51 },
  { "cmpeqps", ORC_X86_INSN_TYPE_SSEM_SSE, 0, 0x0fc2, 0 },
  { "cmpeqpd", ORC_X86_INSN_TYPE_SSEM_SSE, 0, 0x660fc2, 0 },
  { "cmpltps", ORC_X86_INSN_TYPE_SSEM_SSE, 0, 0x0fc2, 1 },
  { "cmpltpd", ORC_X86_INSN_TYPE_SSEM_SSE, 0, 0x660fc2, 1 },
  { "cmpleps", ORC_X86_INSN_TYPE_SSEM_SSE, 0, 0x0fc2, 2 },
  { "cmplepd", ORC_X86_INSN_TYPE_SSEM_SSE, 0, 0x660fc2, 2 },
  { "cvttps2dq", ORC_X86_INSN_TYPE_MMXM_MMX, 0, 0xf30f5b },
  { "cvttpd2dq", ORC_X86_INSN_TYPE_MMXM_MMX, 0, 0x660fe6 },
  { "cvtdq2ps", ORC_X86_INSN_TYPE_MMXM_MMX, 0, 0x0f5b },
  { "cvtdq2pd", ORC_X86_INSN_TYPE_MMXM_MMX, 0, 0xf30fe6 },
  { "cvtps2pd", ORC_X86_INSN_TYPE_MMXM_MMX, 0, 0x0f5a },
  { "cvtpd2ps", ORC_X86_INSN_TYPE_MMXM_MMX, 0, 0x660f5a },
  { "minps", ORC_X86_INSN_TYPE_MMXM_MMX, 0, 0x0f5d },
  { "minpd", ORC_X86_INSN_TYPE_MMXM_MMX, 0, 0x660f5d },
  { "maxps", ORC_X86_INSN_TYPE_MMXM_MMX, 0, 0x0f5f },
  { "maxpd", ORC_X86_INSN_TYPE_MMXM_MMX, 0, 0x660f5f },
  { "psraw", ORC_X86_INSN_TYPE_IMM8_MMX_SHIFT, 0, 0x660f71, 4 },
  { "psrlw", ORC_X86_INSN_TYPE_IMM8_MMX_SHIFT, 0, 0x660f71, 2 },
  { "psllw", ORC_X86_INSN_TYPE_IMM8_MMX_SHIFT, 0, 0x660f71, 6 },
  { "psrad", ORC_X86_INSN_TYPE_IMM8_MMX_SHIFT, 0, 0x660f72, 4 },
  { "psrld", ORC_X86_INSN_TYPE_IMM8_MMX_SHIFT, 0, 0x660f72, 2 },
  { "pslld", ORC_X86_INSN_TYPE_IMM8_MMX_SHIFT, 0, 0x660f72, 6 },
  { "psrlq", ORC_X86_INSN_TYPE_IMM8_MMX_SHIFT, 0, 0x660f73, 2 },
  { "psllq", ORC_X86_INSN_TYPE_IMM8_MMX_SHIFT, 0, 0x660f73, 6 },
  { "psrldq", ORC_X86_INSN_TYPE_IMM8_MMX_SHIFT, 0, 0x660f73, 3 },
  { "pslldq", ORC_X86_INSN_TYPE_IMM8_MMX_SHIFT, 0, 0x660f73, 7 },
  { "pshufd", ORC_X86_INSN_TYPE_IMM8_MMXM_MMX, 0, 0x660f70 },
  { "pshuflw", ORC_X86_INSN_TYPE_IMM8_MMXM_MMX, 0, 0xf20f70 },
  { "pshufhw", ORC_X86_INSN_TYPE_IMM8_MMXM_MMX, 0, 0xf30f70 },
  { "palignr", ORC_X86_INSN_TYPE_IMM8_MMXM_MMX, 0, 0x660f3a0f },
  { "pinsrw", ORC_X86_INSN_TYPE_IMM8_REGM_MMX, 0, 0x660fc4 },
  { "movd", ORC_X86_INSN_TYPE_REGM_MMX, 0, 0x660f6e },
  { "movq", ORC_X86_INSN_TYPE_MMXM_MMX, 0, 0xf30f7e },
  { "movdqa", ORC_X86_INSN_TYPE_MMXM_MMX, 0, 0x660f6f },
  { "movdqu", ORC_X86_INSN_TYPE_MMXM_MMX, 0, 0xf30f6f },
  { "movhps", ORC_X86_INSN_TYPE_MMXM_MMX, 0, 0x0f16 },
  { "pextrw", ORC_X86_INSN_TYPE_IMM8_MMX_REG_REV, 0, 0x660f3a15 },
  { "movd", ORC_X86_INSN_TYPE_MMX_REGM_REV, 0, 0x660f7e },
  { "movq", ORC_X86_INSN_TYPE_MMXM_MMX_REV, 0, 0x660fd6 },
  { "movdqa", ORC_X86_INSN_TYPE_MMXM_MMX_REV, 0, 0x660f7f },
  { "movdqu", ORC_X86_INSN_TYPE_MMXM_MMX_REV, 0, 0xf30f7f },
  { "movntdq", ORC_X86_INSN_TYPE_MMXM_MMX_REV, 0, 0x660fe7 },
  { "ldmxcsr", ORC_X86_INSN_TYPE_MEM, 0, 0x0fae, 2 },
  { "stmxcsr", ORC_X86_INSN_TYPE_MEM, 0, 0x0fae, 3 },
  { "add", ORC_X86_INSN_TYPE_IMM8_REGM, 0, 0x83, 0 },
  { "add", ORC_X86_INSN_TYPE_IMM32_REGM, 0, 0x81, 0 },
  { "add", ORC_X86_INSN_TYPE_REGM_REG, 0, 0x03 },
  { "add", ORC_X86_INSN_TYPE_REG_REGM, 0, 0x01 },
  { "or", ORC_X86_INSN_TYPE_IMM8_REGM, 0, 0x83, 1 },
  { "or", ORC_X86_INSN_TYPE_IMM32_REGM, 0, 0x81, 1 },
  { "or", ORC_X86_INSN_TYPE_REGM_REG, 0, 0x0b },
  { "or", ORC_X86_INSN_TYPE_REG_REGM, 0, 0x09 },
  { "adc", ORC_X86_INSN_TYPE_IMM8_REGM, 0, 0x83, 2 },
  { "adc", ORC_X86_INSN_TYPE_IMM32_REGM, 0, 0x81, 2 },
  { "adc", ORC_X86_INSN_TYPE_REGM_REG, 0, 0x13 },
  { "adc", ORC_X86_INSN_TYPE_REG_REGM, 0, 0x11 },
  { "sbb", ORC_X86_INSN_TYPE_IMM8_REGM, 0, 0x83, 3 },
  { "sbb", ORC_X86_INSN_TYPE_IMM32_REGM, 0, 0x81, 3 },
  { "sbb", ORC_X86_INSN_TYPE_REGM_REG, 0, 0x1b },
  { "sbb", ORC_X86_INSN_TYPE_REG_REGM, 0, 0x19 },
  { "and", ORC_X86_INSN_TYPE_IMM8_REGM, 0, 0x83, 4 },
  { "and", ORC_X86_INSN_TYPE_IMM32_REGM, 0, 0x81, 4 },
  { "and", ORC_X86_INSN_TYPE_REGM_REG, 0, 0x23 },
  { "and", ORC_X86_INSN_TYPE_REG_REGM, 0, 0x21 },
  { "sub", ORC_X86_INSN_TYPE_IMM8_REGM, 0, 0x83, 5 },
  { "sub", ORC_X86_INSN_TYPE_IMM32_REGM, 0, 0x81, 5 },
  { "sub", ORC_X86_INSN_TYPE_REGM_REG, 0, 0x2b },
  { "sub", ORC_X86_INSN_TYPE_REG_REGM, 0, 0x29 },
  { "xor", ORC_X86_INSN_TYPE_IMM8_REGM, 0, 0x83, 6 },
  { "xor", ORC_X86_INSN_TYPE_IMM32_REGM, 0, 0x81, 6 },
  { "xor", ORC_X86_INSN_TYPE_REGM_REG, 0, 0x33 },
  { "xor", ORC_X86_INSN_TYPE_REG_REGM, 0, 0x31 },
  { "cmp", ORC_X86_INSN_TYPE_IMM8_REGM, 0, 0x83, 7 },
  { "cmp", ORC_X86_INSN_TYPE_IMM32_REGM, 0, 0x81, 7 },
  { "cmp", ORC_X86_INSN_TYPE_REGM_REG, 0, 0x3b },
  { "cmp", ORC_X86_INSN_TYPE_REG_REGM, 0, 0x39 },
  { "jo", ORC_X86_INSN_TYPE_BRANCH, 0, 0x70 },
  { "jno", ORC_X86_INSN_TYPE_BRANCH, 0, 0x71 },
  { "jc", ORC_X86_INSN_TYPE_BRANCH, 0, 0x72 },
  { "jnc", ORC_X86_INSN_TYPE_BRANCH, 0, 0x73 },
  { "jz", ORC_X86_INSN_TYPE_BRANCH, 0, 0x74 },
  { "jnz", ORC_X86_INSN_TYPE_BRANCH, 0, 0x75 },
  { "jbe", ORC_X86_INSN_TYPE_BRANCH, 0, 0x76 },
  { "ja", ORC_X86_INSN_TYPE_BRANCH, 0, 0x77 },
  { "js", ORC_X86_INSN_TYPE_BRANCH, 0, 0x78 },
  { "jns", ORC_X86_INSN_TYPE_BRANCH, 0, 0x79 },
  { "jp", ORC_X86_INSN_TYPE_BRANCH, 0, 0x7a },
  { "jnp", ORC_X86_INSN_TYPE_BRANCH, 0, 0x7b },
  { "jl", ORC_X86_INSN_TYPE_BRANCH, 0, 0x7c },
  { "jge", ORC_X86_INSN_TYPE_BRANCH, 0, 0x7d },
  { "jle", ORC_X86_INSN_TYPE_BRANCH, 0, 0x7e },
  { "jg", ORC_X86_INSN_TYPE_BRANCH, 0, 0x7f },
  { "jmp", ORC_X86_INSN_TYPE_BRANCH, 0, 0xeb },
  { "", ORC_X86_INSN_TYPE_LABEL, 0, 0x00 },
  { "ret", ORC_X86_INSN_TYPE_NONE, 0, 0xc3 },
  { "retq", ORC_X86_INSN_TYPE_NONE, 0, 0xc3 },
  { "emms", ORC_X86_INSN_TYPE_NONE, 0, 0x0f77 },
  { "rdtsc", ORC_X86_INSN_TYPE_NONE, 0, 0x0f31 },
  { "nop", ORC_X86_INSN_TYPE_NONE, 0, 0x90 },
  { "rep movsb", ORC_X86_INSN_TYPE_NONE, 0, 0xf3a4 },
  { "rep movsw", ORC_X86_INSN_TYPE_NONE, 0, 0x66f3a5 },
  { "rep movsl", ORC_X86_INSN_TYPE_NONE, 0, 0xf3a5 },
  { "push", ORC_X86_INSN_TYPE_STACK, 0, 0x50 },
  { "pop", ORC_X86_INSN_TYPE_STACK, 0, 0x58 },
  { "movzx", ORC_X86_INSN_TYPE_REGM_REG, 0, 0x0fb6 },
  { "movw", ORC_X86_INSN_TYPE_REGM_REG, 0, 0x668b },
  { "movl", ORC_X86_INSN_TYPE_REGM_REG, 0, 0x8b },
  { "mov", ORC_X86_INSN_TYPE_REGM_REG, 0, 0x8b },
  { "mov", ORC_X86_INSN_TYPE_IMM32_REGM_MOV, 0, 0xb8 },
  { "movb", ORC_X86_INSN_TYPE_REG8_REGM, 0, 0x88 },
  { "movw", ORC_X86_INSN_TYPE_REG16_REGM, 0, 0x6689 },
  { "movl", ORC_X86_INSN_TYPE_REG_REGM, 0, 0x89 },
  { "mov", ORC_X86_INSN_TYPE_REG_REGM, 0, 0x89 },
  { "test", ORC_X86_INSN_TYPE_REGM_REG, 0, 0x85 },
  { "testl", ORC_X86_INSN_TYPE_IMM32_REGM, 0, 0xf7, 0 },
  { "leal", ORC_X86_INSN_TYPE_REGM_REG, 0, 0x8d },
  { "leaq", ORC_X86_INSN_TYPE_REGM_REG, 0, 0x8d },
  { "imul", ORC_X86_INSN_TYPE_REGM_REG, 0, 0x0faf },
  { "imul", ORC_X86_INSN_TYPE_REGM, 0, 0xf7, 5 },
  { "incl", ORC_X86_INSN_TYPE_REGM, 0, 0xff, 0 },
  { "decl", ORC_X86_INSN_TYPE_REGM, 0, 0xff, 1 },
  { "sar", ORC_X86_INSN_TYPE_IMM8_REGM, 0, 0xc1, 7 },
  { "sar", ORC_X86_INSN_TYPE_REGM, 0, 0xd1, 7 },
  { "and", ORC_X86_INSN_TYPE_IMM32_A, 0, 0x25, 4 },
};

static void
output_opcode (OrcCompiler *p, const OrcSysOpcode *opcode, int size,
    int src, int dest)
{
  ORC_ASSERT(opcode->code != 0);

  if (opcode->code & 0xff000000) {
    if ((opcode->code & 0xff000000) == 0x66000000 ||
        (opcode->code & 0xff000000) == 0xf3000000 ||
        (opcode->code & 0xff000000) == 0xf2000000) {
      *p->codeptr++ = (opcode->code >> 24) & 0xff;
      orc_x86_emit_rex (p, size, dest, 0, src);
    } else {
      *p->codeptr++ = (opcode->code >> 24) & 0xff;
      orc_x86_emit_rex (p, size, dest, 0, src);
    }
    *p->codeptr++ = (opcode->code >> 16) & 0xff;
    *p->codeptr++ = (opcode->code >> 8) & 0xff;
    *p->codeptr++ = (opcode->code >> 0) & 0xff;
  } else if (opcode->code & 0xff0000) {
    if ((opcode->code & 0xff0000) == 0x660000 ||
        (opcode->code & 0xff0000) == 0xf30000 ||
        (opcode->code & 0xff0000) == 0xf20000) {
      *p->codeptr++ = (opcode->code >> 16) & 0xff;
      orc_x86_emit_rex (p, size, dest, 0, src);
    } else {
      orc_x86_emit_rex (p, size, dest, 0, src);
      *p->codeptr++ = (opcode->code >> 16) & 0xff;
    }
    *p->codeptr++ = (opcode->code >> 8) & 0xff;
    *p->codeptr++ = (opcode->code >> 0) & 0xff;
  } else if (opcode->code & 0xff00) {
    if ((opcode->code & 0xff00) == 0x6600 ||
        (opcode->code & 0xff00) == 0xf300 ||
        (opcode->code & 0xff00) == 0xf200) {
      *p->codeptr++ = (opcode->code >> 8) & 0xff;
      orc_x86_emit_rex (p, size, dest, 0, src);
    } else {
      orc_x86_emit_rex (p, size, dest, 0, src);
      *p->codeptr++ = (opcode->code >> 8) & 0xff;
    }
    *p->codeptr++ = (opcode->code >> 0) & 0xff;
  } else {
    orc_x86_emit_rex (p, size, dest, 0, src);
    *p->codeptr++ = (opcode->code >> 0) & 0xff;
  }
}

void
orc_x86_insn_output_asm (OrcCompiler *p, OrcX86Insn *xinsn)
{
  char imm_str[40] = { 0 };
  char op1_str[40] = { 0 };
  char op2_str[40] = { 0 };

  if (xinsn->opcode->type == ORC_X86_INSN_TYPE_LABEL) {
    ORC_ASM_CODE(p,"%d:\n", xinsn->label);
    return;
  }

  switch (xinsn->opcode->type) {
    case ORC_X86_INSN_TYPE_MMXM_MMX:
    case ORC_X86_INSN_TYPE_SSEM_SSE:
    case ORC_X86_INSN_TYPE_MMXM_MMX_REV:
    case ORC_X86_INSN_TYPE_REGM_MMX:
    case ORC_X86_INSN_TYPE_MMX_REGM_REV:
    case ORC_X86_INSN_TYPE_REGM_REG:
    case ORC_X86_INSN_TYPE_REG_REGM:
    case ORC_X86_INSN_TYPE_STACK:
    case ORC_X86_INSN_TYPE_MEM:
    case ORC_X86_INSN_TYPE_REGM:
    case ORC_X86_INSN_TYPE_REG8_REGM:
    case ORC_X86_INSN_TYPE_REG16_REGM:
    case ORC_X86_INSN_TYPE_BRANCH:
    case ORC_X86_INSN_TYPE_NONE:
      imm_str[0] = 0;
      break;
    case ORC_X86_INSN_TYPE_IMM8_MMX_SHIFT:
    case ORC_X86_INSN_TYPE_IMM8_MMXM_MMX:
    case ORC_X86_INSN_TYPE_IMM8_REGM_MMX:
    case ORC_X86_INSN_TYPE_IMM8_REGM:
    case ORC_X86_INSN_TYPE_IMM32_REGM:
    case ORC_X86_INSN_TYPE_IMM32_REGM_MOV:
    case ORC_X86_INSN_TYPE_IMM32_A:
      sprintf(imm_str, "$%d, ", xinsn->imm);
      break;
    default:
      ORC_ERROR("%d", xinsn->opcode->type);
      ORC_ASSERT(0);
      break;
  }

  switch (xinsn->opcode->type) {
    case ORC_X86_INSN_TYPE_MMXM_MMX:
    case ORC_X86_INSN_TYPE_SSEM_SSE:
    case ORC_X86_INSN_TYPE_IMM8_MMXM_MMX:
      if (xinsn->type == ORC_X86_RM_REG) {
        sprintf(op1_str, "%%%s, ", orc_x86_get_regname_sse (xinsn->src));
      } else if (xinsn->type == ORC_X86_RM_MEMOFFSET) {
        sprintf(op1_str, "%d(%%%s), ", xinsn->offset,
            orc_x86_get_regname_ptr (p, xinsn->src));
      } else if (xinsn->type == ORC_X86_RM_MEMINDEX) {
        sprintf(op1_str, "%d(%%%s,%%%s,%d), ", xinsn->offset,
            orc_x86_get_regname_ptr (p, xinsn->src),
            orc_x86_get_regname_ptr (p, xinsn->index_reg),
	    1<<xinsn->shift);
      } else {
	ORC_ASSERT(0);
      }
      break;
    case ORC_X86_INSN_TYPE_MMXM_MMX_REV: /* FIXME misnamed */
    case ORC_X86_INSN_TYPE_MMX_REGM_REV:
      sprintf(op1_str, "%%%s, ", orc_x86_get_regname_sse (xinsn->src));
      break;
    case ORC_X86_INSN_TYPE_REGM_MMX:
    case ORC_X86_INSN_TYPE_REGM_REG:
    case ORC_X86_INSN_TYPE_IMM8_REGM_MMX:
      if (xinsn->type == ORC_X86_RM_REG) {
        sprintf(op1_str, "%%%s, ", orc_x86_get_regname_size (xinsn->src,
            xinsn->size));
      } else if (xinsn->type == ORC_X86_RM_MEMOFFSET) {
        sprintf(op1_str, "%d(%%%s), ", xinsn->offset,
            orc_x86_get_regname_ptr (p, xinsn->src));
      } else if (xinsn->type == ORC_X86_RM_MEMINDEX) {
        sprintf(op1_str, "%d(%%%s,%%%s,%d), ", xinsn->offset,
            orc_x86_get_regname_ptr (p, xinsn->src),
            orc_x86_get_regname_ptr (p, xinsn->index_reg),
	    1<<xinsn->shift);
      } else {
	ORC_ASSERT(0);
      }
      break;
    case ORC_X86_INSN_TYPE_MEM:
    case ORC_X86_INSN_TYPE_REGM:
    case ORC_X86_INSN_TYPE_IMM8_MMX_SHIFT:
    case ORC_X86_INSN_TYPE_STACK:
    case ORC_X86_INSN_TYPE_IMM32_REGM_MOV:
    case ORC_X86_INSN_TYPE_IMM8_REGM:
    case ORC_X86_INSN_TYPE_IMM32_REGM:
    case ORC_X86_INSN_TYPE_BRANCH:
    case ORC_X86_INSN_TYPE_NONE:
      op1_str[0] = 0;
      break;
    case ORC_X86_INSN_TYPE_REG_REGM:
      sprintf(op1_str, "%%%s, ", orc_x86_get_regname (xinsn->src));
      break;
    case ORC_X86_INSN_TYPE_REG8_REGM:
      sprintf(op1_str, "%%%s, ", orc_x86_get_regname_8 (xinsn->src));
      break;
    case ORC_X86_INSN_TYPE_REG16_REGM:
      sprintf(op1_str, "%%%s, ", orc_x86_get_regname_16 (xinsn->src));
      break;
    case ORC_X86_INSN_TYPE_IMM32_A:
    default:
      ORC_ERROR("%d", xinsn->opcode->type);
      ORC_ASSERT(0);
      break;
  }

  switch (xinsn->opcode->type) {
    case ORC_X86_INSN_TYPE_MMXM_MMX:
    case ORC_X86_INSN_TYPE_SSEM_SSE:
    case ORC_X86_INSN_TYPE_IMM8_MMXM_MMX:
    case ORC_X86_INSN_TYPE_IMM8_REGM_MMX:
    case ORC_X86_INSN_TYPE_REGM_MMX:
    case ORC_X86_INSN_TYPE_IMM8_MMX_SHIFT:
      sprintf(op2_str, "%%%s", orc_x86_get_regname_sse (xinsn->dest));
      break;
    case ORC_X86_INSN_TYPE_MMXM_MMX_REV:
      if (xinsn->type == ORC_X86_RM_REG) {
        sprintf(op2_str, "%%%s", orc_x86_get_regname_sse (xinsn->dest));
      } else if (xinsn->type == ORC_X86_RM_MEMOFFSET) {
        sprintf(op2_str, "%d(%%%s)", xinsn->offset,
            orc_x86_get_regname_ptr (p, xinsn->dest));
      } else if (xinsn->type == ORC_X86_RM_MEMINDEX) {
        sprintf(op1_str, "%d(%%%s,%%%s,%d), ", xinsn->offset,
            orc_x86_get_regname_ptr (p, xinsn->dest),
            orc_x86_get_regname_ptr (p, xinsn->index_reg),
	    1<<xinsn->shift);
      } else {
	ORC_ASSERT(0);
      }
      break;
    case ORC_X86_INSN_TYPE_MMX_REGM_REV:
    case ORC_X86_INSN_TYPE_IMM32_REGM_MOV:
    case ORC_X86_INSN_TYPE_IMM8_REGM:
    case ORC_X86_INSN_TYPE_IMM32_REGM:
    case ORC_X86_INSN_TYPE_REGM:
    case ORC_X86_INSN_TYPE_REG8_REGM:
    case ORC_X86_INSN_TYPE_REG16_REGM:
    case ORC_X86_INSN_TYPE_REG_REGM:
      if (xinsn->type == ORC_X86_RM_REG) {
        sprintf(op2_str, "%%%s", orc_x86_get_regname (xinsn->dest));
      } else if (xinsn->type == ORC_X86_RM_MEMOFFSET) {
        sprintf(op2_str, "%d(%%%s)", xinsn->offset,
            orc_x86_get_regname_ptr (p, xinsn->dest));
      } else if (xinsn->type == ORC_X86_RM_MEMINDEX) {
        sprintf(op1_str, "%d(%%%s,%%%s,%d), ", xinsn->offset,
            orc_x86_get_regname_ptr (p, xinsn->dest),
            orc_x86_get_regname_ptr (p, xinsn->index_reg),
	    1<<xinsn->shift);
      } else {
	ORC_ASSERT(0);
      }
      break;
    case ORC_X86_INSN_TYPE_REGM_REG:
    case ORC_X86_INSN_TYPE_STACK:
      sprintf(op2_str, "%%%s", orc_x86_get_regname_size (xinsn->dest,
	  xinsn->size));
      break;
    case ORC_X86_INSN_TYPE_MEM:
      if (xinsn->type == ORC_X86_RM_REG) {
        ORC_ERROR("register operand on memory instruction");
        sprintf(op2_str, "ERROR");
      } else if (xinsn->type == ORC_X86_RM_MEMOFFSET) {
	/* FIXME: this uses xinsn->src */
        sprintf(op2_str, "%d(%%%s)", xinsn->offset,
            orc_x86_get_regname_ptr (p, xinsn->src));
      } else {
	ORC_ASSERT(0);
      }
      break;
    case ORC_X86_INSN_TYPE_BRANCH:
      sprintf (op2_str, "%d%c", xinsn->label,
          (p->labels[xinsn->label]!=NULL) ? 'b' : 'f');
      break;
    case ORC_X86_INSN_TYPE_NONE:
      op2_str[0] = 0;
      break;
    case ORC_X86_INSN_TYPE_IMM32_A:
    default:
      ORC_ERROR("%d", xinsn->opcode->type);
      ORC_ASSERT(0);
      break;
  }

  ORC_ASM_CODE(p,"  %s %s%s%s\n", xinsn->opcode->name,
      imm_str, op1_str, op2_str);

}

void
orc_x86_insn_output_opcode (OrcCompiler *p, OrcX86Insn *xinsn)
{
  if (xinsn->opcode->type == ORC_X86_INSN_TYPE_IMM8_MMX_SHIFT) {
    output_opcode (p, xinsn->opcode, 4, xinsn->dest, 0);
  } else if (xinsn->opcode->type == ORC_X86_INSN_TYPE_MMX_REGM_REV ||
      xinsn->opcode->type == ORC_X86_INSN_TYPE_REG_REGM) {
    output_opcode (p, xinsn->opcode, 4, xinsn->dest, xinsn->src);
  } else if (xinsn->opcode->type != ORC_X86_INSN_TYPE_STACK) {
    output_opcode (p, xinsn->opcode, 4, xinsn->src, xinsn->dest);
  }
}

void
orc_x86_insn_output_modrm (OrcCompiler *p, OrcX86Insn *xinsn)
{
  switch (xinsn->opcode->type) {
    case ORC_X86_INSN_TYPE_REGM_REG:
    case ORC_X86_INSN_TYPE_REGM_MMX:
    case ORC_X86_INSN_TYPE_MMXM_MMX:
      orc_x86_emit_modrm_reg (p, xinsn->src, xinsn->dest);
      break;
    case ORC_X86_INSN_TYPE_REG_REGM:
    case ORC_X86_INSN_TYPE_MMXM_MMX_REV:
    case ORC_X86_INSN_TYPE_MMX_REGM_REV:
      orc_x86_emit_modrm_reg (p, xinsn->dest, xinsn->src);
      break;
    case ORC_X86_INSN_TYPE_IMM8_MMX_SHIFT:
      orc_x86_emit_modrm_reg (p, xinsn->dest, xinsn->opcode->code2);
      break;
    case ORC_X86_INSN_TYPE_IMM8_REGM_MMX:
    case ORC_X86_INSN_TYPE_IMM8_MMXM_MMX:
      orc_x86_emit_modrm_reg (p, xinsn->src, xinsn->dest);
      break;
    case ORC_X86_INSN_TYPE_SSEM_SSE:
      orc_x86_emit_modrm_reg (p, xinsn->src, xinsn->dest);
      *p->codeptr++ = xinsn->opcode->code2;
      break;
    case ORC_X86_INSN_TYPE_STACK:
      *p->codeptr++ = xinsn->opcode->code + (xinsn->dest&0x7);
      break;
    case ORC_X86_INSN_TYPE_MEM:
    case ORC_X86_INSN_TYPE_REGM:
    default:
      ORC_ASSERT(0);
      break;
  }
}

void
orc_x86_insn_output_immediate (OrcCompiler *p, OrcX86Insn *xinsn)
{
  switch (xinsn->opcode->type) {
    case ORC_X86_INSN_TYPE_REGM_REG:
    case ORC_X86_INSN_TYPE_REGM_MMX:
    case ORC_X86_INSN_TYPE_MMXM_MMX:
    case ORC_X86_INSN_TYPE_REG_REGM:
    case ORC_X86_INSN_TYPE_MMXM_MMX_REV:
    case ORC_X86_INSN_TYPE_MMX_REGM_REV:
      break;
    case ORC_X86_INSN_TYPE_IMM8_MMX_SHIFT:
    case ORC_X86_INSN_TYPE_IMM8_REGM_MMX:
    case ORC_X86_INSN_TYPE_IMM8_MMXM_MMX:
      *p->codeptr++ = xinsn->imm;
      break;
    case ORC_X86_INSN_TYPE_SSEM_SSE:
    case ORC_X86_INSN_TYPE_STACK:
    case ORC_X86_INSN_TYPE_REGM:
    case ORC_X86_INSN_TYPE_MEM:
      break;
    default:
      ORC_ASSERT(0);
      break;
  }
}

void
orc_x86_emit_cpuinsn (OrcCompiler *p, int index, int imm, int src, int dest)
{
  OrcX86Insn xinsn = { 0 };
  const OrcSysOpcode *opcode = orc_x86_opcodes + index;

  xinsn.opcode = opcode;
  xinsn.imm = imm;
  xinsn.src = src;
  xinsn.dest = dest;
  xinsn.type = ORC_X86_RM_REG;
  xinsn.size = 4;

  orc_x86_insn_output_asm (p, &xinsn);

  orc_x86_insn_output_opcode (p, &xinsn);
  orc_x86_insn_output_modrm (p, &xinsn);
  orc_x86_insn_output_immediate (p, &xinsn);

}

void
orc_x86_emit_cpuinsn_load_memoffset (OrcCompiler *p, int index, int size,
    int imm, int offset, int src, int dest)
{
  OrcX86Insn xinsn = { 0 };
  const OrcSysOpcode *opcode = orc_x86_opcodes + index;

  xinsn.opcode = opcode;
  xinsn.imm = imm;
  xinsn.src = src;
  xinsn.dest = dest;
  xinsn.type = ORC_X86_RM_MEMOFFSET;
  xinsn.offset = offset;
  xinsn.size = size;

  orc_x86_insn_output_asm (p, &xinsn);

#if 0
  orc_x86_insn_output_opcode (p, &xinsn);
  orc_x86_insn_output_modrm (p, &xinsn);
  orc_x86_insn_output_immediate (p, &xinsn);
#endif

  output_opcode (p, opcode, size, src, dest);

  switch (opcode->type) {
    case ORC_X86_INSN_TYPE_MMXM_MMX:
    case ORC_X86_INSN_TYPE_REGM_MMX:
    case ORC_X86_INSN_TYPE_REGM_REG:
      orc_x86_emit_modrm_memoffset (p, offset, src, dest);
      break;
    case ORC_X86_INSN_TYPE_IMM8_REGM_MMX:
    case ORC_X86_INSN_TYPE_IMM8_MMXM_MMX:
      orc_x86_emit_modrm_memoffset (p, offset, src, dest);
      *p->codeptr++ = imm;
      break;
    case ORC_X86_INSN_TYPE_IMM8_MMX_REG_REV:
      orc_x86_emit_modrm_memoffset (p, offset, dest, src);
      *p->codeptr++ = imm;
      break;
    case ORC_X86_INSN_TYPE_MMXM_MMX_REV:
    case ORC_X86_INSN_TYPE_MMX_REGM_REV:
      orc_x86_emit_modrm_memoffset (p, offset, dest, src);
      break;
    case ORC_X86_INSN_TYPE_SSEM_SSE:
      orc_x86_emit_modrm_memoffset (p, offset, src, dest);
      *p->codeptr++ = opcode->code2;
      break;
    case ORC_X86_INSN_TYPE_MEM:
    case ORC_X86_INSN_TYPE_REGM:
      orc_x86_emit_modrm_memoffset (p, offset, src, opcode->code2);
      break;
    default:
      ORC_ASSERT(0);
      break;
  }
}

void
orc_x86_emit_cpuinsn_store_memoffset (OrcCompiler *p, int index, int size,
    int imm, int offset, int src, int dest)
{
  OrcX86Insn xinsn = { 0 };
  const OrcSysOpcode *opcode = orc_x86_opcodes + index;

  xinsn.opcode = opcode;
  xinsn.imm = imm;
  xinsn.src = src;
  xinsn.dest = dest;
  xinsn.type = ORC_X86_RM_MEMOFFSET;
  xinsn.offset = offset;
  xinsn.size = size;

  orc_x86_insn_output_asm (p, &xinsn);

  if (opcode->type == ORC_X86_INSN_TYPE_MMXM_MMX_REV ||
      opcode->type == ORC_X86_INSN_TYPE_IMM8_MMX_REG_REV ||
      opcode->type == ORC_X86_INSN_TYPE_MMX_REGM_REV) {
    output_opcode (p, opcode, 4, dest, src);
  } else {
    output_opcode (p, opcode, 4, src, dest);
  }

  switch (opcode->type) {
    case ORC_X86_INSN_TYPE_MMXM_MMX:
      orc_x86_emit_modrm_memoffset (p, offset, src, dest);
      break;
    case ORC_X86_INSN_TYPE_IMM8_REGM_MMX:
    case ORC_X86_INSN_TYPE_IMM8_MMXM_MMX:
      orc_x86_emit_modrm_memoffset (p, offset, src, dest);
      *p->codeptr++ = imm;
      break;
    case ORC_X86_INSN_TYPE_IMM8_MMX_REG_REV:
      orc_x86_emit_modrm_memoffset (p, offset, dest, src);
      *p->codeptr++ = imm;
      break;
    case ORC_X86_INSN_TYPE_MMXM_MMX_REV:
    case ORC_X86_INSN_TYPE_MMX_REGM_REV:
      orc_x86_emit_modrm_memoffset (p, offset, dest, src);
      break;
    case ORC_X86_INSN_TYPE_SSEM_SSE:
      orc_x86_emit_modrm_memoffset (p, offset, src, dest);
      *p->codeptr++ = opcode->code2;
      break;
    case ORC_X86_INSN_TYPE_REGM_MMX:
    default:
      ORC_ASSERT(0);
      break;
  }
}

void
orc_x86_emit_cpuinsn_load_memindex (OrcCompiler *p, int index, int size,
    int imm, int offset, int src, int src_index, int shift, int dest)
{
  OrcX86Insn xinsn = { 0 };
  const OrcSysOpcode *opcode = orc_x86_opcodes + index;

  xinsn.opcode = opcode;
  xinsn.imm = imm;
  xinsn.src = src;
  xinsn.dest = dest;
  xinsn.type = ORC_X86_RM_MEMINDEX;
  xinsn.offset = offset;
  xinsn.index_reg = src_index;
  xinsn.shift = shift;
  xinsn.size = size;

  orc_x86_insn_output_asm (p, &xinsn);

  output_opcode (p, opcode, size, src, dest);

  switch (opcode->type) {
    case ORC_X86_INSN_TYPE_MMXM_MMX:
    case ORC_X86_INSN_TYPE_REGM_MMX:
    case ORC_X86_INSN_TYPE_MMX_REGM_REV:
    case ORC_X86_INSN_TYPE_REGM_REG:
      orc_x86_emit_modrm_memindex2 (p, offset, src, src_index, shift, dest);
      break;
    case ORC_X86_INSN_TYPE_IMM8_REGM_MMX:
    case ORC_X86_INSN_TYPE_IMM8_MMXM_MMX:
      orc_x86_emit_modrm_memindex2 (p, offset, src, src_index, shift, dest);
      *p->codeptr++ = imm;
      break;
    case ORC_X86_INSN_TYPE_IMM8_MMX_REG_REV:
      orc_x86_emit_modrm_memindex2 (p, offset, dest, src_index, shift, src);
      *p->codeptr++ = imm;
      break;
    case ORC_X86_INSN_TYPE_MMXM_MMX_REV:
      orc_x86_emit_modrm_memindex2 (p, offset, dest, src_index, shift, src);
      break;
    case ORC_X86_INSN_TYPE_SSEM_SSE:
      orc_x86_emit_modrm_memindex2 (p, offset, src, src_index, shift, dest);
      *p->codeptr++ = opcode->code2;
      break;
    default:
      ORC_ASSERT(0);
      break;
  }
}

void
orc_x86_emit_cpuinsn_imm_reg (OrcCompiler *p, int index, int size, int imm,
    int dest)
{
  OrcX86Insn xinsn = { 0 };
  const OrcSysOpcode *opcode = orc_x86_opcodes + index;

  xinsn.opcode = opcode;
  xinsn.imm = imm;
  xinsn.src = 0;
  xinsn.dest = dest;
  xinsn.type = ORC_X86_RM_REG;
  xinsn.size = size;

  orc_x86_insn_output_asm (p, &xinsn);

  if (opcode->type != ORC_X86_INSN_TYPE_IMM32_REGM_MOV &&
      opcode->type != ORC_X86_INSN_TYPE_IMM32_A) {
    output_opcode (p, opcode, size, dest, 0);
  }

  switch (opcode->type) {
    case ORC_X86_INSN_TYPE_IMM8_REGM:
      orc_x86_emit_modrm_reg (p, dest, opcode->code2);
      *p->codeptr++ = imm;
      break;
    case ORC_X86_INSN_TYPE_IMM32_REGM:
      orc_x86_emit_modrm_reg (p, dest, opcode->code2);
      *p->codeptr++ = imm&0xff;
      *p->codeptr++ = (imm>>8)&0xff;
      *p->codeptr++ = (imm>>16)&0xff;
      *p->codeptr++ = (imm>>24)&0xff;
      break;
    case ORC_X86_INSN_TYPE_IMM32_A:
      *p->codeptr++ = imm&0xff;
      *p->codeptr++ = (imm>>8)&0xff;
      *p->codeptr++ = (imm>>16)&0xff;
      *p->codeptr++ = (imm>>24)&0xff;
      break;
    case ORC_X86_INSN_TYPE_IMM32_REGM_MOV:
      *p->codeptr++ = opcode->code + (dest&7);
      *p->codeptr++ = imm&0xff;
      *p->codeptr++ = (imm>>8)&0xff;
      *p->codeptr++ = (imm>>16)&0xff;
      *p->codeptr++ = (imm>>24)&0xff;
      break;
    case ORC_X86_INSN_TYPE_MEM:
    case ORC_X86_INSN_TYPE_REGM:
      orc_x86_emit_modrm_reg (p, dest, opcode->code2);
      break;
    default:
      ORC_ASSERT(0);
      break;
  }
}

void
orc_x86_emit_cpuinsn_imm_memoffset (OrcCompiler *p, int index, int size,
    int imm, int offset, int dest)
{
  OrcX86Insn xinsn = { 0 };
  const OrcSysOpcode *opcode = orc_x86_opcodes + index;

  xinsn.opcode = opcode;
  xinsn.imm = imm;
  xinsn.src = 0;
  xinsn.dest = dest;
  xinsn.type = ORC_X86_RM_MEMOFFSET;
  xinsn.offset = offset;
  xinsn.size = size;

  orc_x86_insn_output_asm (p, &xinsn);

  output_opcode (p, opcode, size, dest, 0);

  switch (opcode->type) {
    case ORC_X86_INSN_TYPE_IMM8_REGM:
      orc_x86_emit_modrm_memoffset (p, offset, dest, opcode->code2);
      *p->codeptr++ = imm;
      break;
    case ORC_X86_INSN_TYPE_IMM32_REGM:
      orc_x86_emit_modrm_memoffset (p, offset, dest, opcode->code2);
      *p->codeptr++ = imm&0xff;
      *p->codeptr++ = (imm>>8)&0xff;
      *p->codeptr++ = (imm>>16)&0xff;
      *p->codeptr++ = (imm>>24)&0xff;
      break;
    default:
      ORC_ASSERT(0);
      break;
  }
}

void
orc_x86_emit_cpuinsn_reg_memoffset (OrcCompiler *p, int index, int src,
    int offset, int dest)
{
  OrcX86Insn xinsn = { 0 };
  const OrcSysOpcode *opcode = orc_x86_opcodes + index;
  int size = 4;

  xinsn.opcode = opcode;
  xinsn.src = src;
  xinsn.dest = dest;
  xinsn.type = ORC_X86_RM_MEMOFFSET;
  xinsn.offset = offset;
  xinsn.size = size;

  orc_x86_insn_output_asm (p, &xinsn);

  if (opcode->type == ORC_X86_INSN_TYPE_REG8_REGM ||
      opcode->type == ORC_X86_INSN_TYPE_REG16_REGM) {
    output_opcode (p, opcode, size, dest, 0);
  } else {
    output_opcode (p, opcode, size, 0, dest);
  }

  switch (opcode->type) {
    case ORC_X86_INSN_TYPE_REG_REGM:
    case ORC_X86_INSN_TYPE_REG16_REGM:
    case ORC_X86_INSN_TYPE_REG8_REGM:
      orc_x86_emit_modrm_memoffset (p, offset, dest, src);
      break;
    default:
      ORC_ASSERT(0);
      break;
  }
}

void
orc_x86_emit_cpuinsn_memoffset_reg (OrcCompiler *p, int index, int size,
    int offset, int src, int dest)
{
  OrcX86Insn xinsn = { 0 };
  const OrcSysOpcode *opcode = orc_x86_opcodes + index;

  xinsn.opcode = opcode;
  xinsn.src = src;
  xinsn.dest = dest;
  xinsn.type = ORC_X86_RM_MEMOFFSET;
  xinsn.offset = offset;
  xinsn.size = size;

  orc_x86_insn_output_asm (p, &xinsn);

  output_opcode (p, opcode, size, src, dest);

  switch (opcode->type) {
    case ORC_X86_INSN_TYPE_REGM_REG:
      orc_x86_emit_modrm_memoffset (p, offset, src, dest);
      break;
    default:
      ORC_ASSERT(0);
      break;
  }
}

void
orc_x86_emit_cpuinsn_branch (OrcCompiler *p, int index, int label)
{
  OrcX86Insn xinsn = { 0 };
  const OrcSysOpcode *opcode = orc_x86_opcodes + index;

  xinsn.opcode = opcode;
  xinsn.label = label;

  orc_x86_insn_output_asm (p, &xinsn);

  if (p->long_jumps) {
    if (index == ORC_X86_jmp) {
      *p->codeptr++ = 0xe9;
    } else {
      *p->codeptr++ = 0x0f;
      *p->codeptr++ = opcode->code + 0x10;
    }
  } else {
    *p->codeptr++ = opcode->code;
  }

  switch (opcode->type) {
    case ORC_X86_INSN_TYPE_BRANCH:
      if (p->long_jumps) {
        x86_add_fixup (p, p->codeptr, label, 1);
        *p->codeptr++ = 0xfc;
        *p->codeptr++ = 0xff;
        *p->codeptr++ = 0xff;
        *p->codeptr++ = 0xff;
      } else {
        x86_add_fixup (p, p->codeptr, label, 0);
        *p->codeptr++ = 0xff;
      }
      break;
    default:
      ORC_ASSERT(0);
      break;
  }
}

void
orc_x86_emit_cpuinsn_label (OrcCompiler *p, int index, int label)
{
  OrcX86Insn xinsn = { 0 };
  const OrcSysOpcode *opcode = orc_x86_opcodes + index;

  xinsn.opcode = opcode;
  xinsn.label = label;

  orc_x86_insn_output_asm (p, &xinsn);

  switch (opcode->type) {
    case ORC_X86_INSN_TYPE_LABEL:
      x86_add_label (p, p->codeptr, label);
      break;
    default:
      ORC_ASSERT(0);
      break;
  }
}

void
orc_x86_emit_cpuinsn_none (OrcCompiler *p, int index)
{
  OrcX86Insn xinsn = { 0 };
  const OrcSysOpcode *opcode = orc_x86_opcodes + index;
  int size = 4;

  xinsn.opcode = opcode;
  xinsn.size = size;

  orc_x86_insn_output_asm (p, &xinsn);

  output_opcode (p, opcode, size, 0, 0);
}

