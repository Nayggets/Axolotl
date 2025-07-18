#include <memory>
#include <fstream>
#include <vector>
#include <cassert>
       #include <unistd.h>
#include "RAM.hpp"
#include "Registers.hpp"
#include "Decoder.hpp"

class Axolotl
{
    public: 
        //Singleton pattern
        void Emulate(std::ifstream& file);
        static Axolotl& getInstance() {
            static Axolotl instance;
            return instance;
        };

        Axolotl(const Axolotl&) = delete;
        Axolotl& operator=(const Axolotl&) = delete;
    private:
        void Execute(Instruction* toExecute);
        void ExecuteAdd(Instruction* toExecute);
        void ExecuteSub(Instruction* toExecute);
        void ExecuteXor(Instruction* toExecute);
        void ExecuteAnd(Instruction* toExecute);
        void ExecuteNot(Instruction* toExecute);
        void ExecuteOr(Instruction* toExecute);
        void ExecuteSll(Instruction* toExecute);
        void ExecuteSlr(Instruction* toExecute);
        void ExecuteLoadLSB(Instruction* toExecute);
        void ExecuteLoadMSB(Instruction* toExecute);
        void ExecuteMemStore(Instruction* toExecute);
        void ExecuteMemLoad(Instruction* toExecute);
        void ExecuteJe(Instruction* toExecute);
        void ExecuteJlt(Instruction* toExecute);
        void ExecuteJgt(Instruction* toExecute);
        void ExecuteRet(Instruction* toExecute);
        void printState();
        // Private constructor to prevent direct instantiation
        Axolotl() {
            mem = std::make_unique<RAM>();
            registers = std::make_unique<Registers>();
            decoder = std::make_unique<Decoder>();
            PC = 0;
            stopped = false;
        }

        ~Axolotl() = default; // private destructor optional

    private:
        std::unique_ptr<RAM> mem;
        std::unique_ptr<Registers> registers;       
        std::unique_ptr<Decoder> decoder; 
        short PC;
        bool stopped;
};