// Program 1: Process creation using fork(), exec() and wait()
#include <iostream>
#include <cstdlib>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
using namespace std;

int main() {
    cout << "Parent process: PID = " << getpid() << endl;
    pid_t pid = fork();

    if (pid < 0) {
        perror("fork failed");
        return 1;
    } else if (pid == 0) {
        cout << "Child process: PID = " << getpid()
             << ", Parent PID = " << getppid() << endl;
        cout << "Child is about to exec 'ls -l'" << endl;
        execlp("ls", "ls", "-l", (char *)nullptr);
        perror("exec failed");   // only reached if exec fails
        _exit(1);
    } else {
        cout << "Parent waiting for child (PID = " << pid << ") to finish..." << endl;
        int status;
        wait(&status);
        if (WIFEXITED(status))
            cout << "Child exited with status " << WEXITSTATUS(status) << endl;
        cout << "Parent process resumes and exits." << endl;
    }
    return 0;
}
