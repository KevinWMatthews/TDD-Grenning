#ifndef D_Test_Flash_h
#define D_Test_Flash_h

class Test_Flash
{
  public:
    explicit Test_Flash();
    virtual ~Test_Flash();

  private:
    Test_Flash(const Test_Flash&);
    Test_Flash& operator=(const Test_Flash&);
};

#endif  // D_Test_Flash_h
