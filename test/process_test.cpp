#include "pipedcp/process.h"

#include <iostream>
#include <unistd.h>
#include <string.h>

#include "gtest/gtest.h"

namespace pipedcp {

class ProcessTest : public ::testing::Test {
protected:
  void SetUp() override {
    const char *pathname {"/app/test/assets/read-echo.sh"};
    const char *const argv[] = {nullptr};
    process.execvp(pathname, argv);
  }

  void TearDown() override {
    process.close();
    process.kill();
  }

  pipedcp::Process process;
  char msg[256];
  char buffer[256];
};

TEST_F(ProcessTest, ReadAndWriteToChildProcess) {
  strncpy(msg, "domo\n", sizeof(msg) - 1);
  write(process.writefd(), msg, strlen(msg));
  read(process.readfd(), buffer, sizeof(buffer));

  EXPECT_TRUE(strcmp(msg, buffer) == 0);
}

} /* namespace pipedcp */
