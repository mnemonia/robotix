class Light {
  public:
    Light(int pwmPin);
    void on();
    void off();
  private:
    int _pwmPin;
};
