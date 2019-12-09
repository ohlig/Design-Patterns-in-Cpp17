#include <iostream>
#include <memory>

class Strategy {
 public:
  virtual void Print() = 0;
  virtual ~Strategy() = default;
};

class StrategyA : public Strategy {
 public:
  void Print() override { std::cout << "StrategyA\n"; }
};

class StrategyB : public Strategy {
 public:
  void Print() override { std::cout << "StrategyB\n"; }
};

class Context {
 public:
  Context(std::unique_ptr<Strategy> p) : p_(std::move(p)) {}

  void Print() const { p_->Print(); }

 private:
  std::unique_ptr<Strategy> p_;
};

int main() {
  Context a{std::make_unique<StrategyA>()};
  Context b{std::make_unique<StrategyB>()};

  a.Print();  // StrategyA
  b.Print();  // StrategyB
}