#ifndef PIPEDCP_PIPEDCP_H_INCLUDED
#define PIPEDCP_PIPEDCP_H_INCLUDED

#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <signal.h>
#include <stdlib.h>
#include <stdio.h>
#include <chrono>
#include <thread>
#include <string>

namespace pipedcp {

class Process {
public:
  void kill();
  void close();

  int writefd() { return outpipefd[1]; }
  int readfd() { return inpipefd[0]; }

  template<std::size_t N>
  void execvp(const char* pathname, const char *const (&argv)[N]) {
    pipe(inpipefd);
    pipe(outpipefd);

    child_pid = fork();

    // child process work here.
    if (child_pid == 0) {
      dup2(outpipefd[0], STDIN_FILENO);
      dup2(inpipefd[1], STDOUT_FILENO);
      dup2(inpipefd[1], STDERR_FILENO);

      // exec replaces this process with command, so below this line should not be executed
      // unless there was an error.
      ::execvp(pathname, const_cast<char* const*>(argv));

      exit(1);
    }

    // FIXME: better way to make sure child process is started
    std::this_thread::sleep_for(std::chrono::milliseconds {100});
  };

  // child_pid holds pid of child process on parent
  pid_t child_pid;
  int inpipefd[2];
  int outpipefd[2];
  int status {0};
};

} /* namespace pipedcp */

#endif /* ifndef PIPEDCP_PIPEDCP_H_INCLUDED */
