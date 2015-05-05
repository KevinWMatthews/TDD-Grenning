#ifndef Test_Example_H_
#define Test_Example_H_

class Test_Example
{
  public:
    explicit Test_Example();
    virtual ~Test_Example();

  private:
    Test_Example(const Test_Example&);
    Test_Example& operator=(const Test_Example&);
};

#endif
