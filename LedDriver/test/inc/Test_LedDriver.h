#ifndef D_Test_LedDriver_h
#define D_Test_LedDriver_h

class Test_LedDriver
{
  public:
    explicit Test_LedDriver();
    virtual ~Test_LedDriver();

  private:
    Test_LedDriver(const Test_LedDriver&);
    Test_LedDriver& operator=(const Test_LedDriver&);
};

#endif  // D_Test_LedDriver_h
