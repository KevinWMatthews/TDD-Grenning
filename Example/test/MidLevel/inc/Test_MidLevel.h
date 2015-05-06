#ifndef Test_MidLevel_H_
#define Test_MidLevel_H_

class Test_MidLevel
{
  public:
    explicit Test_MidLevel();
    virtual ~Test_MidLevel();

  private:
    Test_MidLevel(const Test_MidLevel&);
    Test_MidLevel& operator=(const Test_MidLevel&);
};

#endif
