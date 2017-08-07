class AdditionalLight {
  public:
    AdditionalLight(int pin);
    void on();
    void off();
  private:
    int _pin;
};
