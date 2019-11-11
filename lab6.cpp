#include <unistd.h>
#include <sys/time.h>
#include <signal.h>
#include <wait.h>
#include <iostream>

using namespace std;

int LAST_PID;

void subrun(int i) {
  if(fork() == 0) {
    LAST_PID = getpid();
    timeval curtime;

    gettimeofday(&curtime, NULL);
    cout << "Subprocess PID: " << getpid() << endl << ctime(&curtime.tv_sec) << endl;

    exit(EXIT_SUCCESS);
  }

  // execl("./sub_prog", argv[0], (char*) 0);
}

int main(int argc, char const *argv[]) {

  sigset_t mask;
  struct sigaction act;

  int n_of_runs;
  timeval per;
  itimerval timer, timer_c;
  time_t pr_s = time(NULL), sub_s, rt_s;

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

  sigemptyset(&mask);
  sigaddset(&mask, SIGTSTP);
  sigprocmask(SIG_BLOCK, &mask, NULL);

  signal(SIGALRM, subrun);

  timer.it_interval = per;
  timer.it_value.tv_sec = 2;
  timer.it_value.tv_usec = 0;

  setitimer(ITIMER_REAL, &timer, NULL);
  for(int i = 0; i < n_of_runs; i++) {
    // cout << "\n[RUN]\n";
    rt_s = time(NULL);
    pause();

    // sigset_t t; int p;
    // sigaddset(&t, SIGALRM);
    // sigwait(&t, &p);

    cout << "Real time period: " << difftime(time(NULL), rt_s) << endl;
  }

  usleep(1000);
  cout << "\n- - -\nProcess working time: " << difftime(time(NULL), pr_s) << endl;

  return 0;
}
