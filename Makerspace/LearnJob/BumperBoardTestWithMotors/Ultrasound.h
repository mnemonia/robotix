class Ultrasound
{
  public:
    Ultrasound(int echoPin, int triggerPin);
    int distance();
  private:
    int _echoPin;
    int _triggerPin;
};
