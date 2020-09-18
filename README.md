# pipedcp
- Provides piped child process so that parent process can read/write to stdio.

# Todo
- [x] implement basic usage and test
- [ ] make it installable with cmake

# Apis
- Create child process
  - Can write to standard input
  - Can read standard output

# Reference
- https://www.unix.com/unix-for-dummies-questions-and-answers/63311-how-write-stdin-another-program-program-stdin-program-b.html
- https://man7.org/linux/man-pages/man2/pipe.2.html
- https://man7.org/linux/man-pages/man2/dup.2.html
- https://stackoverflow.com/questions/6171552/popen-simultaneous-read-and-write
- https://stackoverflow.com/a/47072631
