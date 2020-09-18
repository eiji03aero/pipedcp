#include "pipedcp/process.h"

namespace pipedcp {

void Process::kill() {
  ::kill(child_pid, SIGKILL);
}

void Process::close() {
  ::close(outpipefd[0]);
  ::close(outpipefd[1]);
  ::close(inpipefd[0]);
  ::close(inpipefd[1]);
}

} /* namespace pipedcp */
