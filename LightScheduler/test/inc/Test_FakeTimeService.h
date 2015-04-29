#ifndef D_Test_FakeTimeService_h
#define D_Test_FakeTimeService_h

class Test_FakeTimeService
{
  public:
    explicit Test_FakeTimeService();
    virtual ~Test_FakeTimeService();

  private:
    Test_FakeTimeService(const Test_FakeTimeService&);
    Test_FakeTimeService& operator=(const Test_FakeTimeService&);
};

#endif  // D_Test_FakeTimeService_h
