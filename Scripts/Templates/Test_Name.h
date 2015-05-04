#ifndef Test_Name_H_
#define Test_Name_H_

class Test_Name
{
  public:
    explicit Test_Name();
    virtual ~Test_Name();

  private:
    Test_Name(const Test_Name&);
    Test_Name& operator=(const Test_Name&);
};

#endif
