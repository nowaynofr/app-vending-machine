#include "mainwindow.h"

#include <QApplication>

#if defined (Q_OS_ANDROID)
#include <QtAndroid>

bool requestAndroidPermissions(){
    //Request requiered permissions at runtime

    const QVector<QString> permissions({"android.permission.RECEIVE_BOOT_COMPLETED",
                                        "android.permission.REORDER_TASKS",
                                        "android.permission.SYSTEM_ALERT_WINDOW",
                                        "android.permission.EXPAND_STATUS_BAR",
                                        "android.permission.GET_TASKS",
                                        "android.permission.WAKE_LOCK"});

    for(const QString &permission : permissions){
        auto result = QtAndroid::checkPermission(permission);
        if(result == QtAndroid::PermissionResult::Denied){
            auto resultHash = QtAndroid::requestPermissionsSync(QStringList({permission}));
            if(resultHash[permission] == QtAndroid::PermissionResult::Denied)
                return false;
        }
    }

    return true;
}
#endif

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    #if defined (Q_OS_ANDROID)
        if(!requestAndroidPermissions())
            return -1;
    #endif
    MainWindow w;
    w.showFullScreen();
    return a.exec();
}
