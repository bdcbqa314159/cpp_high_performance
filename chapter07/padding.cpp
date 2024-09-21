#if _MSVC_VER
#pragma warning(disable : 4127)
#endif

#include <gtest/gtest.h>
#include <iostream>

class DocumentV1 {
  bool is_cached_{};
  double rank_{};
  int id_{};
};

class DocumentV2 {
  double rank_{};
  int id_{};
  bool is_cached_{};
};

TEST(Padding, ClassSize) {
  std::cout << sizeof(DocumentV1) << "\n";
  std::cout << sizeof(DocumentV2) << "\n";

  if (sizeof(double) > sizeof(int)) {
    ASSERT_TRUE(sizeof(DocumentV1) > sizeof(DocumentV2));
  }

  else {
    ASSERT_TRUE(sizeof(DocumentV1) == sizeof(DocumentV2));
  }
}
