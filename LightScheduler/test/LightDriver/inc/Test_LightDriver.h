#ifndef Test_LightDriver_H_
#define Test_LightDriver_H_

class Test_LightDriver
{
  public:
    explicit Test_LightDriver();
    virtual ~Test_LightDriver();

  private:
    Test_LightDriver(const Test_LightDriver&);
    Test_LightDriver& operator=(const Test_LightDriver&);
};

#endif
