#include <cstddef>
#include <fstream>
#include <iostream>
#include <optional>
#include <pthread.h>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>

namespace Emulator {
  enum Reg {
    R0,
    R1,
    R2,
    R3
  };

  struct EmulatorState {
    static const size_t regs_size = 4;
    static const size_t mem_size  = 1024;

    std::vector<int> _registers{regs_size};
    std::vector<int> _mem{mem_size};

    size_t _pc = 0; // program counter register
  };

  class Instruction {
  public:
    virtual void eval(EmulatorState& emul) = 0;
    virtual ~Instruction(){};
  };

  class MovReg: public Instruction {
    Reg _dst, _src;

  public:
    MovReg(Reg dst, Reg src):
        _dst(dst), _src(src) {}

    void eval(EmulatorState& emul) override {
      emul._registers[_dst] = emul._registers[_src];
      emul._pc++;
    }
  };

  class MovImm: public Instruction {
    Reg _dst;
    int _val;

  public:
    MovImm(Reg dst, int val):
        _dst(dst), _val(val){};

    void eval(EmulatorState& emul) override {
      emul._registers[_dst] = _val;
      emul._pc++;
    }
  };

  class AddReg: public Instruction {
    Reg _dst, _src;

  public:
    AddReg(Reg dst, Reg src):
        _dst(dst), _src(src) {}

    void eval(EmulatorState& emul) override {
      emul._registers[_dst] += emul._registers[_src];
      emul._pc++;
    }
  };

  class AddImm: public Instruction {
    Reg _dst;
    int _val;

  public:
    AddImm(Reg dst, int val):
        _dst(dst), _val(val) {}

    void eval(EmulatorState& emul) override {
      emul._registers[_dst] += _val;
      emul._pc++;
    }
  };

  class SubReg: public Instruction {
    Reg _dst, _src;

  public:
    SubReg(Reg dst, Reg src):
        _dst(dst), _src(src) {}

    void eval(EmulatorState& emul) override {
      emul._registers[_dst] -= emul._registers[_src];
      emul._pc++;
    }
  };

  class SubImm: public Instruction {
    Reg _dst;
    int _val;

  public:
    SubImm(Reg dst, int val):
        _dst(dst), _val(val) {}

    void eval(EmulatorState& emul) override {
      emul._registers[_dst] -= _val;
      emul._pc++;
    }
  };

  class MulReg: public Instruction {
    Reg _dst, _src;

  public:
    MulReg(Reg dst, Reg src):
        _dst(dst), _src(src) {}

    void eval(EmulatorState& emul) override {
      emul._registers[_dst] *= emul._registers[_src];
      emul._pc++;
    }
  };

  class MulImm: public Instruction {
    Reg _dst;
    int _val;

  public:
    MulImm(Reg dst, int val):
        _dst(dst), _val(val) {}

    void eval(EmulatorState& emul) override {
      emul._registers[_dst] *= _val;
      emul._pc++;
    }
  };

  class DivReg: public Instruction {
    Reg _dst, _src;

  public:
    DivReg(Reg dst, Reg src):
        _dst(dst), _src(src) {}

    void eval(EmulatorState& emul) override {
      emul._registers[_dst] /= emul._registers[_src];
      emul._pc++;
    }
  };

  class DivImm: public Instruction {
    Reg _dst;
    int _val;

  public:
    DivImm(Reg dst, int val):
        _dst(dst), _val(val) {}

    void eval(EmulatorState& emul) override {
      emul._registers[_dst] /= _val;
      emul._pc++;
    }
  };

  class Load: public Instruction {
    Reg _dst;
    int _addr;

  public:
    Load(Reg dst, int addr):
        _dst(dst), _addr(addr) {}

    void eval(EmulatorState& emul) {
      if (_addr < 0 || (size_t) _addr >= emul.mem_size) {
        throw std::runtime_error("Out of memory.");
      }
      emul._registers[_dst] = emul._mem[_addr];
      emul._pc++;
    }
  };

  class Store: public Instruction {
    Reg _src;
    int _addr;

  public:
    Store(Reg src, int addr):
        _src(src), _addr(addr) {}

    void eval(EmulatorState& emul) {
      if (_addr < 0 || (size_t) _addr >= emul.mem_size) {
        throw std::runtime_error("Out of memory.");
      }
      emul._mem[_addr] = emul._registers[_src];
      emul._pc++;
    }
  };

  class Jmp: public Instruction {
    int _offset;

  public:
    Jmp(int offset):
        _offset(offset) {}

    void eval(EmulatorState& emul) {
      emul._pc = (size_t) _offset;
    }
  };

  class Jmpz: public Instruction {
    int _offset;

  public:
    Jmpz(int offset):
        _offset(offset) {}

    void eval(EmulatorState& emul) {
      if (emul._registers[R0] == 0) {
        emul._pc = (size_t) _offset;
      } else {
        emul._pc++;
      }
    }
  };

  /* This function accepts the program written in the vrisc assembly
   * If the input program is correct, returns sequence of insturction, corresponding to the input program.
   * If the input text is incorrect, the behaviour is undefined
   */
  std::vector<Instruction*>
  parse(const std::string& program) {
    std::vector<Instruction*> instructions;
    std::istringstream iss(program);
    std::string line;

    std::unordered_map<std::string, Emulator::Reg> reg_map = {
        {"R0", Emulator::R0}, {"R1", Emulator::R1}, {"R2", Emulator::R2}, {"R3", Emulator::R3}};

    while (std::getline(iss, line)) {
      if (line.empty()) {
        continue;
      }

      std::istringstream line_stream(line);
      std::string op, arg1, arg2;

      line_stream >> op >> arg1 >> arg2;

      bool is_reg1 = reg_map.count(arg1);
      bool is_reg2 = reg_map.count(arg2);

      if (op == "Mov") {
        //std::cout << "Mov arguments: " << arg1 << arg2 << is_reg1 << is_reg2 << std::endl;
        if (is_reg1 && is_reg2)
          instructions.push_back(new Emulator::MovReg(reg_map[arg1], reg_map[arg2]));
        else if (is_reg1 && !is_reg2)
          instructions.push_back(new Emulator::MovImm(reg_map[arg1], std::stoi(arg2)));
        else
          throw std::runtime_error("Parsing error for Mov.");
      } else if (op == "Add") {
        if (is_reg1 && is_reg2)
          instructions.push_back(new Emulator::AddReg(reg_map[arg1], reg_map[arg2]));
        else if (is_reg1)
          instructions.push_back(new Emulator::AddImm(reg_map[arg1], std::stoi(arg2)));
        else
          throw std::runtime_error("Parsing error for Add.");
      } else if (op == "Sub") {
        if (is_reg1 && is_reg2)
          instructions.push_back(new Emulator::SubReg(reg_map[arg1], reg_map[arg2]));
        else if (is_reg1)
          instructions.push_back(new Emulator::SubImm(reg_map[arg1], std::stoi(arg2)));
        else
          throw std::runtime_error("Parsing error for Sub.");
      } else if (op == "Mul") {
        if (is_reg1 && is_reg2)
          instructions.push_back(new Emulator::MulReg(reg_map[arg1], reg_map[arg2]));
        else if (is_reg1)
          instructions.push_back(new Emulator::MulImm(reg_map[arg1], std::stoi(arg2)));
        else
          throw std::runtime_error("Parsing error for Mul.");
      } else if (op == "Div") {
        if (is_reg1 && is_reg2)
          instructions.push_back(new Emulator::DivReg(reg_map[arg1], reg_map[arg2]));
        else if (is_reg1)
          instructions.push_back(new Emulator::DivImm(reg_map[arg1], std::stoi(arg2)));
        else
          throw std::runtime_error("Parsing error for Div.");
      } else if (op == "Load") {
        if (is_reg1)
          instructions.push_back(new Emulator::Load(reg_map[arg1], std::stoi(arg2)));
        else
          throw std::runtime_error("Parsing error for Load.");
      } else if (op == "Store") {
        if (is_reg1)
          instructions.push_back(new Emulator::Store(reg_map[arg1], std::stoi(arg2)));
        else
          throw std::runtime_error("Parsing error for Store.");
      } else if (op == "Jmp") {
        instructions.push_back(new Emulator::Jmp(std::stoi(arg1)));
      } else if (op == "Jmpz") {
        instructions.push_back(new Emulator::Jmpz(std::stoi(arg1)));
      }
    }
    return instructions;
  }

  /* Emulate receive a program, written in the vrisc assembly,
   * in case of the correct program, emulate returns R0 value at the end of the emulation.
   * If the program is incorrect, that is, either its text is not vrisc assembly language or it contains UB(endless cycles),
   * the behaviour of emulate if also undefined. Handle these cases in any way.
   */
  int emulate(const std::string& program_text) {
    try {
      std::vector<Instruction*> program = parse(program_text);

      EmulatorState state;


      while (state._pc < program.size()) {
        Instruction* current_instruction = program[state._pc];

        if (current_instruction == nullptr) {
          throw std::runtime_error("Invalid instruction pointer.");
        }

        current_instruction->eval(state);

        if (state._pc >= program.size()) {
          break;
        }
      }

      for (size_t i = 0; i < program.size(); i++)
        delete program[i];

      return state._registers[R0];
    } catch (const std::exception& e) {
      std::cerr << "Emulation error: " << e.what() << std::endl;
      return -1;
    }
  }

} // namespace Emulator
