#include <stdio.h>
#include <stdint.h>

uint16_t tones[] = {
	0, 0x180, 0x197, 0x1AF, 0x1C9, 0x1E4, 0x201, 0x21F, 0x23F, 0x262, 0x286,
	0x2AC, 0x2D5, 0x300, 0x32E, 0x35E, 0x391, 0x3C8, 0x401, 0x43E, 0x47F, 0x4C3,
	0x50C, 0x558, 0x5AA, 0x600, 0x65B, 0x6BC, 0x723, 0x78F, 0x802, 0x87C, 0x8FD,
	0x986, 0x0A17, 0x0AB1, 0x0B54, 0x0C00, 0x0CB7, 0x0D79, 0x0E46, 0x0F1F, 0x1005,
	0x10F9, 0x11FB, 0x130D, 0x142F, 0x1562, 0x16A8, 0x1801, 0x196E, 0x1AF1
};

unsigned char intro_music[] = {
  0x58, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x58, 0x00, 0x00, 0x00, 0x00, 0x00, 0x5a, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x5a, 0x00, 0x00, 0x00, 0x00, 0x00, 0x5e, 0x00, 0x00, 0x00, 0x5a, 0x00,
  0x5e, 0x00, 0x00, 0x00, 0x62, 0x00, 0x00, 0x00, 0x00, 0x00, 0x62, 0x00,
  0x62, 0x00, 0x5e, 0x00, 0x5a, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x58, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x5a, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x5e, 0x00, 0x00, 0x00, 0x62, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x40, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x40, 0x00, 0x00, 0x00, 0x42, 0x40, 0x42, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x42, 0x00, 0x00, 0x00, 0x46, 0x42, 0x46, 0x00, 0x00, 0x00, 0x42, 0x00,
  0x46, 0x00, 0x00, 0x00, 0x4a, 0x00, 0x00, 0x00, 0x00, 0x00, 0x4a, 0x00,
  0x4a, 0x00, 0x46, 0x00, 0x42, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x42, 0x00,
  0x42, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x4c, 0x4a,
  0x46, 0x00, 0x00, 0x00, 0x4a, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x30, 0x2e, 0x2c, 0x2a, 0x28, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x28, 0x00, 0x00, 0x00, 0x2a, 0x28, 0x2a, 0x00, 0x00, 0x00, 0x2a, 0x28,
  0x2a, 0x00, 0x00, 0x00, 0x2e, 0x2a, 0x2e, 0x00, 0x00, 0x00, 0x2a, 0x00,
  0x2e, 0x2a, 0x2e, 0x00, 0x32, 0x00, 0x00, 0x00, 0x00, 0x00, 0x32, 0x00,
  0x32, 0x00, 0x2e, 0x00, 0x2a, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x28, 0x2a, 0x28, 0x2a, 0x28, 0x00, 0x00, 0x00, 0x00, 0x00, 0x2a, 0x00,
  0x2a, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x34, 0x32,
  0x2e, 0x00, 0x00, 0x00, 0x32, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x32,
  0x34, 0x36, 0x38, 0x3a, 0x3c, 0x3e, 0x40, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x28, 0x00, 0x00, 0x00, 0x42, 0x40, 0x42, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x2a, 0x00, 0x00, 0x00, 0x46, 0x42, 0x46, 0x00, 0x00, 0x00, 0x42, 0x00,
  0x00, 0x00, 0x46, 0x42, 0x46, 0x00, 0x4a, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x1a, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x40, 0x00,
  0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x2a, 0x00,
  0x2a, 0x28, 0x2a, 0x28, 0x2a, 0x28, 0x26, 0x24, 0x22, 0x20, 0x1e, 0x04,
  0x16, 0x00, 0x00, 0x00, 0x1a, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x40, 0x00, 0x32, 0x00, 0x00, 0x00,
  0x40, 0x00, 0x38, 0x00, 0x00, 0x00, 0x42, 0x40, 0x42, 0x00, 0x3c, 0x00,
  0x42, 0x00, 0x00, 0x00, 0x00, 0x00, 0x46, 0x40, 0x46, 0x40, 0x42, 0x00,
  0x46, 0x00, 0x00, 0x00, 0x4a, 0x42, 0x4a, 0x42, 0x00, 0x00, 0x4a, 0x00,
  0x4a, 0x00, 0x46, 0x00, 0x42, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x40, 0x00, 0x32, 0x00, 0x40, 0x00, 0x32, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x2a, 0x42, 0x2a, 0x42, 0x2a, 0x42, 0x28, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x46, 0x00, 0x00, 0x00, 0x4a, 0x2a, 0x4a, 0x2a, 0x4a, 0x2a, 0x4a, 0x2a,
  0x4a, 0x2a, 0x4a, 0x2a, 0x4a, 0x2a, 0x40, 0x00, 0x1a, 0x00, 0x00, 0x00,
  0x40, 0x00, 0x20, 0x00, 0x00, 0x00, 0x42, 0x40, 0x42, 0x00, 0x00, 0x00,
  0x24, 0x00, 0x42, 0x00, 0x00, 0x00, 0x46, 0x28, 0x46, 0x28, 0x42, 0x24,
  0x42, 0x24, 0x46, 0x28, 0x46, 0x28, 0x4a, 0x2a, 0x4a, 0x2a, 0x4a, 0x2a,
  0x4a, 0x42, 0x3c, 0x42, 0x4a, 0x42, 0x3c, 0x32, 0x3c, 0x42, 0x3c, 0x32,
  0x40, 0x00, 0x1a, 0x00, 0x00, 0x00, 0x1a, 0x00, 0x1a, 0x12, 0x1a, 0x12,
  0x42, 0x00, 0x00, 0x00, 0x00, 0x00, 0x42, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x46, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0e, 0x00, 0x46, 0x00, 0x4a, 0x0c,
  0x4a, 0x0c, 0x4a, 0x0c, 0x4a, 0x0c, 0x48, 0x0a, 0x46, 0x08, 0x44, 0x06,
  0x58, 0x20, 0x00, 0x00, 0x1a, 0x00, 0x58, 0x20, 0x00, 0x00, 0x1a, 0x00,
  0x5a, 0x24, 0x00, 0x00, 0x1a, 0x00, 0x5a, 0x24, 0x00, 0x00, 0x1a, 0x00,
  0x5e, 0x28, 0x28, 0x00, 0x5a, 0x1a, 0x5e, 0x28, 0x24, 0x00, 0x62, 0x20,
  0x24, 0x00, 0x14, 0x00, 0x12, 0x00, 0x1a, 0x00, 0x14, 0x00, 0x12, 0x00,
  0x1a, 0x00, 0x00, 0x00, 0x02, 0x00, 0x58, 0x08, 0x00, 0x00, 0x1a, 0x00,
  0x1a, 0x00, 0x00, 0x00, 0x02, 0x00, 0x5a, 0x0c, 0x00, 0x00, 0x1a, 0x00,
  0x02, 0x00, 0x04, 0x00, 0x08, 0x00, 0x5e, 0x04, 0x08, 0x00, 0x62, 0x12,
  0x42, 0x00, 0x44, 0x00, 0x42, 0x00, 0x44, 0x00, 0x4a, 0x00, 0x58, 0x14,
  0x16, 0x00, 0x1a, 0x00, 0x16, 0x00, 0x14, 0x00, 0x16, 0x00, 0x1a, 0x00,
  0x1e, 0x00, 0x24, 0x00, 0x26, 0x00, 0x28, 0x00, 0x2c, 0x00, 0x28, 0x00,
  0x5e, 0x24, 0x22, 0x00, 0x5a, 0x20, 0x1a, 0x00, 0x5e, 0x16, 0x12, 0x00,
  0x62, 0x00, 0x4a, 0x00, 0x4a, 0x00, 0x4a, 0x00, 0x4a, 0x00, 0x58, 0x0a,
  0x08, 0x00, 0x02, 0x00, 0x58, 0x0a, 0x08, 0x00, 0x02, 0x00, 0x5a, 0x0c,
  0x02, 0x00, 0x06, 0x00, 0x0c, 0x00, 0x0e, 0x00, 0x1a, 0x00, 0x14, 0x00,
  0x16, 0x00, 0x1a, 0x00, 0x5e, 0x1e, 0x26, 0x00, 0x28, 0x00, 0x62, 0x2a,
  0x62, 0x4a, 0x5c, 0x44, 0x62, 0x4a, 0x5c, 0x44, 0x5a, 0x42, 0x58, 0x40,
  0x50, 0x38, 0x4a, 0x32, 0x38, 0x20, 0x32, 0x1a, 0x2a, 0x12, 0x5a, 0x42,
  0x54, 0x3c, 0x4c, 0x34, 0x3c, 0x24, 0x34, 0x1c, 0x2e, 0x16, 0x5e, 0x46,
  0x56, 0x3e, 0x50, 0x38, 0x62, 0x5a, 0x54, 0x4e, 0x4a, 0x42, 0x3c, 0x36,
  0x32, 0x2a, 0x24, 0x1e, 0x1a, 0x12, 0x0c, 0x06, 0x02, 0x04, 0x02, 0x04,
  0x02, 0x04, 0x02, 0x04, 0x02, 0x04, 0x02, 0x04, 0x02, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x62, 0x00, 0x66
};
size_t intro_music_size = sizeof(intro_music);

