

class RAM
{

    public:
        RAM();
        short getValue(short index);
        void setValue(short value,short index);
    private:
        short mem[65536];
};