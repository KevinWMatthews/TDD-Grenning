#ifndef D_Test_CircularBuffer_h
#define D_Test_CircularBuffer_h

class Test_CircularBuffer
{
  public:
    explicit Test_CircularBuffer();
    virtual ~Test_CircularBuffer();

  private:
    Test_CircularBuffer(const Test_CircularBuffer&);
    Test_CircularBuffer& operator=(const Test_CircularBuffer&);
};

#endif  // D_Test_CircularBuffer_h
