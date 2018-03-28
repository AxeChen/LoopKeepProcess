#include <jni.h>
#include <string>
#include "native_lib.h"



int user_id;


void sig_handler(int sino){
    int status;
    wait(&status);
    create_child();
}

extern "C"
JNIEXPORT void JNICALL
Java_com_mg_axechen_processerone_Watcher_createWatcher(JNIEnv *env, jobject instance, jint userId) {

    // TODO
    user_id = userId;

//    // 防止子进程被杀死,监听sigchld信号量
//    struct sigaction sa;
//    sa.sa_flags = 0;
//    sa.sa_handler = sig_handler;
//    sigaction(SIGCHLD, &sa, NULL);

    create_child();

}




void create_child() {
    pid_t pid = fork();
    if (pid < 0) {

    } else if (pid > 0) {

    } else if (pid == 0) {
        //LOGE("子进程开启 ");
        LOGE("子进程开启 ");
        child_start_monitor();
    }
}

// it like runnable in java's thread
void *thread_rt(void *data) {
    pid_t pid;
    while ((pid == getppid()) != 1) {
        sleep(2);
    }
    LOGE("重启父进程");
    execlp("am", "am", "startservice", "--user", user_id,
           "com.dongnao.signalprocess/com.dongnao.signalprocess.ProcessService", (char*)NULL);
}

void child_start_monitor() {
    // start a thread
    pthread_t tid;
    pthread_create(&tid, NULL, thread_rt, NULL);
}