class LightController {
  public:
    LightController(int ldrPin, int ledPin);
    void tick();
    void off();
  private:
    int _lastLedValue; 
    int _currentLdrValue; 
    int _lastLdrValue; 
    int _ldrPin;
    int _ledPin; 
    void dimUp(int ledValue);
    void dimDown(int ledValue);
    int mapLdrValueToLedValue(int value);
};
