#include "ArmDisassembler.h"

#include <cerrno>
#include <cstdlib>
#include <iomanip>
#include <iostream>
#include <string>

#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>

static bool bit(uint32_t value, size_t index) {
  return (value & (1 << index));
}

static void dumpHex32(std::ostream& os, uint32_t value) {
  os << std::hex << std::noshowbase << "0x" << std::setw(8) << std::setfill('0')
     << value
     << std::dec;
}

static void disassembleCondition(std::ostream& os, uint32_t instruction) {
  static const char* conditions[] = {
    "eq", "ne", "cs", "cc", "mi", "pl", "vs", "vc",
    "hi", "ls", "ge", "lt", "gt", "le", "", "nv",
  };
  os << conditions[(instruction >> 28) & 0xf];
}

static void disassembleCccccTttMmmm(std::ostream& os, uint32_t instruction) {
  os << ",r" << ((instruction >> 0) & 0xf);
  // If there's a shift other than "lsl 0" (which is the preferred way to
  // assemble no shift), decode it.
  if ((instruction & 0x00000ff0) != 0) {
    static const char* shiftMnemonic[] = { "lsl", "lsr", "asr", "ror" };
    os << " " << shiftMnemonic[(instruction >> 5) & 0x3] << " ";
    if (((instruction >> 4) & 1) != 0) {
      os << "r" << ((instruction >> 8) & 0xf);
    } else {
      os << ((instruction >> 8) & 0xf);
    }
  }
}

ArmDisassembler::ArmDisassembler(std::ostream& os) : os(os) {
}

void ArmDisassembler::disassembleInstruction(uint32_t address, uint32_t instruction) {
  dumpHex32(os, address);
  os << " : ";
  dumpHex32(os, instruction);
  os << " : ";
  // The three bits immediately below the condition bits are good
  // discriminators.
  const int high3 = (instruction & 0x0e000000) >> 25;
  if (high3 == 0x5) {
    // Branches.
    // xxxx101L oooooooo oooooooo oooooooo
    os << (bit(instruction, 24) ? "bl" : "b");
    disassembleCondition(os, instruction);
    os << " ";
    const int32_t offset = ((int32_t(instruction) & 0x00ffffff) << 8) >> 8;
    const uint32_t destination = address + 8 + (4 * offset);
    dumpHex32(os, destination);
  } else if ((instruction & 0x0fc000f0) == 0x00000090) {
    // Multiplication.
    // xxxx0000 00ASdddd nnnnssss 1001mmmm
    const bool mla = bit(instruction, 21);
    os << (mla ? "mla" : "mul");
    disassembleCondition(os, instruction);
    if (bit(instruction, 20)) {
      os << "s";
    }
    os << " r" << ((instruction >> 16) & 0xf);
    os << ",r" << ((instruction >> 0) & 0xf);
    os << ",r" << ((instruction >> 8) & 0xf);
    if (mla) {
      os << ",r" << ((instruction >> 12) & 0xf);
    }
  } else if ((instruction & 0x0f000000) == 0x0f000000) {
    // Software interrupt.
    // xxxx1111 yyyyyyyy yyyyyyyy yyyyyyyy
    os << "swi";
    disassembleCondition(os, instruction);
    os << " " << (instruction & 0x00ffffff);
  } else if (high3 == 0x0 || high3 == 0x1) {
    // Data processing instructions.
    // xxxx000a aaaSnnnn ddddcccc ctttmmmm  Register form
    // xxxx001a aaaSnnnn ddddrrrr bbbbbbbb  Immediate form
    const bool immediate = (high3 == 0x1);
    static const char* opCodes[] = {
      "and", "eor", "sub", "rsb", "add", "adc", "sbc", "rsc",
      "tst", "teq", "cmp", "cmn", "orr", "mov", "bic", "mvn",
    };
    const int opCode = (instruction >> 21) & 0xf;
    os << opCodes[opCode];
    disassembleCondition(os, instruction);
    const int rd = ((instruction >> 12) & 0xf);
    const int rn = ((instruction >> 16) & 0xf);
    if ((opCode & 0x8) == 0 || opCode == 0xc || opCode == 0xe) {
      // and, eor, sub, rsb, add, adc, sbc, rsc || orr || bic.
      if (bit(instruction, 20)) {
        os << "s";
      }
      os << " r" << rd << ",r" << rn;
    } else if ((opCode & 0xc) == 0x8) {
      // tst, teq, cmp, cmn.
      if (rd == 0xf) {
        os << "p";
      }
      // FIXME: rd should be 0x0 or 0xf; warn if not?
      os << " r" << rn;
    } else {
      // mov, mvn.
      if (bit(instruction, 20)) {
        os << "s";
      }
      os << " r" << rd;
      // FIXME: rn should be 0; warn if not?
    }
    if (immediate) {
      const uint32_t value = (instruction & 0xff);
      const uint32_t position = ((instruction >> 8) & 0xf);
      uint64_t barrel = (value << position);
      uint32_t result = (barrel & 0xffffffff) | (barrel >> 32);
      os << "," << result;
    } else {
      disassembleCccccTttMmmm(os, instruction);
    }
  } else if (high3 == 0x2 || high3 == 0x3) {
    // Single data transfer.
    // xxxx010P UBWLnnnn ddddoooo oooooooo  Immediate form
    // xxxx011P UBWLnnnn ddddcccc ctt0mmmm  Register form
    os << (bit(instruction, 20) ? "ldr" : "str");
    disassembleCondition(os, instruction);
    if (bit(instruction, 22)) {
      os << "b";
    }
    os << " r" << ((instruction >> 12) & 0xf)
       << ","
       << "[r" << ((instruction >> 16) & 0xf);
    if (bit(instruction, 25)) {
      disassembleCccccTttMmmm(os, instruction);
    } else {
      os << "FIXME: immediate form (12-bit offset)";
    }
    os << "]";
  } else if (high3 == 0x4) {
    // Block data transfer.
    // xxxx100P USWLnnnn llllllll llllllll
    os << (bit(instruction, 20) ? "ldm" : "stm");
    disassembleCondition(os, instruction);
    static const char* puBits[] = { "da", "ia", "db", "ib", };
    os << puBits[(instruction >> 23) & 0x3];
    os << " r" << ((instruction >> 16) & 0xf);
    if (bit(instruction, 21)) {
      os << "!";
    }
    os << ",{";
    // FIXME: fancier register lists, like "{r0-r8,r12,lr,pc}".
    int registerCount = 0;
    for (int i = 0; i < 16; ++i) {
      if (bit(instruction, i)) {
        if (registerCount > 0) {
          os << ",";
        }
        os << "r" << i;
        ++registerCount;
      }
    }
    os << "}";
    if (bit(instruction, 22)) {
      os << "^";
    }
  } else {
    // Unknown instruction.
    os << ".word ";
    dumpHex32(os, instruction);
  }
}

void ArmDisassembler::disassembleFile(const std::string& path) {
  int fd = TEMP_FAILURE_RETRY(open(path.c_str(), O_RDONLY));
  if (fd == -1) {
    std::cerr << path << ": open failed: " << strerror(errno) << "\n";
    exit(EXIT_FAILURE);
  }
  
  uint32_t address = 0;
  uint8_t buf[BUFSIZ];
  int bytesRead;
  while ((bytesRead = TEMP_FAILURE_RETRY(read(fd, buf, sizeof(buf)))) > 0) {
    for (uint8_t* p = &buf[0]; p != &buf[bytesRead]; p += 4) {
      uint32_t instruction = (p[0] << 24) | (p[1] << 16) | (p[2] << 8) | p[3];
      disassembleInstruction(address, instruction);
      os << std::endl;
      address += 4;
    }
  }
  if (bytesRead == -1) {
    // FIXME: this would leak 'fd' except we actually exit. need scoped_fd.
    std::cerr << path << ": read failed: " << strerror(errno) << "\n";
    exit(EXIT_FAILURE);
  }
  
  if (TEMP_FAILURE_RETRY(close(fd)) == -1) {
    std::cerr << path << ": close failed: " << strerror(errno) << "\n";
    exit(EXIT_FAILURE);
  }
}
