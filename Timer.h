class Timer {
 public:
  int Delta();
  void Start();
  void Stop();
  Timer();
  ~Timer();
  bool active;
  int l_ticks;
  int s_ticks;
  int e_ticks;
};
