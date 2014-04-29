class Position {
  float x;
  float y;
  float z;
 public:
  float X();
  float Y();
  void MoveTo(float x, float y, float time);
  Position();
  ~Position();
};
