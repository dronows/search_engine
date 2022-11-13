#include "..\\inc\\search_engine.h"
#include "gtest/gtest.h"


struct ConverterJsonFixture :public testing::Test {
  ConverterJSON fixJs;
  static void SetUpTestSuite() {
    std::cout << "SetUpTestSuite " << std::endl;
  }
  static void TearDownTestSuite() {
    std::cout << "TearDownTestSuite" << std::endl;
  }
  void SetUp() override {
    std::cout << "SetUp" << std::endl;
  }
  void TearDown() override {
    std::cout << "TearDown" << std::endl;
  }
};

TEST_F(ConverterJsonFixture, GetTextDoc) {
  std::vector<std::string> toFiles{ "file001.txt",
        "file002.txt",
        "file003.txt",
        };
  fixJs.AddFile(toFiles);
  std::vector<std::string> fromFiles = fixJs.GetTextDocuments();
  ASSERT_EQ(toFiles.size(), fromFiles.size());
  for (size_t i = 0; i < fromFiles.size(); ++i) {
    EXPECT_EQ(toFiles[i], fromFiles[i]);
    
  }
}
 
TEST_F(ConverterJsonFixture, GetRequests) {
  std::vector<std::string> toRequests{ "one","two","three" };
  fixJs.AddRequests(toRequests);
  std::vector<std::string> fromRequests = fixJs.GetRequests();
  ASSERT_EQ(toRequests.size(), fromRequests.size());
  for (size_t i = 0; i < fromRequests.size(); ++i) {
    EXPECT_EQ(toRequests[i], fromRequests[i]);
  }
}

TEST_F(ConverterJsonFixture, PutAnswer) {
  std::vector<std::vector<std::pair<int, float>>> toAnswer{ { {5,2.6},{2,7.1}} ,{{4, 9.2}} };
  fixJs.putAnswers(toAnswer);
  std::vector<std::vector<std::pair<int, float>>> fromAnswer;
  fromAnswer = fixJs.getAnswer();
  ASSERT_EQ(toAnswer.size(), fromAnswer.size());
  for (size_t i = 0; i < toAnswer.size(); ++i) {
    for (size_t j = 0; j < toAnswer[i].size(); ++j) {
      EXPECT_EQ(toAnswer[i][j], fromAnswer[i][j]);
    }
  }
}


int main(int argc, char** argv) {
  testing::InitGoogleTest(&argc, argv);

  return RUN_ALL_TESTS();
}

