

class Registers
{
    public:
        short getValueRegister(short index);
        void setValueRegister(short index,short value);
        void setLSBRegister(short index,unsigned char value);
        void setMSBRegister(short index,unsigned char value);

    private:
        short registers[16];
};