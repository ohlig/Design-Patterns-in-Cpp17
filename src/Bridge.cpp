#include <iostream>
#include <memory>
#include <utility>

class AbstractionImpl {
 public:
  virtual void PrintImpl() = 0;
  virtual ~AbstractionImpl() = default;
};

class AImpl1 : public AbstractionImpl {
 public:
  void PrintImpl() override { std::cout << 1; }
};

class AImpl2 : public AbstractionImpl {
 public:
  void PrintImpl() override { std::cout << 2; }
};

class Abstraction {
 public:
  virtual void Print() = 0;
  virtual ~Abstraction() = default;
};

class A1 : public Abstraction {
 public:
  explicit A1(std::unique_ptr<AbstractionImpl> p) : p_(std::move(p)) {}

  void Print() override { p_->PrintImpl(); }

 private:
  std::unique_ptr<AbstractionImpl> p_;
};

class A2 : public Abstraction {
 public:
  explicit A2(std::unique_ptr<AbstractionImpl> p) : p_(std::move(p)) {}

  void Print() override { p_->PrintImpl(); }

 private:
  std::unique_ptr<AbstractionImpl> p_;
};

int main() {
  std::unique_ptr<Abstraction> a1 =
      std::make_unique<A1>(std::make_unique<AImpl1>());
  std::unique_ptr<Abstraction> a2 =
      std::make_unique<A1>(std::make_unique<AImpl2>());
  std::unique_ptr<Abstraction> a3 =
      std::make_unique<A2>(std::make_unique<AImpl1>());
  std::unique_ptr<Abstraction> a4 =
      std::make_unique<A2>(std::make_unique<AImpl2>());

  a1->Print();  // 1
  a2->Print();  // 2
  a3->Print();  // 1
  a4->Print();  // 2
}