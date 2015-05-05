#ifndef Test_LowLevel_H_
#define Test_LowLevel_H_

class Test_LowLevel
{
  public:
    explicit Test_LowLevel();
    virtual ~Test_LowLevel();

  private:
    Test_LowLevel(const Test_LowLevel&);
    Test_LowLevel& operator=(const Test_LowLevel&);
};

#endif
