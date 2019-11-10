#include <unistd.h>
#include <sys/time.h>
#include <signal.h>
#include <iostream>

using namespace std;

void subrun(int i) {
  if(fork() == 0) {
    timeval curtime;

    gettimeofday(&curtime, NULL);
    cout << ctime(&curtime.tv_sec) << endl;
  }

    // execl("./sub_prog", argv[0], (char*) 0);
}

int main(int argc, char const *argv[]) {

  // sigset_t mask;
  struct sigaction act;

  int n_of_runs;
  timeval per;
  itimerval timer, timer_c;

  try {
    n_of_runs = stoi(argv[1]);
  } catch(exception &e) {
    cout << e.what() << endl;
    return 1;
  }

  try {
    per.tv_sec = stoi(argv[2]);
    per.tv_usec = 0;
  } catch(exception &e) {
    cout << e.what() << endl;
    return 1;
  }

  // sigemptyset(&mask);
  // sigaddset(&mask, SIGTSTP);
  // sigprocmask(SIG_BLOCK, &mask, NULL);

  signal(SIGALRM, subrun);

  timer.it_interval = per;
  timer.it_value.tv_sec = 2;
  timer.it_value.tv_usec = 0;

  setitimer(ITIMER_REAL, &timer, NULL);
  for(int i = 0; i < n_of_runs; i++) {
    pause();
    // signal(SIGALRM, subrun);
  }

  return 0;
}
